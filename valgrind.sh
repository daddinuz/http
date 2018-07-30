#!/usr/bin/env  bash

set -e
valgrind --trace-children=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --log-file=valgrind.log "${@}"
