"""The chat client of tools/llm.py: any server with an OpenAI-style /chat/completions.

`llm.py init` writes the config file, llm.json (git-ignored), with these keys:

  base_url       the URL before /chat/completions, such as http://127.0.0.1:8080/v1
  model          a model name from the server's /models
  api_key_env    the environment variable that holds the key, or "" when the server needs none
  temperature    the temperature of a try that does not repeat an earlier one
  max_tokens     the reply limit of a try
  seed           true when the server repeats a reply for the same seed
  timeout        seconds to wait for one reply
  extra_body     fields to add to every request: a null value removes a field
  think_on       fields to add to a thinking try; {} turns thinking off
  think_off      fields to add to every other try
  start          a command line that starts the server when nothing answers, or ""
  start_timeout  seconds to wait for a server it started: a first model download takes a while
  tables, drafts, context   folders for `check.py decls` and `check.py dossier`, or ""
  shared_context the context that the server's slots share (llama.cpp -kvu: its -c), or 0: see reserved

A server that start started stops when the harness exits. One that already ran keeps
running. Standard library only.
"""

import atexit
import contextlib
import hashlib
import http.client
import json
import os
import random
import shutil
import subprocess
import sys
import tempfile
import time
import urllib.error
import urllib.request
from pathlib import Path
from typing import NamedTuple

import osutil

DEFAULTS = {"base_url": "", "model": "", "api_key_env": "", "temperature": 0.6, "max_tokens": 2048, "seed": False,
            "timeout": 900, "extra_body": {}, "think_on": {}, "think_off": {}, "start": "", "start_timeout": 900,
            "tables": "", "drafts": "", "context": "", "shared_context": 0}
PRESETS = (("llama.cpp", "http://127.0.0.1:8080/v1"), ("Ollama", "http://127.0.0.1:11434/v1"),
           ("LM Studio", "http://127.0.0.1:1234/v1"), ("vLLM", "http://127.0.0.1:8000/v1"))
# (think_on, think_off) pairs that init tries in this order.
THINK_SWITCHES = (
    # llama.cpp, vLLM and SGLang pass these to Qwen-style chat templates.
    ({"chat_template_kwargs": {"enable_thinking": True, "reasoning_effort": "medium"}},
     {"chat_template_kwargs": {"enable_thinking": False}}),
    # Ollama and most hosted APIs.
    ({"reasoning_effort": "medium"}, {"reasoning_effort": "none"}),
    # OpenRouter.
    ({"reasoning": {"enabled": True}}, {"reasoning": {"enabled": False}}),
)
THINK_MAX_TOKENS = 12000  # thinking counts toward max_tokens
PROBE_MAX_TOKENS = 1024  # enough to see whether a reply starts with thinking
REFUSED = (400, 422)  # the status of a request with a field the server does not take
POLL_SECONDS = 2
# llama.cpp's answer when its slots share one context and the requests running together filled it. It fails them all
# at once, so each waits a random time before it asks again: asked together, they would fill it again.
CONTEXT_FULL = "Context size has been exceeded"
# llama.cpp's answer when its draft model fails one of the replies that decode together. The same request goes through
# when asked again.
DRAFT_FAILED = "speculative batch index"
FULL_RETRIES, FULL_WAIT_SECONDS = 10, (15, 120)
BUDGET_POLL_SECONDS = 1


class ServerError(Exception):
    """The server answered with an error (status is its HTTP status), or not at all (status 0)."""

    def __init__(self, message: str, status: int = 0):
        super().__init__(message)
        self.status = status


class Reply(NamedTuple):
    text: str  # the answer, without its thinking
    reasoning: str
    usage: dict  # prompt_tokens and completion_tokens, 0 when the server does not say
    finish: str  # finish_reason: "length" means the reply hit its max_tokens


def load(path: Path) -> dict:
    if not path.exists():
        sys.exit(f"{path} is missing. Run: python tools/llm.py init")
    config = json.loads(path.read_text(encoding="utf-8"))
    unknown = set(config) - set(DEFAULTS)
    if unknown:
        sys.exit(f"{path}: unknown keys {', '.join(sorted(unknown))}. tools/llmclient.py lists the keys.")
    return {**DEFAULTS, **config}


def merged(body: dict, extra: dict) -> dict:
    """BODY with the fields of EXTRA: a None value removes the field."""
    out = dict(body)
    for key, value in extra.items():
        if value is None:
            out.pop(key, None)
        else:
            out[key] = value
    return out


def call(config: dict, path: str, body: dict | None = None, timeout: float | None = None, read=json.load):
    """What READ makes of the server's answer at base_url + path, by default its JSON: a POST of BODY, or a GET
    without one."""
    url = config["base_url"].rstrip("/") + path
    headers = {"Content-Type": "application/json"}
    key = os.environ.get(config["api_key_env"]) if config["api_key_env"] else None
    if key:
        headers["Authorization"] = f"Bearer {key}"
    data = None if body is None else json.dumps(body).encode("utf-8")
    request = urllib.request.Request(url, data=data, headers=headers)
    try:
        with urllib.request.urlopen(request, timeout=timeout or config["timeout"]) as response:
            return read(response)
    except urllib.error.HTTPError as e:
        raise ServerError(f"{url} answered {e.code}: {e.read().decode('utf-8', 'replace')[:500]}", e.code) from e
    except (urllib.error.URLError, http.client.HTTPException, OSError) as e:  # HTTPException: a reply cut short
        raise ServerError(f"{url} failed: {e}") from e
    except json.JSONDecodeError as e:
        raise ServerError(f"{url} answered something other than JSON: {e}") from e


def text_of(content) -> str:
    """A message's content as text: Mistral sends a list of parts."""
    if isinstance(content, list):
        return "".join(part.get("text", "") for part in content if part.get("type") == "text")
    return content or ""


def events(lines, on_text, timeout: float) -> dict:
    """The server-sent events of a streamed answer, as the JSON of an answer without a stream. ON_TEXT, when given,
    gets each piece of the reply as it comes: ("reasoning" or "content", text)."""
    deadline = time.time() + timeout
    parts = {"reasoning": [], "content": []}
    finish, usage, ended = "", {}, False
    for raw in lines:
        if time.time() > deadline:
            raise ServerError(f"the reply took more than {timeout}s (timeout)")
        field, _, data = raw.decode("utf-8").strip().partition(":")
        data = data.strip()
        if field not in ("data", "error") or not data:
            continue
        if data == "[DONE]":
            ended = True
            break
        chunk = json.loads(data)
        error = chunk if field == "error" else chunk.get("error")  # llama.cpp sends an error after the start either way
        if error:
            code = error.get("code") if isinstance(error, dict) else None
            raise ServerError(f"the server failed during the reply: {data[:500]}", code if isinstance(code, int) else 0)
        usage = chunk.get("usage") or usage
        for choice in chunk.get("choices") or []:
            delta = choice.get("delta") or {}
            pieces = (("reasoning", delta.get("reasoning_content") or delta.get("reasoning")),
                      ("content", text_of(delta.get("content"))))
            for kind, text in pieces:
                if text:
                    parts[kind].append(text)
                    if on_text:
                        on_text(kind, text)
            finish = choice.get("finish_reason") or finish
    if not (ended or finish):  # the server closed the connection between two events
        raise ServerError("the server closed the stream before the reply ended")
    message = {"content": "".join(parts["content"]), "reasoning_content": "".join(parts["reasoning"])}
    return {"choices": [{"message": message, "finish_reason": finish}], "usage": usage}


def parse(data: dict) -> Reply:
    try:
        choice = data["choices"][0]
        message = choice["message"]
    except (KeyError, IndexError, TypeError):
        raise ServerError(f"the answer holds no reply: {json.dumps(data)[:500]}") from None
    content = text_of(message.get("content"))
    reasoning = message.get("reasoning_content") or message.get("reasoning") or ""
    if "</think>" in content:  # inline thinking: some templates send the opening tag themselves
        thought, _, content = content.rpartition("</think>")
        reasoning = reasoning or thought.replace("<think>", "").strip()
        content = content.lstrip()
    usage = data.get("usage") or {}
    counts = {key: usage.get(key) or 0 for key in ("prompt_tokens", "completion_tokens")}
    return Reply(content, reasoning, counts, choice.get("finish_reason") or "")


def chat(config: dict, messages: list[dict], temperature: float, thinking: bool, seed: int | None,
         on_text=None) -> Reply:
    """The reply, asked as a stream: ON_TEXT, when given, gets each piece as it comes (see events), and
    ("restart", "") when a full context or a failed draft makes it ask again."""
    body = {"model": config["model"], "messages": messages, "temperature": temperature,
            "max_tokens": config["max_tokens"], "stream": True, "stream_options": {"include_usage": True}}
    if seed is not None and config["seed"]:
        body["seed"] = seed
    body = merged(body, config["extra_body"])
    body = merged(body, config["think_on"] if thinking else config["think_off"])
    for retry in range(FULL_RETRIES + 1):
        try:
            with reserved(config, body):
                return parse(call(config, "/chat/completions", body,
                                  read=lambda response: events(response, on_text, config["timeout"])))
        except ServerError as e:
            asks_again = CONTEXT_FULL in str(e) or DRAFT_FAILED in str(e)
            if retry == FULL_RETRIES or e.status != 500 or not asks_again:
                raise
            if on_text:
                on_text("restart", "")
            time.sleep(random.uniform(*FULL_WAIT_SECONDS))


# The shared context


@contextlib.contextmanager
def reserved(config: dict, body: dict):
    """Hold room for BODY's prompt and max_tokens in the context that the server's slots share, while the block runs.
    llama.cpp fails every running reply when they fill that context together, so the clients of one server note
    their room in one file, and a request starts once may_start says so. Nothing waits when shared_context is 0."""
    if not config["shared_context"]:
        yield
        return
    path = ledger_path(config)
    key = f"{os.getpid()}:{time.time_ns()}"
    tokens = prompt_tokens(config, body) + body["max_tokens"]
    try:
        with ledger(path) as requests:
            requests[key] = {"pid": os.getpid(), "tokens": tokens, "since": time.time(), "running": False}
        while not try_start(path, key, config["shared_context"]):
            time.sleep(BUDGET_POLL_SECONDS)
        yield
    finally:
        with ledger(path) as requests:
            requests.pop(key, None)


def may_start(requests: dict, key: str, total: int) -> bool:
    """Whether request KEY may start: no request waited longer, and its tokens fit in TOTAL beside those of the
    running ones, or none runs. A request that needs more than TOTAL thus runs alone."""
    me = requests[key]
    running = [r["tokens"] for r in requests.values() if r["running"]]
    waited_longer = any(not r["running"] and r["since"] < me["since"] for r in requests.values())
    return not waited_longer and (not running or sum(running) + me["tokens"] <= total)


def try_start(path: Path, key: str, total: int) -> bool:
    """Mark request KEY running, when it may start."""
    with ledger(path) as requests:
        if not may_start(requests, key, total):
            return False
        requests[key]["running"] = True
        return True


@contextlib.contextmanager
def ledger(path: Path):
    """The requests noted in PATH, by key, without those of processes that ended. The block may change them."""
    with osutil.locked(path.with_suffix(".lock")):
        requests = json.loads(path.read_text(encoding="utf-8")) if path.exists() else {}
        requests = {key: r for key, r in requests.items() if osutil.alive(r["pid"])}
        yield requests
        osutil.write_whole(path, json.dumps(requests))  # a client stopped while it writes leaves the old file whole


def ledger_path(config: dict) -> Path:
    """The file where the clients of the server at base_url note their requests."""
    name = hashlib.sha256(config["base_url"].encode("utf-8")).hexdigest()[:12]
    return Path(tempfile.gettempdir()) / f"llmclient-{name}.json"


def prompt_tokens(config: dict, body: dict) -> int:
    """The tokens of BODY's prompt, from llama.cpp's chat template and tokenizer, which it serves beside /v1."""
    root = {**config, "base_url": config["base_url"].rstrip("/").removesuffix("/v1")}
    prompt = call(root, "/apply-template", body)["prompt"]
    return len(call(root, "/tokenize", {"content": prompt, "add_special": True})["tokens"])


# The server


def models(config: dict) -> list[str]:
    """The model names the server lists. Raises ServerError when it does not answer, or not yet."""
    data = call(config, "/models", timeout=10)
    return [m["id"] for m in data.get("data", [])]


def ensure_server(config: dict, log: Path) -> None:
    """Return once the server lists its models: start it with config["start"] when nothing answers."""
    try:
        models(config)
        return
    except ServerError as e:
        if e.status or not config["start"]:
            sys.exit(f"{e}\n{no_server_hint(config)}")
    log.parent.mkdir(parents=True, exist_ok=True)
    print(f"Starting the server: {config['start']}\n  (its output goes to {log})", flush=True)
    with open(log, "w", encoding="utf-8") as out:
        process = subprocess.Popen(config["start"], shell=True, stdout=out, stderr=subprocess.STDOUT)
    atexit.register(stop, process)
    started = time.time()
    while time.time() - started < config["start_timeout"]:
        if process.poll() is not None:
            sys.exit(f"The server stopped before it answered: see {log}")
        try:
            models(config)
            print(f"The server answers after {time.time() - started:.0f}s.", flush=True)
            return
        except ServerError:
            time.sleep(POLL_SECONDS)
    sys.exit(f"The server did not answer within {config['start_timeout']}s (start_timeout): see {log}")


def stop(process: subprocess.Popen) -> None:
    """Stop the server and the processes it started: only this one, so other servers keep running."""
    if process.poll() is None:
        subprocess.run(["taskkill", "/F", "/T", "/PID", str(process.pid)], capture_output=True)


def no_server_hint(config: dict) -> str:
    hint = ("Start the server, or give init the command that starts it: llm.py init --start \"...\".\n"
            "docs/FRAMEWORK.md, section \"LLM agents\", has a command for each server.")
    if shutil.which("nvidia-smi"):
        gpus = subprocess.run(["nvidia-smi", "--query-gpu=name,memory.total", "--format=csv,noheader"],
                              capture_output=True, text=True).stdout.strip()
        if gpus:
            hint += f"\nYour GPU: {gpus}. The same section says which model size fits it."
    return hint


# init


def init(path: Path, url: str | None, key_env: str | None, model: str | None, start: str | None,
         log: Path) -> int:
    """Find the server, see what it takes and write the config file. A rerun keeps the keys it does not probe."""
    config = load(path) if path.exists() else dict(DEFAULTS)
    if url:
        config["base_url"] = url
    elif not config["base_url"]:
        config["base_url"] = ask_url()
    if key_env is not None:
        config["api_key_env"] = key_env
    if start is not None:
        config["start"] = start
    ensure_server(config, log)
    names = models(config)
    config["model"] = model or pick_model(names)
    try:
        probe(config)
    except ServerError as e:
        sys.exit(f"{e}\nIf it names a field, set that field in extra_body in {path}: null removes one.")
    path.write_text(json.dumps(config, indent=2) + "\n", encoding="utf-8")
    print(f"Wrote {path}.")
    return 0


def ask_url() -> str:
    print("Which server?")
    for i, (name, url) in enumerate(PRESETS, 1):
        print(f"  {i}. {name}: {url}")
    answer = input("A number, or the URL before /chat/completions: ").strip()
    if answer.isdigit() and 1 <= int(answer) <= len(PRESETS):
        return PRESETS[int(answer) - 1][1]
    return answer


def pick_model(names: list[str]) -> str:
    if not names:
        sys.exit("The server lists no model: give one with --model.")
    if len(names) == 1:
        return names[0]
    for i, name in enumerate(names, 1):
        print(f"  {i}. {name}")
    return names[int(input("Which model? A number: ")) - 1]


def probe(config: dict) -> None:
    """Set think_on, think_off, seed and, for a model that always thinks, max_tokens from what the server does."""
    test = ask(config, "Reply with the word ok.", {})
    if test is None:
        raise ServerError("the server refuses even the plainest request")
    print(f"The model {config['model']} answers: {test.text.strip()[:60]!r}")
    find_think_switch(config)
    first = ask(config, "Write one sentence about an animal of your choice.", {"temperature": 1.0, "seed": 7})
    second = first and ask(config, "Write one sentence about an animal of your choice.", {"temperature": 1.0, "seed": 7})
    config["seed"] = bool(first and first == second)
    if config["seed"]:
        print("A seed repeats a reply: a rerun with the same --seed repeats.")
    else:
        print("The server " + ("refuses a seed" if first is None else "does not repeat a reply for a seed")
              + ": a rerun does not repeat.")


def find_think_switch(config: dict) -> None:
    question = "How many times does the letter r occur in the word strawberry? Reply with the number only."
    config["think_on"], config["think_off"] = {}, {}
    by_default = thinks(ask(config, question, {}))
    for on, off in THINK_SWITCHES:
        if not thinks(ask(config, question, on)):
            continue
        reply = ask(config, question, off)
        if reply is not None and not thinks(reply):
            config["think_on"] = {**on, "max_tokens": THINK_MAX_TOKENS}
            config["think_off"] = off
            print(f"Thinking turns on with {json.dumps(on)}: a try thinks after the score stops moving.")
            return
    if by_default:
        config["max_tokens"] = THINK_MAX_TOKENS
        print(f"The model thinks on every try and no switch turns it off: max_tokens is now {THINK_MAX_TOKENS}.")
    else:
        print("No switch turns thinking on: no try thinks.")


def ask(config: dict, question: str, fields: dict) -> Reply | None:
    """The reply to a short request with FIELDS added, or None when the server refuses one of them."""
    body = {"model": config["model"], "messages": [{"role": "user", "content": question}],
            "temperature": config["temperature"], "max_tokens": PROBE_MAX_TOKENS}
    body = merged(merged(merged(body, config["extra_body"]), config["think_off"]), fields)
    try:
        return parse(call(config, "/chat/completions", body))
    except ServerError as e:
        if e.status in REFUSED:
            return None
        raise


def thinks(reply: Reply | None) -> bool:
    return reply is not None and bool(reply.reasoning or "<think>" in reply.text)
