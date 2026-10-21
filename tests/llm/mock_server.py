"""A fake chat server, to test tools/llm.py without a model. Manual: it needs the toolchain and the game.

  python tests/llm/mock_server.py [--port 8099] MODE

Then point llm.json at http://127.0.0.1:8099/v1, or put this command line in its "start".
MODE says what it replies to a function's prompt:
  oracle   the function as the last commit has it, with its file's declarations
  broken   first the oracle with a line that does not build, then the oracle
  repeat   the broken reply on every try
  strict   the oracle, but a 400 for any field besides model, messages, temperature and max_tokens
  think    the oracle after inline <think> text, and no usage field
Any other request gets a short fixed reply. In every mode but strict, a request with
chat_template_kwargs.enable_thinking true also gets reasoning_content. Every request goes
to build/llm/mock/request-N.json.
"""

import argparse
import json
import re
import subprocess
from http.server import BaseHTTPRequestHandler, HTTPServer
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
LOG = ROOT / "build" / "llm" / "mock"
STRICT_FIELDS = {"model", "messages", "temperature", "max_tokens"}
TASK = re.compile(r"Function (0x[0-9a-f]{8}), to go in (\S+)\. Dossier")
ANNOTATION = re.compile(r"//\s*FUNCTION:\s*\w+\s+(0x[0-9a-fA-F]+)")


def oracle(file: str, address: int) -> str:
    """The function at ADDRESS as the last commit has it, after its file's top-of-file declarations."""
    lines = subprocess.run(["git", "show", f"HEAD:{file}"], cwd=ROOT, capture_output=True, text=True,
                           check=True).stdout.split("\n")
    marks = [i for i, line in enumerate(lines) if ANNOTATION.match(line)]
    start = next(i for i in marks if int(ANNOTATION.match(lines[i]).group(1), 16) == address)
    end = lines.index("}", start)
    decls = [line for line in lines[:marks[0]] if line.endswith(";")]
    return "\n".join(decls + lines[start:end + 1])


def reply_text(mode: str, body: dict, count: int) -> str:
    task = TASK.search(body["messages"][1]["content"]) if len(body["messages"]) > 1 else None
    if task is None:
        return "ok"
    code = oracle(task.group(2), int(task.group(1), 16))
    tries = (len(body["messages"]) - 2) // 2 + 1
    if mode == "repeat" or (mode == "broken" and tries == 1):
        code = code.replace("\n{\n", "\n{\n\tthis does not build;\n", 1)
    text = f"Here it is.\n\n```cpp\n{code}\n```\n"
    return f"<think>request {count}: thinking</think>\n{text}" if mode == "think" else text


class Handler(BaseHTTPRequestHandler):
    mode = "oracle"
    count = 0

    def send(self, status: int, data: dict) -> None:
        raw = json.dumps(data).encode("utf-8")
        self.send_response(status)
        self.send_header("Content-Type", "application/json")
        self.send_header("Content-Length", str(len(raw)))
        self.end_headers()
        self.wfile.write(raw)

    def do_GET(self) -> None:
        if self.path.rstrip("/").endswith("/models"):
            self.send(200, {"object": "list", "data": [{"id": "mock", "object": "model"}]})
        else:
            self.send(404, {"error": {"message": f"no {self.path}"}})

    def do_POST(self) -> None:
        body = json.loads(self.rfile.read(int(self.headers["Content-Length"])))
        Handler.count += 1
        LOG.mkdir(parents=True, exist_ok=True)
        (LOG / f"request-{Handler.count}.json").write_text(json.dumps(body, indent=1), encoding="utf-8")
        unknown = sorted(set(body) - STRICT_FIELDS)
        if self.mode == "strict" and unknown:
            self.send(400, {"error": {"message": f"Unrecognized request argument supplied: {unknown[0]}"}})
            return
        text = reply_text(self.mode, body, Handler.count)
        message = {"role": "assistant", "content": text}
        if (body.get("chat_template_kwargs") or {}).get("enable_thinking"):
            message["reasoning_content"] = "Let me think."
        answer = {"choices": [{"index": 0, "message": message, "finish_reason": "stop"}]}
        if self.mode != "think":
            answer["usage"] = {"prompt_tokens": len(json.dumps(body["messages"])) // 4, "completion_tokens": len(text) // 4}
        self.send(200, answer)

    def log_message(self, *args) -> None:
        pass


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--port", type=int, default=8099)
    parser.add_argument("mode", choices=("oracle", "broken", "repeat", "strict", "think"))
    args = parser.parse_args()
    Handler.mode = args.mode
    HTTPServer(("127.0.0.1", args.port), Handler).serve_forever()


if __name__ == "__main__":
    main()
