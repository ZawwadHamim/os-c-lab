#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Usage: $0 <path>"
    exit 1
fi

if [ -f "$1" ]; then
    echo "$1 is a regular file."

    if [ -r "$1" ]; then
        echo "$1 is readable."
    else
        echo "$1 is NOT readable."
    fi

    if [ -w "$1" ]; then
        echo "$1 is writable."
    else
        echo "$1 is NOT writable."
    fi

    if [ -x "$1" ]; then
        echo "$1 is executable."
    else
        echo "$1 is NOT executable."
    fi
else
    echo "$1 is not a regular file."
fi
