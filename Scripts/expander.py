#!/usr/bin/env python

import os
import re
import logging
import sys

# logger
logger = logging.getLogger(__name__)
logger.setLevel(logging.INFO)
handler = logging.StreamHandler(sys.stderr)
handler.setLevel(logging.INFO)
logger.addHandler(handler)

# TODO: 正規表現で #include "..." をパターンマッチング
# include_pattern = re.compile(r'#include\s+"([^"]+)"')
# 今は CP-library 以下のファイルのみを対象とする
include_pattern = re.compile(r'#include\s*"CP-library/([^"]+)"')

# 不存在ファイルのリストを格納するリスト
missing_includes = []


def resolve_include(file_path, include_dirs):
    if not os.path.isfile(file_path):
        raise FileNotFoundError(f"File not found: {file_path}")

    with open(file_path, "r") as f:
        lines = f.readlines()

    result = []

    for line in lines:
        stripped_line = line.strip()
        # #include "..." にマッチさせる
        match = include_pattern.match(stripped_line)
        if match:
            include_path = "CP-library/" + match.group(1)  # "..." 内のパスを取得

            # include_dirs で指定されたディレクトリを順に探索
            for include_dir in include_dirs:
                full_path = os.path.join(include_dir, include_path)
                print(f"full_path: {full_path}", file=sys.stderr)
                # logger.info(f"Checking {full_path}")
                if os.path.isfile(full_path):
                    result.append(f"// {stripped_line} => {full_path}\n")
                    # TODO: 再帰的にインクルードファイルを展開
                    # result.append(resolve_include(full_path, include_dirs))
                    # 今は単純にファイルの内容を追加
                    with open(full_path, "r") as include_file:
                        result.append(include_file.read())
                    break
            else:
                # ファイルが見つからない場合
                warning_message = f"Warning: Include file not found: {include_path}"
                logger.warning(warning_message)
                missing_includes.append(
                    include_path
                )  # 見つからないファイルをリストに追加
                result.append(f"// {warning_message}\n")
        else:
            result.append(line)

    return "".join(result)


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python script.py <path_to_main_cpp_file>", file=sys.stderr)
        sys.exit(1)

    # 第一引数でファイルパスを取得
    main_file = sys.argv[1]
    # main_file = "./main_2.cpp"

    # インクルードディレクトリを指定
    include_dirs = [
        "/Users/capoth/CP/include",
    ]
    logger.info(f"Include directories: {include_dirs}")

    try:
        expanded_code = resolve_include(main_file, include_dirs)
        print(expanded_code)

        # 不存在ファイルのリストを表示
        if missing_includes:
            logger.warning("The following include files were not found:")
            for missing in missing_includes:
                logger.warning(f"  {missing}")
        else:
            logger.info("All include files were found successfully.")

    except FileNotFoundError as e:
        print(f"Error: {e}")
