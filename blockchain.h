#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <stdbool.h>
#include <time.h>

#define HASH_SIZE 32
#define DIFFICULTY 2

// linked list node structure
typedef struct Block {
  size_t index;
  char data[256];
  unsigned char prev_hash[HASH_SIZE];
  unsigned char hash[HASH_SIZE];
  time_t timestamp;
  long nonce;
  struct Block *next;
} Block;

// Core functions
Block *create_genesis_block();
void add_block(Block **head, const char *data);
bool validate_chain(Block *head);
void print_chain(Block *head);
void free_chain(Block *head);

#endif
