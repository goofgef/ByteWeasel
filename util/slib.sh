#!/usr/bin/env bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$SCRIPT_DIR/.."

cmake -S "$PROJECT_ROOT/cmake/static" -B "$PROJECT_ROOT/build/static"
cmake --build "$PROJECT_ROOT/build/static"