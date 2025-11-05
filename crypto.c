#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include "crypto.h"

unsigned char *create_sha256(const unsigned char str[], unsigned char *buffer){
    SHA256(str, strlen((const char*)str), buffer);
    return buffer;
}

void hash_to_string(unsigned char hash[32], char output[65]) {
    // Loop through each of the 32 bytes
    for (int i = 0; i < 32; i++) {
        // Convert each byte to 2 hex characters
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[64] = '\0';
}