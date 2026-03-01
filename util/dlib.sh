#!/usr/bin/env bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$SCRIPT_DIR/.."

cmake -S "$PROJECT_ROOT/cmake/shared" -B "$PROJECT_ROOT/build/shared"
cmake --build "$PROJECT_ROOT/build/shared"