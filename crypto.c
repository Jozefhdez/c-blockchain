#include "crypto.h"
#include <openssl/sha.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char *create_sha256(const unsigned char *data, size_t len,
                             unsigned char *buffer) {
  SHA256(data, len, buffer);
  return buffer;
}

void hash_to_string(const unsigned char *hash, char *output) {
  for (int i = 0; i < 32; i++) {
    sprintf(output + (i * 2), "%02x", hash[i]);
  }
  output[64] = '\0';
}
