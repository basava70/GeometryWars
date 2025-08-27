#!/bin/bash
set -e

if [ ! -d build ]; then
  echo "No build directory found. Configuring CMake..."
  cmake -S . -B build
fi

cmake --build build

if [ "$1" == "test" ]; then
  echo "Running tests..."
  cd build
  ctest --output-on-failure
else
  echo "Running game..."
  ./build/GeometryWars
fi
