#!/bin/bash

SRC="main.c"
OUT="main"
gcc -Wall -g $SRC -o $OUT

if [ $? -eq 0 ]; then
    echo "Compilation successful. Run ./$OUT to execute."
else
    echo "Compilation failed."
fi