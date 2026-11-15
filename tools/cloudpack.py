"""Pack JSONL training rows for a cloud trainer, so the cloud never stores them in plain text.

pack drops each line that a project's drop rule matches from every string value in every row, turns each private word
into hidden_name, then refuses to write if a deny rule still matches a value. Dict keys are the row format's own and
are not checked. One pack holds named sets of rows (such as train and dev) and a small meta object (such as the export
manifest's sha256), so the cloud stores one opaque file. It gzips them and encrypts them with AES-256-GCM. keygen
writes the key, 32 random bytes in base64, to a file outside the repo; no command prints it. The trainer reads the key
from its own secret store (Kaggle Secrets) and calls load(), which decrypts in memory only and never writes the rows
to disk.

The trainer's outputs go back the other way, in boxes: boxgen writes an X25519 key pair, the private key to a file
outside the repo and the public key to a file the trainer embeds. seal_box encrypts with the public key alone, so the
cloud stores no output it can read; open decrypts a pulled output folder on the PC. A box hides its data but does not
prove who made it: anyone who holds the public key can make one.

Every function takes keys as bytes; decode_key turns a key file's base64 text into them.

Rules file, one rule per line, `#` starts a comment:
    drop REGEX     a line of a string that this matches leaves the row
    private GLOB   a word of these files (relative to the repo root) that no file git tracks holds, in its text or
                   its path, becomes hidden_name: a name that only a private source knows. A word that is a hex
                   number, such as dead, stays: the rows' bytes are written with such words
    deny REGEX     a string that still matches after the drops stops the pack
"""
import argparse
import base64
import gzip
import hashlib
import io
import json
import re
import secrets
import subprocess
import sys
from collections import Counter
from pathlib import Path

MAGIC = b"CPK1"  # the format tag; also the GCM associated data
KEY_BYTES = 32
NONCE_BYTES = 12
HEADER_BYTES = len(MAGIC) + NONCE_BYTES
BOX_MAGIC = b"CPB1"  # a box: this magic, the sender's one-time public key, then a seal() under the derived key
BOX_HEADER_BYTES = len(BOX_MAGIC) + KEY_BYTES
WORD = re.compile(r"\b[A-Za-z_]\w*", re.ASCII)
HEX = re.compile(r"[0-9A-Fa-f]+")
HIDDEN_NAME = "hidden_name"
SHOWN_HITS = 20  # the deny hits a refused pack prints


def read_rules(text: str) -> tuple[list[re.Pattern], list[str], list[re.Pattern]]:
    """The drop rules, the private globs and the deny rules of a rules file's TEXT. A rule keeps its spaces, trailing
    ones too."""
    rules = {"drop": [], "private": [], "deny": []}
    for number, line in enumerate(text.splitlines(), 1):
        if not line.strip() or line.lstrip().startswith("#"):
            continue
        kind, _, argument = line.partition(" ")
        if kind not in rules or not argument:
            raise ValueError(f"rules line {number}: want 'drop REGEX', 'private GLOB' or 'deny REGEX', got {line!r}")
        try:
            rules[kind].append(argument if kind == "private" else re.compile(argument))
        except re.error as error:
            raise ValueError(f"rules line {number}: {error}") from None
    return rules["drop"], rules["private"], rules["deny"]


def words(texts) -> set[str]:
    """The words of TEXTS that can be names: hex numbers such as e8 or dead are left out."""
    found = set()
    for text in texts:
        found.update(WORD.findall(text))
    return {word for word in found if not HEX.fullmatch(word)}


def git_output(*args, cwd: Path | None = None) -> str:
    """The stdout of git ARGS run in CWD; git's own error goes to stderr."""
    return subprocess.run(["git", *args], cwd=cwd, stdout=subprocess.PIPE, encoding="utf-8", check=True).stdout


def private_words(globs: list[str]) -> set[str]:
    """The words of the files that GLOBS name under the git repo's root that no file git tracks holds, in its text
    or its path."""
    root = Path(git_output("rev-parse", "--show-toplevel").strip())
    tracked = git_output("ls-files", "-z", cwd=root).split("\0")
    public = words((root / name).read_text(encoding="utf-8", errors="replace")
                   for name in tracked if (root / name).is_file()) | words(tracked)
    private = set()
    for pattern in globs:
        paths = [path for path in root.glob(pattern) if path.is_file()]
        if not paths:
            raise ValueError(f"private {pattern} names no file under {root}")
        private |= words(path.read_text(encoding="utf-8", errors="replace") for path in paths)
    return private - public


def scrub(value, drops: list[re.Pattern], hidden: set[str], counts: Counter):
    """VALUE with drop_lines and hide applied to each string in it."""
    if isinstance(value, str):
        return hide(drop_lines(value, drops, counts), hidden, counts)
    if isinstance(value, list):
        return [scrub(item, drops, hidden, counts) for item in value]
    if isinstance(value, dict):
        return {key: scrub(item, drops, hidden, counts) for key, item in value.items()}
    return value


def drop_lines(text: str, drops: list[re.Pattern], counts: Counter) -> str:
    """TEXT without the lines that a rule of DROPS matches; COUNTS gets one per dropped line, under its rule."""
    kept = []
    for line in text.split("\n"):
        rule = next((rule for rule in drops if rule.search(line)), None)
        if rule:
            counts[f"lines dropped by {rule.pattern!r}"] += 1
        else:
            kept.append(line)
    return "\n".join(kept)


def hide(text: str, hidden: set[str], counts: Counter) -> str:
    """TEXT with each word of HIDDEN turned into HIDDEN_NAME; COUNTS gets one per word."""
    if not hidden:
        return text

    def rename(match: re.Match) -> str:
        if match.group(0) not in hidden:
            return match.group(0)
        counts["private words hidden"] += 1
        return HIDDEN_NAME

    return WORD.sub(rename, text)


def strings(value):
    """Every string in VALUE, at any depth of its lists and dict values."""
    if isinstance(value, str):
        yield value
    elif isinstance(value, (list, dict)):
        items = value.values() if isinstance(value, dict) else value
        for item in items:
            yield from strings(item)


def deny_hits(value, denies: list[re.Pattern]) -> list[str]:
    """The deny rules that match a string in VALUE, each with the text it matched."""
    hits = []
    for text in strings(value):
        for rule in denies:
            match = rule.search(text)
            if match:
                hits.append(f"{rule.pattern}: {match.group(0)!r}")
    return hits


def encode_key(key: bytes) -> str:
    """The base64 text of KEY, as a key file holds it."""
    return base64.b64encode(key).decode("ascii")


def decode_key(text: str) -> bytes:
    """The key bytes of a key's base64 TEXT; raises ValueError unless it is valid base64 of KEY_BYTES bytes."""
    key = base64.b64decode(text.strip(), validate=True)
    if len(key) != KEY_BYTES:
        raise ValueError(f"the key is {len(key)} bytes, not {KEY_BYTES}")
    return key


def seal(data: bytes, key: bytes) -> bytes:
    """DATA encrypted with KEY: magic, nonce, then the ciphertext with its tag."""
    from cryptography.hazmat.primitives.ciphers.aead import AESGCM  # here, not at the top: it needs .venv's packages

    nonce = secrets.token_bytes(NONCE_BYTES)
    return MAGIC + nonce + AESGCM(key).encrypt(nonce, data, MAGIC)


def unseal(blob: bytes, key: bytes) -> bytes:
    """The data that seal() encrypted into BLOB; raises ValueError if the key is wrong or the blob changed."""
    from cryptography.exceptions import InvalidTag
    from cryptography.hazmat.primitives.ciphers.aead import AESGCM

    if not blob.startswith(MAGIC):
        raise ValueError("not a cloudpack file")
    try:
        return AESGCM(key).decrypt(blob[len(MAGIC):HEADER_BYTES], blob[HEADER_BYTES:], MAGIC)
    except InvalidTag:
        raise ValueError("the key is wrong or the pack changed") from None


def new_box_keys() -> tuple[bytes, bytes]:
    """A new X25519 private key and its public key, raw."""
    from cryptography.hazmat.primitives import serialization
    from cryptography.hazmat.primitives.asymmetric.x25519 import X25519PrivateKey

    private = X25519PrivateKey.generate()
    raw = private.private_bytes(serialization.Encoding.Raw, serialization.PrivateFormat.Raw,
                                serialization.NoEncryption())
    return raw, raw_public(private)


def box_key(shared: bytes, sender_public: bytes, recipient_public: bytes) -> bytes:
    """The AES key of a box: HKDF-SHA256 of the X25519 SHARED secret, bound to both public keys and BOX_MAGIC."""
    from cryptography.hazmat.primitives import hashes
    from cryptography.hazmat.primitives.kdf.hkdf import HKDF

    info = BOX_MAGIC + sender_public + recipient_public
    return HKDF(algorithm=hashes.SHA256(), length=KEY_BYTES, salt=None, info=info).derive(shared)


def raw_public(private) -> bytes:
    """The raw 32 bytes of the public key of an X25519 PRIVATE key."""
    from cryptography.hazmat.primitives import serialization

    return private.public_key().public_bytes(serialization.Encoding.Raw, serialization.PublicFormat.Raw)


def seal_box(data: bytes, public: bytes) -> bytes:
    """DATA encrypted for the holder of the private key of PUBLIC, with a one-time sender key."""
    from cryptography.hazmat.primitives.asymmetric.x25519 import X25519PrivateKey, X25519PublicKey

    sender = X25519PrivateKey.generate()
    sender_public = raw_public(sender)
    shared = sender.exchange(X25519PublicKey.from_public_bytes(public))
    return BOX_MAGIC + sender_public + seal(data, box_key(shared, sender_public, public))


def unseal_box(blob: bytes, private: bytes) -> bytes:
    """The data that seal_box() encrypted into BLOB; raises ValueError if the key is wrong or the box changed."""
    from cryptography.hazmat.primitives.asymmetric.x25519 import X25519PrivateKey, X25519PublicKey

    if not blob.startswith(BOX_MAGIC):
        raise ValueError("not a cloudpack box")
    private_key = X25519PrivateKey.from_private_bytes(private)
    sender_public = blob[len(BOX_MAGIC):BOX_HEADER_BYTES]
    shared = private_key.exchange(X25519PublicKey.from_public_bytes(sender_public))
    return unseal(blob[BOX_HEADER_BYTES:], box_key(shared, sender_public, raw_public(private_key)))


def pack_rows(sets: dict, meta: dict, rules_text: str, key: bytes) -> tuple[bytes, Counter]:
    """SETS ({name: rows}) scrubbed by the rules, checked, and sealed with KEY together with META; and the counts of
    what the rules removed. The plain text is a header line {"meta": META, "sets": {name: row count}}, then the rows
    of each set in order, one JSON line each."""
    drops, globs, denies = read_rules(rules_text)
    hidden = private_words(globs) if globs else set()
    counts = Counter()
    scrubbed = {name: [scrub(row, drops, hidden, counts) for row in rows] for name, rows in sets.items()}
    hits = [f"{name} row {index}: {hit}" for name, rows in scrubbed.items()
            for index, row in enumerate(rows) for hit in deny_hits(row, denies)]
    if hits:
        raise ValueError(f"deny rules still match {len(hits)} times; the first {SHOWN_HITS}:\n"
                         + "\n".join(hits[:SHOWN_HITS]))
    header = {"meta": meta, "sets": {name: len(rows) for name, rows in scrubbed.items()}}
    lines = [header] + [row for rows in scrubbed.values() for row in rows]
    text = "".join(json.dumps(line, ensure_ascii=False) + "\n" for line in lines)
    return seal(gzip.compress(text.encode("utf-8")), key), counts


def load(blob: bytes, key: bytes) -> tuple[dict, dict]:
    """(meta, {set name: rows}) of a pack, in memory only. Rows split at b"\\n" only: a row may hold U+2028 or \\x85,
    which str.splitlines() would split at."""
    with gzip.GzipFile(fileobj=io.BytesIO(unseal(blob, key))) as lines:
        header, *rows = [json.loads(line) for line in lines]
    sets, start = {}, 0
    for name, count in header["sets"].items():
        sets[name] = rows[start:start + count]
        start += count
    return header["meta"], sets


def write_new(path: Path, text: str) -> None:
    """Write TEXT to a new file at PATH; raises ValueError if PATH exists, so no command overwrites a key."""
    try:
        with open(path, "x", encoding="ascii") as file:
            file.write(text)
    except FileExistsError:
        raise ValueError(f"{path} exists; a key is never overwritten") from None


def keygen(args):
    write_new(args.key, encode_key(secrets.token_bytes(KEY_BYTES)))
    print(f"wrote a new key to {args.key}")


def boxgen(args):
    private, public = new_box_keys()
    write_new(args.key, encode_key(private))
    args.public.write_text(encode_key(public) + "\n")
    print(f"wrote a new private key to {args.key} and its public key to {args.public}")


def open_folder(args):
    """Every box (*.sealed) under FOLDER, opened with the private key, and with --pack-key every *.pk file too, written
    to OUT at the same relative path without the suffix."""
    private = decode_key(args.key.read_text())
    pack_key = decode_key(args.pack_key.read_text()) if args.pack_key else None
    opened = skipped = 0
    for path in sorted(args.folder.rglob("*")):
        if path.suffix == ".pk" and not pack_key:
            skipped += 1
            continue
        if path.suffix not in (".sealed", ".pk"):
            continue
        try:
            data = (unseal_box(path.read_bytes(), private) if path.suffix == ".sealed"
                    else unseal(path.read_bytes(), pack_key))
        except ValueError as error:
            raise ValueError(f"{path}: {error}") from None
        target = args.out / path.relative_to(args.folder).with_suffix("")
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_bytes(data)
        opened += 1
    note = f"; skipped {skipped} .pk files: no --pack-key" if skipped else ""
    print(f"opened {opened} files into {args.out}{note}")


def read_jsonl(path: Path) -> list:
    """The rows of a JSONL file, split at "\\n" only (see load)."""
    rows = []
    for number, line in enumerate(path.read_text(encoding="utf-8").split("\n"), 1):
        if not line.strip():
            continue
        try:
            rows.append(json.loads(line))
        except json.JSONDecodeError as error:
            raise ValueError(f"{path} line {number}: {error}") from None
    return rows


def sizes(sets: dict) -> str:
    """The row count of each set, as 'train 5, dev 2'."""
    return ", ".join(f"{name} {len(rows)}" for name, rows in sets.items())


def pack(args):
    sets = {}
    for item in args.set:
        name, _, path = item.partition("=")
        if not path or name in sets:
            sys.exit(f"--set takes NAME=FILE with a new name each time, not {item!r}")
        sets[name] = read_jsonl(Path(path))
    meta = {"manifest_sha256": hashlib.sha256(args.manifest.read_bytes()).hexdigest()} if args.manifest else {}
    blob, counts = pack_rows(sets, meta, args.rules.read_text(encoding="utf-8"), decode_key(args.key.read_text()))
    args.out.write_bytes(blob)
    print(f"rows: {sizes(sets)}; {len(blob)} bytes to {args.out}")
    for label, count in counts.most_common():
        print(f"  {count} {label}")


def check(args):
    meta, sets = load(args.pack.read_bytes(), decode_key(args.key.read_text()))
    print(f"{args.pack}: rows {sizes(sets)} decrypt with {args.key.name}; meta {json.dumps(meta)}")


def main():
    parser = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    commands = parser.add_subparsers(required=True)
    command = commands.add_parser("keygen", help="write a new key file")
    command.add_argument("key", type=Path)
    command.set_defaults(run=keygen)
    command = commands.add_parser("boxgen", help="write a new private key file and its public key file")
    command.add_argument("key", type=Path)
    command.add_argument("--public", type=Path, required=True)
    command.set_defaults(run=boxgen)
    command = commands.add_parser("open", help="decrypt a pulled output folder")
    command.add_argument("folder", type=Path)
    command.add_argument("--key", type=Path, required=True, help="the private key file of boxgen")
    command.add_argument("--pack-key", type=Path, help="the pack key file, to open *.pk files too")
    command.add_argument("--out", type=Path, required=True)
    command.set_defaults(run=open_folder)
    command = commands.add_parser("pack", help="scrub, check and encrypt JSONL files into one pack; run it inside "
                                                "the repo")
    command.add_argument("out", type=Path)
    command.add_argument("--set", action="append", required=True, help="NAME=FILE, a JSONL file of rows; repeat it")
    command.add_argument("--manifest", type=Path, help="a file whose sha256 goes into the pack's meta")
    command.add_argument("--rules", type=Path, required=True)
    command.add_argument("--key", type=Path, required=True)
    command.set_defaults(run=pack)
    command = commands.add_parser("check", help="decrypt a pack in memory and count its rows")
    command.add_argument("pack", type=Path)
    command.add_argument("--key", type=Path, required=True)
    command.set_defaults(run=check)
    args = parser.parse_args()
    try:
        args.run(args)
    except (ValueError, OSError, subprocess.CalledProcessError) as error:
        sys.exit(str(error))


if __name__ == "__main__":
    # here, not at the top: a trainer imports this module without the repo's check.py; renamed, as `check` is a command
    import check as repo_check

    repo_check.rerun_in_venv(__file__)
    main()
