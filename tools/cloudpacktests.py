"""Checks for tools/cloudpack.py: the rules file, the drops, the numbered private words and their way back, the deny
stop, the round trip, line separators inside a row, the refusals of a changed pack or box and of a wrong key, and the
command line."""
import base64
import hashlib
import json
import secrets
import subprocess
import sys
import tempfile
from collections import Counter
from pathlib import Path
from unittest import mock

import cloudpack
import osutil

HERE = Path(__file__).resolve().parent
RULES = "# test rules\ndrop ^note: \ndeny \\.obj\\b\n"
ROW = {"messages": [{"role": "user", "content": "file: a.cpp\nnote: object a.obj, source line 3\nmov eax, 1"},
                    {"role": "assistant", "content": "int a;"}]}


def new_key() -> bytes:
    return secrets.token_bytes(cloudpack.KEY_BYTES)


def flip(blob: bytes, index: int) -> bytes:
    """BLOB with the low bit of its byte at INDEX flipped."""
    changed = bytearray(blob)
    changed[index] ^= 1
    return bytes(changed)


def refusal(function, *args) -> str:
    """The message of the ValueError that FUNCTION raises for ARGS, or 'accepted'."""
    try:
        function(*args)
    except ValueError as error:
        return str(error)
    return "accepted"


def run_cloudpack(cwd: Path, *args) -> subprocess.CompletedProcess:
    """cloudpack.py run with ARGS in the folder CWD."""
    return subprocess.run([sys.executable, "-X", "utf8", str(HERE / "cloudpack.py"), *map(str, args)],
                          capture_output=True, text=True, cwd=cwd)


def check_rules() -> list[str]:
    """A rules file skips comments and blank lines, and names the line of a rule without an argument, of an unknown
    kind and of a bad regex."""
    drops, globs, denies = cloudpack.read_rules("# a comment\n\ndrop ^a \nprivate t/*.tsv\ndeny b\n")
    failures = [] if ([rule.pattern for rule in drops], globs, [rule.pattern for rule in denies]) == (
        ["^a "], ["t/*.tsv"], ["b"]) else [f"rules read as {drops}, {globs}, {denies}"]
    for text in ("drop", "keep x", "deny ("):
        got = refusal(cloudpack.read_rules, f"# x\n{text}\n")
        if not got.startswith("rules line 2: "):
            failures.append(f"rule {text!r} gives {got!r}")
    return failures


def check_drops() -> list[str]:
    """A drop rule removes only the lines it matches, in nested strings, and counts them; a rule keeps its spaces."""
    key = new_key()
    blob, counts, _ = cloudpack.pack_rows({"train": [ROW]}, {}, RULES, key)
    rows = cloudpack.load(blob, key)[1]["train"]
    wanted = [{"messages": [{"role": "user", "content": "file: a.cpp\nmov eax, 1"},
                            {"role": "assistant", "content": "int a;"}]}]
    failures = [] if rows == wanted else [f"round trip gives {rows}, not {wanted}"]
    return failures + ([] if counts == {"lines dropped by '^note: '": 1} else [f"drop counts are {dict(counts)}"])


def check_hidden() -> list[str]:
    """Each private word gets its own placeholder, numbered by first appearance across nested strings, the same one
    each time it comes back; a longer word that holds it stays. unhide turns them back and leaves a placeholder the
    row never had."""
    counts, names = Counter(), {}
    value = {"a": ["mov eax, [0x10] ; secret_name+0x4", "secret_names stay"], "b": "other_secret(secret_name)"}
    got = cloudpack.scrub(value, [], {"secret_name", "other_secret"}, counts, names)
    wanted = {"a": ["mov eax, [0x10] ; hidden_1+0x4", "secret_names stay"], "b": "hidden_2(hidden_1)"}
    failures = [] if got == wanted else [f"hiding gives {got}"]
    if counts != {"private words hidden": 3}:
        failures.append(f"hide counts are {dict(counts)}")
    back = cloudpack.unhide("hidden_2(hidden_1, hidden_3) hidden_1x", {p: w for w, p in names.items()})
    if back != "other_secret(secret_name, hidden_3) hidden_1x":
        failures.append(f"unhide gives {back!r}")
    return failures


def check_placeholders() -> list[str]:
    """pack_rows numbers each row on its own and returns each row's placeholders."""
    key = new_key()
    rows = [{"text": "b a b"}, {"text": "a"}]
    with mock.patch.object(cloudpack, "private_words", lambda globs: {"a", "b"}):
        blob, _, placeholders = cloudpack.pack_rows({"train": rows}, {}, "private t/*\n", key)
    got = (cloudpack.load(blob, key)[1]["train"], placeholders)
    wanted = ([{"text": "hidden_1 hidden_2 hidden_1"}, {"text": "hidden_1"}],
              {"train": [{"hidden_1": "b", "hidden_2": "a"}, {"hidden_1": "a"}]})
    return [] if got == wanted else [f"pack_rows placeholders give {got}, not {wanted}"]


def check_words() -> list[str]:
    """A hex number such as e8 or dead, or the x of 0x10, is never a word."""
    found = cloudpack.words(["e851b80900 call x_y _z 0x4000001 dead"])
    return [] if found == {"call", "x_y", "_z"} else [f"words are {found}"]


def check_separators() -> list[str]:
    """A row that holds U+2028, U+2029 or \\x85 comes back whole."""
    key = new_key()
    row = {"text": "a b c\x85d"}
    blob, _, _ = cloudpack.pack_rows({"train": [row, row]}, {}, "", key)
    rows = cloudpack.load(blob, key)[1]["train"]
    return [] if rows == [row, row] else [f"separators round trip gives {rows}"]


def check_sets() -> list[str]:
    """Two sets and the meta come back apart and in order, an empty set included."""
    key = new_key()
    sets = {"train": [{"i": 0}, {"i": 1}], "empty": [], "dev": [{"i": 2}]}
    meta = {"manifest_sha256": "ab" * 32}
    got = cloudpack.load(cloudpack.pack_rows(sets, meta, "", key)[0], key)
    return [] if got == (meta, sets) and list(got[1]) == list(sets) else [f"sets round trip gives {got}"]


def check_deny() -> list[str]:
    """A deny rule that still matches after the drops stops the pack and the error gives the count."""
    got = refusal(cloudpack.pack_rows, {"dev": [{"text": "call foo ; from foo.obj"}]}, {}, RULES, new_key())
    return [] if "match 1 times" in got and "dev row 0: " in got else [f"deny error: {got}"]


def check_refusals() -> list[str]:
    """load refuses a pack with a changed nonce, ciphertext or tag byte, a changed magic or another key, and
    decode_key refuses a key of 16 bytes."""
    key = new_key()
    blob, _, _ = cloudpack.pack_rows({"train": [ROW]}, {}, RULES, key)
    changed = "the key is wrong or the pack changed"
    cases = [("a changed nonce", flip(blob, len(cloudpack.MAGIC)), key, changed),
             ("a changed ciphertext", flip(blob, cloudpack.HEADER_BYTES), key, changed),
             ("a changed tag", flip(blob, -1), key, changed),
             ("a changed magic", b"CPK2" + blob[len(cloudpack.MAGIC):], key, "not a cloudpack file"),
             ("another key", blob, new_key(), changed)]
    failures = []
    for name, data, use, wanted in cases:
        got = refusal(cloudpack.load, data, use)
        if got != wanted:
            failures.append(f"load with {name} gives {got!r}")
    got = refusal(cloudpack.decode_key, base64.b64encode(secrets.token_bytes(16)).decode("ascii"))
    return failures + ([] if got == "the key is 16 bytes, not 32" else [f"a 16-byte key gives {got!r}"])


def check_boxes() -> list[str]:
    """A box opens with its private key, two boxes of the same data have different sender keys, and unseal_box
    refuses a changed byte, a changed sender key, a changed magic, a cut box and another private key."""
    private, public = cloudpack.new_box_keys()
    data = b"canary \x00 bytes"
    box, again = cloudpack.seal_box(data, public), cloudpack.seal_box(data, public)
    failures = [] if cloudpack.unseal_box(box, private) == data else ["a box does not open to its data"]
    sender = slice(len(cloudpack.BOX_MAGIC), cloudpack.BOX_HEADER_BYTES)
    failures += ["two boxes have the same sender key"] if box[sender] == again[sender] else []
    failures += ["a box holds its data in plain text"] if data in box else []
    cases = [("a changed byte", flip(box, -1), private), ("a changed sender key", flip(box, sender.start), private),
             ("a changed magic", b"CPB2" + box[sender.start:], private), ("a cut box", box[:10], private),
             ("another private key", box, cloudpack.new_box_keys()[0])]
    for name, blob, key in cases:
        if refusal(cloudpack.unseal_box, blob, key) == "accepted":
            failures.append(f"unseal_box accepted {name}")
    return failures


def check_key_commands() -> list[str]:
    """keygen and boxgen write keys that work, and refuse to overwrite a key."""
    failures = []
    with tempfile.TemporaryDirectory() as temp:
        folder = Path(temp)
        for command in (["keygen", "pack.key"], ["boxgen", "box.key", "--public", "box.pub"]):
            first = run_cloudpack(folder, *command)
            written = (folder / command[1]).read_text() if first.returncode == 0 else ""
            again = run_cloudpack(folder, *command)
            if first.returncode != 0 or again.returncode == 0 or (folder / command[1]).read_text() != written:
                failures.append(f"{command[0]} exits {first.returncode}, then {again.returncode} on its own key")
        if failures:
            return failures
        key = cloudpack.decode_key((folder / "pack.key").read_text())
        private = cloudpack.decode_key((folder / "box.key").read_text())
        box = cloudpack.seal_box(b"x", cloudpack.decode_key((folder / "box.pub").read_text()))
        if cloudpack.unseal(cloudpack.seal(b"x", key), key) != b"x" or cloudpack.unseal_box(box, private) != b"x":
            failures.append("the keys of keygen and boxgen do not seal and open")
    return failures


def check_pack_command() -> list[str]:
    """pack in a git repo hides the words of a private file that no tracked file holds and puts the manifest's
    sha256 in the meta, and check reads the pack, as CAMPAIGN.md runs them."""
    with osutil.foreign_repository(), tempfile.TemporaryDirectory() as temp:
        folder = Path(temp)
        osutil.git(folder, "init", "--quiet")
        (folder / "public.txt").write_text("public_name", encoding="utf-8")
        osutil.git(folder, "add", "public.txt")
        (folder / "private.txt").write_text("public_name secret_name", encoding="utf-8")
        (folder / "rules.txt").write_text(RULES + "private private.txt\n", encoding="utf-8")
        row = {"text": "call secret_name ; public_name"}
        (folder / "train.jsonl").write_text(json.dumps(row) + "\n", encoding="utf-8")
        (folder / "manifest.json").write_text("{}", encoding="utf-8")
        key = new_key()
        (folder / "pack.key").write_text(cloudpack.encode_key(key))
        packed = run_cloudpack(folder, "pack", "data.bin", "--set", "train=train.jsonl", "--manifest", "manifest.json",
                               "--rules", "rules.txt", "--key", "pack.key")
        if packed.returncode != 0:
            return [f"cloudpack pack exits {packed.returncode}: {packed.stderr[-300:]}"]
        got = cloudpack.load((folder / "data.bin").read_bytes(), key)
        wanted = ({"manifest_sha256": hashlib.sha256(b"{}").hexdigest()},
                  {"train": [{"text": "call hidden_1 ; public_name"}]})
        failures = [] if got == wanted else [f"pack in a git repo gives {got}"]
        checked = run_cloudpack(folder, "check", "data.bin", "--key", "pack.key")
        return failures + ([] if "rows train 1 " in checked.stdout else [f"cloudpack check prints {checked.stdout!r}"])


def check_open_command() -> list[str]:
    """open writes each box of a folder back in plain text, and each .pk file with --pack-key; without it, it counts
    the .pk files it skips."""
    private, public = cloudpack.new_box_keys()
    key = new_key()
    failures = []
    with tempfile.TemporaryDirectory() as temp:
        folder = Path(temp)
        (folder / "pulled" / "resume").mkdir(parents=True)
        (folder / "pulled" / "a.json.sealed").write_bytes(cloudpack.seal_box(b"a", public))
        (folder / "pulled" / "resume" / "b.bin.pk").write_bytes(cloudpack.seal(b"b", key))
        (folder / "box.key").write_text(cloudpack.encode_key(private))
        (folder / "pack.key").write_text(cloudpack.encode_key(key))
        boxes = run_cloudpack(folder, "open", "pulled", "--key", "box.key", "--out", "boxes")
        if "skipped 1 .pk files" not in boxes.stdout or (folder / "boxes" / "a.json").read_bytes() != b"a":
            failures.append(f"open without --pack-key prints {boxes.stdout!r} {boxes.stderr[-300:]}")
        both = run_cloudpack(folder, "open", "pulled", "--key", "box.key", "--pack-key", "pack.key", "--out", "both")
        if both.returncode != 0 or (folder / "both" / "resume" / "b.bin").read_bytes() != b"b":
            failures.append(f"open with --pack-key exits {both.returncode}: {both.stderr[-300:]}")
    return failures


def run() -> list[str]:
    """Every check of cloudpack.py: the failures of all."""
    return (check_rules() + check_drops() + check_hidden() + check_placeholders() + check_words() + check_separators() + check_sets()
            + check_deny() + check_refusals() + check_boxes() + check_key_commands() + check_pack_command()
            + check_open_command())


if __name__ == "__main__":
    failures = run()
    print("\n".join(failures) or "cloudpack: all checks passed")
    sys.exit(1 if failures else 0)
