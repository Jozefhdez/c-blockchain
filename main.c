#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "crypto.h"

// structure representing a single block in the blockchain
typedef struct {
    size_t index; // position in the blockchain (0, 1, 2, ...)
    unsigned char *hash; // This blocks hash
    unsigned char *prev_hash; //prev blocks hash
    char *timestamp; // when the block was created
    int nonce; // number used for mining
} Block;

unsigned char *hashBlock(Block block){
    // Should concatenate all block data -> hash it -> return hash
    char str_index[20];
    snprintf(str_index, sizeof(str_index), "%zu", block.index);

    char str_prev_hash[65];
    hash_to_string(block.prev_hash, str_prev_hash);

    char str_nonce[20];
    snprintf(str_nonce, sizeof(str_nonce), "%d", block.nonce);
    
    size_t total_len = strlen(str_index) + strlen(str_prev_hash) + strlen(block.timestamp) + strlen(str_nonce) + 1;

    // allocate buffer for concatenated string
    char *data = malloc(total_len);
    if (data == NULL) {
        return NULL;  // Memory allocation failed
    }

    // concatenate data
    snprintf(data, total_len, "%s%s%s%s", 
             str_index, str_prev_hash, block.timestamp, str_nonce);

    // allocate memory for the hash result (32 bytes)
    unsigned char *hash = malloc(32);
    if (hash == NULL) {
        free(data);
        return NULL;  // Memory allocation failed
    }
    
    // hash the concatenated data
    create_sha256((unsigned char*)data, hash);
    
    free(data);
    return hash;
}

Block createGenesisBlock() {
    Block genesis;
    genesis.index = 0;
    
    // allocate and set prev_hash to 32 bytes of zeros (no previous block)
    genesis.prev_hash = (unsigned char *)calloc(32, sizeof(unsigned char));
    
    time_t current_time = time(NULL);
    genesis.timestamp = strdup(ctime(&current_time));
    
    genesis.nonce = 0;
    
    genesis.hash = hashBlock(genesis);
    return genesis;
}

void addBlock(Block blockchain[], int *block_count, int nonce){
    Block *prev_block = &blockchain[*block_count - 1];

    Block new_block;
    new_block.index = prev_block->index + 1;
    
    // allocate 32 bytes of zeros
    new_block.prev_hash = malloc(32);
    memcpy(new_block.prev_hash, prev_block->hash, 32); // copy hash to prev_hash
    
    time_t current_time = time(NULL);
    new_block.timestamp = strdup(ctime(&current_time));
    
    new_block.nonce = nonce; // use parameter
    
    new_block.hash = hashBlock(new_block);

    blockchain[*block_count] = new_block; // store the block in the array
    (*block_count)++; // increment block count (dereference the pointer)
}

bool validateChain(Block blockchain[], int block_count){
    if (block_count == 0) {
        printf("Blockchain is empty");
        return false;
    } else if (blockchain[0].index != 0) {
        printf("Genesis block index is not 0");
        return false;
    }

    for (int i = 1; i < block_count; i++) {
        Block current = blockchain[i];
        Block prev_block = blockchain[i - 1];

        if (current.index != prev_block.index + 1) {
            printf("Block %zu has wrong index\n", current.index);
            return false;
        } else if (memcmp(current.prev_hash, prev_block.hash, 32) != 0) {
            printf("Block %zu prev_hash doesn't match previous block\n", current.index);
            return false;
        }
        
        unsigned char *recalculated_hash = hashBlock(current);
        if (memcmp(current.hash, recalculated_hash, 32) != 0){
            printf("Block %zu hash is invalid!\n", current.index);
            free(recalculated_hash);
            return false;
        }
    }
    printf("--- Blockchain is valid ---\n");
    return true;
}

void printBlock(Block block) {
    printf("\n--- Block %zu ---\n", block.index);
    
    // Print hash
    char hash_str[65];
    hash_to_string(block.hash, hash_str);
    printf("Hash: %s\n", hash_str);
    
    // Print prev_hash
    char prev_hash_str[65];
    hash_to_string(block.prev_hash, prev_hash_str);
    printf("Prev Hash: %s\n", prev_hash_str);
    
    printf("Timestamp: %s", block.timestamp);
    printf("Nonce: %d\n", block.nonce);
}

void printBlockchain(Block blockchain[], int block_count) {
    printf("\n---------- BLOCKCHAIN ----------\n");
    for (int i = 0; i < block_count; i++) {
        printBlock(blockchain[i]);
    }
    printf("-----------------------------------\n");
    printf("Total Blocks: %d\n", block_count);
}

int main(){
    Block blockchain[16];
    int block_count = 0;
    
    // Create genesis block
    blockchain[0] = createGenesisBlock();
    block_count = 1;
    
    // Add blocks
    addBlock(blockchain, &block_count, 42);
    addBlock(blockchain, &block_count, 100);
    addBlock(blockchain, &block_count, 256);
    
    // Print entire blockchain
    printBlockchain(blockchain, block_count);
        
    // Validate blockchain
    validateChain(blockchain, block_count);
    return 0;
}