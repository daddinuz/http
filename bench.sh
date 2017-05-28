#!/usr/bin/env bash

echo "Python"
time python3 -c "import requests; requests.get('https://api.github.com/repos/daddinuz/http/issues', headers={'Accept': 'application/vnd.github.v3+json', 'Content-Type': 'application/json', 'User-Agent': 'daddinuz/http'})"

echo

echo "C"
time ./cmake-build-release/example
