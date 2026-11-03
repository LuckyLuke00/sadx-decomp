"""The class, struct and namespace scopes of a source line, for reccmp's parser.

reccmp's parser takes any line that starts with class, struct or namespace and a name, and does not end with ;, for
the head of a scope. So the head of a function that returns a struct pointer, such as `struct task *AmyBirdStart()`,
opens a scope task, and a static in it gets the name task::DAT_009979a8. Our build's symbol has no such scope, so
the two do not pair, and AmyBirdStart scored 98.57% on code that matches.

SCOPE takes only the head of a definition: the name, then maybe final, a base list and {, and nothing else.
install() makes reccmp's parser use it. Needs reccmp, so it runs in .venv.
"""

import re

from reccmp.parser import parser

SCOPE = re.compile(r"(?:class|struct|namespace) (?P<name>\w+)\s*(?:final\s*)?(?::[^;()]*)?\{?\s*$")


def install() -> None:
    """Make reccmp's parser open a scope only at the head of a class, struct or namespace. Installing it again changes
    nothing."""
    parser.scopeDetectRegex = SCOPE
