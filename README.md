# C Blockchain

A simple blockchain project implemented in C.

## Overview

This project implements a basic blockchain data structure with the following features:

- Block creation with index, hash, previous hash, timestamp, and nonce
- Genesis block initialization
- Chain validation to ensure integrity
- SHA-256 cryptographic hashing using OpenSSL

## Project Structure

```
c-blockchain/
├── main.c   # Main blockchain logic and implementation
├── crypto.c # SHA-256 hashing functions
├── crypto.h # Cryptography header file
├── build.sh # Build script
└── README.md
```

## Building

To compile the project, run:

```bash
./build.sh
```

Or manually compile with:

```bash
gcc -o main main.c crypto.c -lssl -lcrypto
```

## Usage

After building, run the executable:

```bash
./main
```

The program will:
1. Create a genesis block (first block in the chain)
2. Add several blocks to the blockchain
3. Display the entire blockchain with block details
4. Validate the integrity of the blockchain