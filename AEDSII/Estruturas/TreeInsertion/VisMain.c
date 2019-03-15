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

/*
 * Finds the largest key of the tree, and stores it in the global variable
 * largestKey. This variable is updated within the auxiliary function
 * getLargestKey_aux.
 */
int largestKey;

void getLargestKey_aux(Apontador p) {
  if (p->Reg.Chave > largestKey)
    largestKey = p->Reg.Chave;
}

int getLargestKey(Apontador p) {
  largestKey = 0;
  Central(p, &getLargestKey_aux);
  return largestKey;
}

/*
 * Finds the number of leaves in this tree, accumulating the answer in the
 * global variable "numLeaves".
 * @global numLeaves: the accumulator for the number of leaves in the tree.
 * @param p: the root of the subtree that we are investigating.
 */
int numLeaves;

void getNumLeaves_aux(Apontador p) {
  if (!p->Esq)
    numLeaves++;
  if (!p->Dir)
    numLeaves++;
}

int getNumLeavesAcc(Apontador p) {
  numLeaves = 0;
  Central(p, &getNumLeaves_aux);
  return numLeaves;
}

/*
 * Finds the number of leaves in the tree, in a more functional style.
 * @param p: the root of the subtree that we are investigating.
 * @return the number of leaves in the tree rooted in p.
 */
int getNumLeavesFun(Apontador p) {
  return (p->Dir ? getNumLeavesFun(p->Dir) : 1)
    + (p->Esq ? getNumLeavesFun(p->Esq) : 1);
}

// Generate random keys to fill up the tree.
//
#define MAX 10

TipoChave gen(const int MAX_KEY) {
  return random() % MAX_KEY + 1;
}

int main() {
  Apontador D;
  Inicializa(&D);
  int i;
  // Inserts elements in the tree.
  printf("Inserting:\n");
  for (i = 0; i < MAX; i++) {
    Registro Reg;
    Reg.Chave = gen(16);
    if (Insere(Reg, &D))
      printf("%4s%4d", "+", Reg.Chave);
    else
      printf("%4s%4d", "*", Reg.Chave);
  }
  // Searches elements in the tree.
  printf("\nSearching:\n");
  for (i = 0; i < MAX; i++) {
    TipoChave Chave = i;
    if (Pesquisa(Chave, D))
      printf("%4d%4s", i, "+");
    else
      printf("%4d%4s", i, "-");
  }
  // Visits every key in the tree.
  printf("\nPre-Order:\n");
  Central(D, &visita);
  // Gets the largest key:
  printf("\nLargest key = %d\n", getLargestKey(D));
  // Prints the number of leaves in the tree using the accumulator.
  printf("\nNum leaves (Acc) = %d\n", getNumLeavesAcc(D));
  // Prints the number of leaves in the tree using the functional style.
  printf("\nNum leaves (Fun) = %d\n", getNumLeavesFun(D));
}
