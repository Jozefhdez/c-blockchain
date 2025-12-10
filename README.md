# C Blockchain

A simple blockchain project implemented in C.

## Overview

This project implements a dynamic blockchain using a Linked List structure. Key features include:

- Proof of Work: Basic mining algorithm (difficulty adjustment).
- Dynamic Memory: Uses malloc/free for scalable chain growth.
- Data Integrity: Cryptographic linking using SHA-256 (OpenSSL).
- Validation: automated chain verification.

## Project Structure

```
c-blockchain/
├── main.c        # Entry point and simulation logic
├── blockchain.c  # Core logic: Mining, Linked List, Validation
├── blockchain.h  # Blockchain interface and structs
├── crypto.c      # SHA-256 wrapper functions
├── crypto.h      # Cryptography interface
├── build.sh      # Compilation script (Mac/Linux)
└── README.md
```

## Building

To compile the project, run:

```bash
./build.sh
```

Or manually compile with:

```bash
gcc -o main main.c blockchain.c crypto.c -lssl -lcrypto
```

## Usage

After building, run the executable:

```bash
./main
```

The program will:

1. Initialize the Genesis Block.
2. Mine new blocks (calculating nonces to meet difficulty).
3. Display the chain with hex hashes.
4. Validate the cryptographic integrity of the entire chain.
5. Clean up memory before exiting.

