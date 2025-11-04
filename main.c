#include <stdio.h>

// structure representing a merkel node
typedef struct {
    unsigned char *hash;
} MerkelNode;

// structure representing a single block in the blockchain
typedef struct {
    size_t index; // size_t unsigned integer used for sizes

    // * pointer to memory location
    unsigned char *prev_hash; // points to array of bytes
    char *timestamp; // points to string of chars
    
    int nonce;
    MerkelNode root;
} Block;

int main(){
    printf("Hello, world!\n");
}