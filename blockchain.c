#include "blockchain.h"
#include "crypto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static void calculate_block_hash(Block *block, unsigned char *output_hash) {
  size_t data_size = sizeof(size_t) + sizeof(block->data) +
                     sizeof(block->prev_hash) + sizeof(time_t) + sizeof(long);

  unsigned char *buffer = malloc(data_size);
  if (!buffer) {
    perror("Failed to allocate memo");
    exit(EXIT_FAILURE);
  }

  unsigned char *ptr = buffer;
  memcpy(ptr, &block->index, sizeof(size_t));
  ptr += sizeof(size_t);
  memcpy(ptr, block->data, sizeof(block->data));
  ptr += sizeof(block->data);
  memcpy(ptr, block->prev_hash, sizeof(block->prev_hash));
  ptr += sizeof(block->prev_hash);
  memcpy(ptr, &block->timestamp, sizeof(time_t));
  ptr += sizeof(time_t);
  memcpy(ptr, &block->nonce, sizeof(long));

  create_sha256(buffer, data_size, output_hash);
  free(buffer);
}

static void mine_block(Block *block) {
  printf("Mining Block %zu\n", block->index);
  block->nonce = 0;

  while (true) {
    calculate_block_hash(block, block->hash);

    // Verify difficulty (first n bytes should be 0
    bool valid = true;
    for (int i = 0; i < DIFFICULTY; i++) {
      if (block->hash[i] != 0) {
        valid = false;
        break;
      }
    }

    if (valid) {
      printf("Success, nonce: %ld\n", block->nonce);
      break;
    }
    block->nonce++;
  }
}

Block *create_genesis_block() {
  Block *genesis = malloc(sizeof(Block));

  genesis->index = 0;
  strncpy(genesis->data, "Genesis Block", 255);
  memset(genesis->prev_hash, 0, HASH_SIZE);
  genesis->timestamp = time(NULL);
  genesis->next = NULL;

  mine_block(genesis);
  return genesis;
}

void add_block(Block **head, const char *data) {
  // find last block
  Block *current = *head;
  while (current->next != NULL) {
    current = current->next;
  }

  // create new node
  Block *new_block = malloc(sizeof(Block));
  new_block->index = current->index + 1;
  strncpy(new_block->data, data, 255);
  memcpy(new_block->prev_hash, current->hash, HASH_SIZE);
  new_block->timestamp = time(NULL);
  new_block->next = NULL;

  // proof of work
  mine_block(new_block);

  // link to previous block
  current->next = new_block;
}

bool validate_chain(Block *head) {
  Block *current = head;
  while (current != NULL && current->next != NULL) {
    Block *next_b = current->next;

    if (next_b->index != current->index + 1)
      return false;
    if (memcmp(next_b->prev_hash, current->hash, HASH_SIZE) != 0)
      return false;

    unsigned char check_hash[HASH_SIZE];
    calculate_block_hash(next_b, check_hash);
    if (memcmp(check_hash, next_b->hash, HASH_SIZE) != 0)
      return false;

    current = next_b;
  }
  return true;
}

void print_chain(Block *head) {
  Block *current = head;
  char hex_str[65];

  printf("\n=== BLOCKCHAIN STATE ===\n");
  while (current != NULL) {
    hash_to_string(current->hash, hex_str);
    printf("[Block %zu] %s\n", current->index, hex_str);
    printf("Data: %s\n", current->data);
    current = current->next;
  }
  printf("========================\n\n");
}

void free_chain(Block *head) {
  Block *current = head;
  while (current != NULL) {
    Block *temp = current;
    current = current->next;
    free(temp);
  }
}
