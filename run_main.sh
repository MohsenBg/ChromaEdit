#!/bin/bash

# Get the directory path of the script
SCRIPT_DIR="$(dirname "$0")"

# Define the build and test directories
BUILD_DIR="$SCRIPT_DIR/build"
MAIN_BIN="$BUILD_DIR/ChromaEdit"
MAKE_FILE="$BUILD_DIR/Makefile"

# Define build and make functions
function build {
  mkdir -p "$BUILD_DIR"
  cmake -S "$SCRIPT_DIR" -B "$BUILD_DIR"
}

function makefile {
  make -C "$BUILD_DIR"
}

# Check if the "-f" flag is present
if [[ "$*" == *-f* ]]; then
  build
  makefile
fi

# Check if Makefile exists
if ! [ -f "$MAKE_FILE" ]; then
  build
fi

# Check if ChoramEdit exists
if ! [ -f "$MAIN_BIN" ]; then
  makefile
fi

# Run the Main Bin
"$MAIN_BIN"
