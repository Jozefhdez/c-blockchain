#!/bin/bash

SRC="main.c"
OUT="main"
gcc -Wall -g $SRC -o $OUT

if [ $? -eq 0 ]; then
    printf "Compilation successful. \nRun ./$OUT to execute.\n"
else
    printf "Compilation failed."
fi