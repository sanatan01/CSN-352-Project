#!/bin/bash

# Remove build directory if it exists
rm -rf build
# Create build directory if it doesn't exist
mkdir -p build

# Go to build directory
cd build

# Configure with Ninja if build.ninja doesn't exist
if [ ! -f "build.ninja" ]; then
    echo "Configuring project with Ninja..."
    cmake -G Ninja ..
fi

# Run the clean command
echo "Running deep clean..."
ninja deep_clean

echo "Clean completed successfully!" 