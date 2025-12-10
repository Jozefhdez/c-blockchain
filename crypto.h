#ifndef CRYPTO_H
#define CRYPTO_H

#include <stddef.h>

unsigned char *create_sha256(const unsigned char *data, size_t len,
                             unsigned char *output_hash);

void hash_to_string(const unsigned char *hash, char *output_string);

#endif
