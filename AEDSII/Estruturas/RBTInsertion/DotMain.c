#include <stdio.h>
#include <stdlib.h>

#include "RBT.h"
#include "Tree.h"
#include "TreeGen.h"

void printDot_aux(RedBlackTree p) {
  if (p->Color == Red) {
    printf("  %d [style=filled fillcolor=red];\n", p->Element);
  }
  if (p->Left)
    printf("  %d -> %d;\n", p->Element, p->Left->Element);
  if (p->Right)
    printf("  %d -> %d;\n", p->Element, p->Right->Element);
}

void printDot(RedBlackTree p) {
  printf("\ndigraph tree {\n");
  Central_RBT_Header(p, &printDot_aux);
  printf("\n}\n");
}

int main(int argc, char** argv) {
  if (argc < 2) {
    fprintf(stderr, "Syntax: %s num_nodes\n", argv[0]);
  } else {
    const int num_nodes = atoi(argv[1]);
    RedBlackTree T = genRandomRBT(num_nodes, 100);
    printDot(T);
  }
}
