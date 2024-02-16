#!/bin/bash

# Default values
MODE="debug"
MAKE="make"

# Parse arguments
while getopts ":mcdrj" opt; do
    case ${opt} in
        m )
            rm -r build
            exit
            ;;
        d )
            MODE="debug"
            ;;
        r )
            MODE="release"
            ;;
        \? )
            echo "Usage: $0 [-m] [-d] [-r]"
            echo "  -m: Clean the build (remove build directory)"
            echo "  -d: Build in debug mode (default)"
            echo "  -r: Build in release mode"
            exit 1
            ;;
    esac
done

# Create build directory if it doesn't exist
mkdir -p build

# Change to build directory
cd build || exit

# Configure build based on mode
if [ "$MODE" = "debug" ]; then
    echo "Configuring project for Debug"
    cmake -DCMAKE_BUILD_TYPE=Debug ..
else
    echo "Configuring project for Release"
    cmake -DCMAKE_BUILD_TYPE=Release ..
fi

# Build the project
$MAKE

