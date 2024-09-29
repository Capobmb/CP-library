#!/bin/bash
set -euo pipefail

# activate conda environment
eval "$(conda shell.bash hook)"
conda activate CP

tmpfile=$(mktemp)
unbuffer atcoder-tools submit -u | tee "$tmpfile"
if grep -q "Passed all test case but with stderr." "$tmpfile"; then
  echo "INFO: Ignoring atcoder-tools warning and proceeding to submit with option -fu ."
  atcoder-tools submit -fu
fi
