#!/usr/bin/env bash
# Watch a source file; on every save: rebuild (via CMake) and run.
# Usage: ./watch.sh [path/to/file.cpp]
# Env:   BUILD_DIR=build  TARGET=main  INPUT=input.txt  TIMEOUT=5
set -uo pipefail

FILE="${1:-main.cpp}"
BUILD_DIR="${BUILD_DIR:-build}"
TARGET="${TARGET:-main}"
INPUT="${INPUT:-input.txt}"
TIMEOUT="${TIMEOUT:-5}"

command -v inotifywait >/dev/null || {
    echo "missing inotifywait: sudo pacman -S inotify-tools"
    exit 1
}
[[ -f $FILE ]] || {
    echo "no such file: $FILE"
    exit 1
}

dir=$(dirname -- "$FILE")
base=$(basename -- "$FILE")

cmake -S . -B "$BUILD_DIR" -DSRC="$(realpath -- "$FILE")" >/dev/null || exit 1

run() {
    clear
    printf '\e[1;34m[%s] building %s...\e[0m\n' "$(date +%T)" "$base"
    if ! cmake --build "$BUILD_DIR" 2>&1; then
        printf '\e[1;31m--- build failed ---\e[0m\n'
        return
    fi

    # Feed input.txt to stdin if it exists, otherwise /dev/null
    # (never the inotify pipe, or std::cin would eat the watch events).
    local in=/dev/null
    [[ -f $INPUT ]] && in=$INPUT

    printf '\e[1;32m--- running (stdin: %s) ---\e[0m\n' "$in"
    timeout "$TIMEOUT" "./$BUILD_DIR/$TARGET" <"$in"
    local rc=$?
    if ((rc == 124)); then
        printf '\e[1;31m--- killed: exceeded %ss ---\e[0m\n' "$TIMEOUT"
    else
        printf '\e[1;33m--- exit %d ---\e[0m\n' "$rc"
    fi
}

run

# Watch the directory, not the file: vim/neovim and many editors save by
# writing a new file and renaming it, which breaks a direct file watch.
inotifywait -mq -e close_write,moved_to,create --format '%f' -- "$dir" |
    while read -r f; do
        [[ $f == "$base" || $f == "$(basename -- "$INPUT")" ]] || continue
        # Debounce: swallow the burst of events a single save can produce.
        while read -r -t 0.15 _; do :; done
        run
    done
