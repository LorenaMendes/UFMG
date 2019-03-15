#include <stdio.h>
#include <stdlib.h>

#include "Tree.h"

/*
 * Prints the tree in dot format, using the auxiliary function printDot_aux.
 */
void printDot_aux(Apontador p) {
  if (p->Esq)
    printf("  %d -> %d\n", p->Reg.Chave, p->Esq->Reg.Chave);
  if (p->Dir)
    printf("  %d -> %d\n", p->Reg.Chave, p->Dir->Reg.Chave);
}

void printDot(Apontador p) {
  printf("\ndigraph tree {\n");
  Central(p, &printDot_aux);
  printf("\n}\n");
}

TipoChave gen(const int MAX_KEY) {
  return random() % MAX_KEY + 1;
}

int main(int argc, char** argv) {
  if (argc != 3) {
    fprintf(stderr, "Syntax: %s NUM_GEN MAX_KEY\n", argv[0]);
    exit(1);
  } else {
    const int NUM_GEN = atoi(argv[1]);
    const int MAX_KEY = atoi(argv[2]);
    Apontador D;
    Inicializa(&D);
    int i;
    // Inserts NUM_GEN elements in the tree. Repeated elements are not stored
    // in the tree (given the implementation of the tree itself):
    for (i = 0; i < NUM_GEN; i++) {
      Registro Reg;
      Reg.Chave = gen(MAX_KEY);
      Insere(Reg, &D);
    }
    // Print the tree in dot format:
    printDot(D);
  }
}
