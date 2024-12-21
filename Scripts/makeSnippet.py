#! /usr/bin/env python3
import sys
import json
from typing import List


def make_snippet(name: str, prefix: str, lines: List[str], description: str):
    lines = [line.strip("\n") for line in lines]
    return {name: {"prefix": prefix, "body": lines, "description": description}}


if __name__ == "__main__":
    if len(sys.argv) < 3:
        print(
            "Usage: python makeSnippet.py <file_name> <snippet_name> <prefix> [ <description>]\n"
            "  <file_name>: Path to the file containing snippet body\n"
            "  <snippet_name>: Name of the snippet\n"
            "  <prefix>: Shortcut prefix for the snippet\n"
            "  <description>: Optional description for the snippet",
            file=sys.stderr,
        )
        sys.exit(1)
    fileName = sys.argv[1]
    snippetName = sys.argv[2]
    prefix = sys.argv[3]
    description = sys.argv[4] if len(sys.argv) > 4 else ""

    with open(fileName, "r") as f:
        lines = f.readlines()
    snippetJson = make_snippet(snippetName, prefix, lines, description)
    result = json.dumps(snippetJson, indent=4)
    assert result[0] == "{" and result[-1] == "}"
    print(result[1:-1])
