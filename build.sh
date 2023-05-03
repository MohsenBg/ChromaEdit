#!/bin/bash

# Get the directory path of the script
SCRIPT_DIR="$(dirname "$0")"

# Define the build and test directories
BUILD_DIR="$SCRIPT_DIR/build"

function makefile {
  make -C "$BUILD_DIR"
}

makefile
