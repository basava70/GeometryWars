#!/bin/bash
if rm -rf build_*/; then
  echo "Removed build..."
else
  echo "No such directory 'build' exits!. Exiting..."
fi
