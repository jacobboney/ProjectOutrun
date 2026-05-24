#!/bin/bash
set -e

# Resolve project root
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

BUILD_DIR="$PROJECT_ROOT/build"
INSTALL_DIR="$PROJECT_ROOT"

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

echo "Configuring project..."
cmake "$PROJECT_ROOT" -DCMAKE_INSTALL_PREFIX="$INSTALL_DIR"

echo "Building..."
cmake --build .

echo "Installing..."
cmake --install .

echo "Build and install complete."