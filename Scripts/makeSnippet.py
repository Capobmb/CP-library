#! /usr/bin/env python3
import argparse
import json
import sys
from typing import List


def make_snippet(name: str, prefix: str, lines: List[str], description: str):
    lines = [line.strip("\n") for line in lines]
    return {name: {"prefix": prefix, "body": lines, "description": description}}


def description_with_default(raw_description: str, default_value: str):
    return f"{raw_description}\n(default: {default_value})"


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Create VSCode snippet that expands the content of a file.\nThe output can easily be pasted into setting json.",
        formatter_class=argparse.RawTextHelpFormatter,
    )
    parser.add_argument(
        "-i",
        "--input",
        type=argparse.FileType("r"),
        help=description_with_default(
            "Path to the file containing snippet body", "standard input"
        ),
        default=sys.stdin,
    )
    parser.add_argument(
        "-p", "--prefix", required=True, help="Shortcut prefix for the snippet"
    )
    parser.add_argument(
        "-s",
        "--snippet_name",
        default=None,
        help=description_with_default("Name of the snippet", "same as PREFIX"),
    )
    parser.add_argument(
        "-d",
        "--description",
        default="",
        help=description_with_default("Description for the snippet", "empty"),
    )
    parser.add_argument(
        "--no-trailing-comma",
        help=description_with_default(
            "remove trailing comma from the output json", "None"
        ),
        action="store_true",
        default=None,
    )
    args = parser.parse_args()

    lines = args.input.readlines()
    if args.snippet_name is None:
        args.snippet_name = args.prefix
    snippetJson = make_snippet(args.snippet_name, args.prefix, lines, args.description)
    result = json.dumps(snippetJson, indent=4)
    assert result[0] == "{" and result[-1] == "}"
    result = result[1:-1].strip("\n")
    if args.no_trailing_comma is None:
        result += ","

    print(result)
