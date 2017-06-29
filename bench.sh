#!/usr/bin/env bash

set -e

x=1
while [ ${x} -le 5 ]; do
    echo -e "====================\nPython"
    \time -p python3 bench.py 2>&1
    echo

    echo "C"
    \time -p ./cmake-build-release/bench 2>&1
    echo -e "====================\n"

    x=$(( ${x} + 1 ))
done
