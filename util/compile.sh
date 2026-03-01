#!/usr/bin/env bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$SCRIPT_DIR/.."

cmake -S "$PROJECT_ROOT/cmake/exe" -B "$PROJECT_ROOT/build/exe"
cmake --build "$PROJECT_ROOT/build/exe"