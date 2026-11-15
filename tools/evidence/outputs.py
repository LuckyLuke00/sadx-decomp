"""The generated outputs outside the state folder. The first line of each names the generation that wrote it:
`# <kind> generation=N` for a CSV file, `# <title>, generation N` for a Markdown file. A file whose generation is not
the live one is out of date. Also the row readers: of the neutral input files that local adapters write, and of the
schema files (notes.csv and the state's ledger.csv and sites.csv), whose first line is `# evidence-<kind> schema=N`
with the file's name without its suffix as the kind.

Standard library only.
"""

import csv
import io
import re
from pathlib import Path

HEADER = re.compile(r"# .*\bgeneration[= ](\d+)")
SCHEMA_LINE = re.compile(r"# evidence-([a-z]+) schema=(\d+)")


def csv_text(kind: str, generation: int, columns: tuple, rows) -> str:
    return f"# {kind} generation={generation}\n" + table_text(columns, rows)


def schema_text(name: str, schema: int, columns: tuple, rows) -> str:
    """The text of the schema file NAME: its schema line, then COLUMNS and ROWS as CSV."""
    return f"# evidence-{Path(name).stem} schema={schema}\n" + table_text(columns, rows)


def table_text(columns: tuple, rows) -> str:
    """COLUMNS and ROWS as CSV text with LF line ends."""
    out = io.StringIO()
    writer = csv.writer(out, lineterminator="\n")
    writer.writerow(columns)
    writer.writerows(rows)
    return out.getvalue()


def read_rows(path: Path, columns: tuple, error, skip: int = 0):
    """(where, values) per data row of PATH after its first SKIP lines, each value stripped. The next line must name
    COLUMNS. A fault raises ERROR, an exception class, with the file and line."""
    with path.open(encoding="utf-8", newline="") as data:
        for _ in range(skip):
            data.readline()
        for where, values in _checked_rows(data, columns, error, str(path), skip + 1):
            yield where, {name: value.strip() for name, value in values.items()}


def schema_rows(text: str, name: str, schema: int, columns: tuple, error):
    """(where, values) per data row of TEXT, the schema file NAME (a path or a file name), with the values as written.
    Its first line must name its kind and SCHEMA, its second COLUMNS. A fault raises ERROR, an exception class."""
    kind = Path(name).stem
    first, _, rest = text.partition("\n")
    match = SCHEMA_LINE.fullmatch(first)
    if match is None or match[1] != kind:
        raise error(f"{name}: not a {kind} file, its first line is {first[:60]!r}")
    if int(match[2]) != schema:
        raise error(f"{name}: {kind} schema {match[2]}, this tool reads schema {schema}")
    yield from _checked_rows(io.StringIO(rest), columns, error, name, 2)


def line_of(where: str) -> int:
    """The line number in a WHERE of read_rows or schema_rows."""
    return int(where.rpartition(":")[2])


def _checked_rows(data, columns: tuple, error, name: str, header: int):
    """(where, values) per CSV row of the text stream DATA, whose header names COLUMNS and is line HEADER of NAME.
    WHERE names the line the row ends on, so blank lines and values that span lines count. A row needs one value per
    column, no fewer and no more."""
    reader = csv.DictReader(data)
    if tuple(reader.fieldnames or ()) != columns:
        raise error(f"{name}: the columns must be {','.join(columns)}")
    for fields in reader:
        where = f"{name}:{header - 1 + reader.line_num}"
        if None in fields or any(fields[column] is None for column in columns):
            raise error(f"{where}: the row needs {len(columns)} values")
        yield where, fields


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
