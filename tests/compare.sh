#!/usr/bin/env bash
#

if [[ $# -ne 3 ]]; then
    echo "Usage: $0 <cmd> <source> <expected>"
    exit 1
fi

cmd=$1
source=$2
expected=$3

tmpfile=$(mktemp)
$cmd $source > $tmpfile

diff -u $expected $tmpfile
