#include <stdio.h>
#include <stdlib.h>

#include "Tree.h"

/*
 * Auxiliary function used in a tree traversal that prints key information for
 * all the keys in the tree.
 */
void visita(Apontador p) {
  printf("Key = %8d, Dir? = %d, Esq? = %d\n", p->Reg.Chave, p->Dir != NULL,
      p->Esq != NULL);
}

// Generate random keys to fill up the tree.
//
TipoChave gen(const int MAX_KEY) {
  return random() % MAX_KEY + 1;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "Syntax: %s num_keys\n", argv[0]);
    exit(1);
  } else {
    Apontador D;
    Inicializa(&D);
    int i;
    const int NUM_KEYS = atoi(argv[1]);
    // Inserts elements in the tree.
    printf("Inserting:\n");
    for (i = 0; i < NUM_KEYS; i++) {
      Registro Reg;
      Reg.Chave = gen(NUM_KEYS * 2);
      if (Insere(Reg, &D))
        printf("%4s%4d", "+", Reg.Chave);
      else
        printf("%4s%4d", "*", Reg.Chave);
    }
    // Visits every key in the tree.
    printf("\nOriginal tree:\n");
    Central(D, &visita);
    // Removes elements from the tree.
    printf("\nRemoving:\n");
    for (i = 0; i < NUM_KEYS; i++) {
      TipoChave Chave = gen(NUM_KEYS * 2);
      if (Retira(Chave, &D))
        printf("%4d%4s", Chave, "-");
      else
        printf("%4d%4s", Chave, "*");
    }
    // Visits every key in the tree.
    printf("\nAfter removing elements:\n");
    Central(D, &visita);
  }
}
