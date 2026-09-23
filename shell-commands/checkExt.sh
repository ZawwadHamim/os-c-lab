#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Usage: $0 <path>"
    exit 1
fi

if [ -d "$1" ]; then
    echo "$1 is a directory"
elif [ -f "$1" ]; then
    echo "$1 is a regular file"
else
    echo "$1 is something else (or does not exist)"
fi
