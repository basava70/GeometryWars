#!/bin/bash
## The following is written with the help of ChatGPT
set -euo pipefail

MODE=${1:-game-debug}
ROOT_DIR=$(dirname "$(realpath "$0")")

# Check preset validity
if ! grep -q "\"name\": \"$MODE\"" "$ROOT_DIR/CMakePresets.json"; then
  echo "  Unknown preset: $MODE"
  echo "  Available presets:"
  jq -r '.configurePresets[].name' "$ROOT_DIR/CMakePresets.json"
  exit 1
fi

echo "󰙨  Using preset: $MODE"

# 1️⃣ Configure + Build
cmake --preset "$MODE"
cmake --build --preset "$MODE-build"

# 2️⃣ Update compile_commands.json symlink for clangd
BUILD_DIR=$(jq -r ".configurePresets[] | select(.name==\"$MODE\") | .binaryDir" "$ROOT_DIR/CMakePresets.json")
ln -sf "$ROOT_DIR/$BUILD_DIR/compile_commands.json" "$ROOT_DIR/compile_commands.json"
echo "󰌠  Linked compile_commands.json → $BUILD_DIR"

# 3️⃣ Run the target
case $MODE in
game-*)
  echo "󰡄  Launching GeometryWars..."
  "$ROOT_DIR/$BUILD_DIR/GeometryWars"
  ;;
test-*)
  echo "󰙨  Running unit tests..."
  ctest --test-dir "$ROOT_DIR/$BUILD_DIR" --output-on-failure
  ;;
all-*)
  echo "󰡄  Launching GeometryWars..."
  "$ROOT_DIR/$BUILD_DIR/GeometryWars"
  echo
  echo "󰙨  Running unit tests..."
  ctest --test-dir "$ROOT_DIR/$BUILD_DIR" --output-on-failure
  ;;
esac
