#include "blockchain.h"
#include <stdio.h>

int main() {
  printf("--- Initializing Blockchain ---\n");

  Block *chain = create_genesis_block();

  add_block(&chain, "Transfer: $500");
  add_block(&chain, "Transfer: $1000");
  add_block(&chain, "Transfer: $200");

  print_chain(chain);

  if (validate_chain(chain)) {
    printf("Blockchain is valid.\n");
  } else {
    printf("Blockchain corrupted!\n");
  }

  free_chain(chain);
  printf("Memory cleaned");
  return 0;
}
