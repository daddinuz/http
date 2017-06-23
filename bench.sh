#!/usr/bin/env bash

set -e

x=1
while [ ${x} -le 5 ]; do
    echo "Python"
    \time -p python3 -c "import requests; response = requests.get('https://api.github.com/repos/daddinuz/http/issues', headers={'Accept': 'application/vnd.github.v3+json', 'Content-Type': 'application/json', 'User-Agent': 'daddinuz/http'})" 2>&1
    echo

    echo "C"
    \time -p ./cmake-build-release/bench 2>&1
    echo

    x=$(( ${x} + 1 ))
done
