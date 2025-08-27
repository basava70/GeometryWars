#!/bin/bash
set -e

MODE=${1:-all} # default = all

# Single build folder
BUILD_DIR="build"

# Map mode → cmake flags
case $MODE in
game)
  CMAKE_FLAGS="-DBUILD_GAME=ON -DBUILD_TEST=OFF"
  ;;
test)
  CMAKE_FLAGS="-DBUILD_GAME=OFF -DBUILD_TEST=ON"
  ;;
all)
  CMAKE_FLAGS="-DBUILD_GAME=ON -DBUILD_TEST=ON"
  ;;
*)
  echo "Usage: $0 [game|test|all]"
  exit 1
  ;;
esac

# Configure or reconfigure (safe if build dir already exists)
echo "Configuring CMake for mode: $MODE"
cmake -S . -B "$BUILD_DIR" $CMAKE_FLAGS

# Build
cmake --build "$BUILD_DIR"

# Run what was requested
case $MODE in
game)
  echo "Running game..."
  "./$BUILD_DIR/GeometryWars"
  ;;
test)
  echo "Running tests..."
  ctest --test-dir "$BUILD_DIR" --output-on-failure
  ;;
all)
  echo "Running game..."
  "./$BUILD_DIR/GeometryWars"
  echo
  echo "Running tests..."
  ctest --test-dir "$BUILD_DIR" --output-on-failure
  ;;
esac
