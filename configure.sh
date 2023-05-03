#!/bin/bash

# Get the directory path of the script
SCRIPT_DIR="$(dirname "$0")"

# Define the build and test directories
BUILD_DIR="$SCRIPT_DIR/build"

# Define build and make functions
function build {
  mkdir -p "$BUILD_DIR"
  cmake -S "$SCRIPT_DIR" -B "$BUILD_DIR"
}

build

