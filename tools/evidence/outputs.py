"""The generated outputs outside the state folder. The first line of each names the generation that wrote it:
`# <kind> generation=N` for a CSV file, `# <title>, generation N` for a Markdown file. A file whose generation is not
the live one is out of date. Also the row reader of the neutral input files that local adapters write.

Standard library only.
"""

import csv
import io
import re
from pathlib import Path

HEADER = re.compile(r"# .*\bgeneration[= ](\d+)")


def csv_text(kind: str, generation: int, columns: tuple, rows) -> str:
    return f"# {kind} generation={generation}\n" + table_text(columns, rows)


def table_text(columns: tuple, rows) -> str:
    """COLUMNS and ROWS as CSV text with LF line ends."""
    out = io.StringIO()
    writer = csv.writer(out, lineterminator="\n")
    writer.writerow(columns)
    writer.writerows(rows)
    return out.getvalue()


def read_rows(path: Path, columns: tuple, error, skip: int = 0):
    """(where, values) per data row of PATH after its first SKIP lines. The next line must name COLUMNS. A fault
    raises ERROR, an exception class, with the file and line."""
    with path.open(encoding="utf-8", newline="") as data:
        for _ in range(skip):
            data.readline()
        reader = csv.DictReader(data)
        if tuple(reader.fieldnames or ()) != columns:
            raise error(f"{path}: the columns must be {','.join(columns)}")
        for line, fields in enumerate(reader, skip + 2):
            where = f"{path}:{line}"
            if None in fields or any(fields[name] is None for name in columns):
                raise error(f"{where}: the row needs {len(columns)} values")
            yield where, {name: fields[name].strip() for name in columns}


def generation_of(path: Path) -> int | None:
    """The generation in PATH's first line; None when PATH is missing or its first line names none."""
    if not path.is_file():
        return None
    with path.open(encoding="utf-8") as data:
        match = HEADER.match(data.readline())
    return int(match[1]) if match else None


def stale(folder: Path, names: tuple, generation: int) -> list[str]:
    """The NAMES (paths relative to FOLDER) that exist and were not written by GENERATION, with forward slashes."""
    return [Path(name).as_posix() for name in names
            if (folder / name).is_file() and generation_of(folder / name) != generation]
