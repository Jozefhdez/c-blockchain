#!/bin/bash

OPENSSL_PATH=$(brew --prefix openssl@3)

gcc -I${OPENSSL_PATH}/include \
    -L${OPENSSL_PATH}/lib \
    crypto.c blockchain.c main.c \
    -o main \
    -lssl -lcrypto

if [ $? -eq 0 ]; then
    echo "Build complete! Run with: ./main"
else
    echo "Build failed!"
    exit 1
fi
