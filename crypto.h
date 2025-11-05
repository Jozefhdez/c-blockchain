#ifndef CRYPTO_H
#define CRYPTO_H

unsigned char *create_sha256(const unsigned char str[], unsigned char *buffer);
void hash_to_string(unsigned char hash[32], char output[65]);

#endif