#include "Tree.h"
#include "RBT.h"
#include "TreeGen.h"

#include <stdio.h>
#include <stdlib.h>

Apontador genDegenerateTree(const int NUM_NODES) {
  static TipoChave t = 0;
  int i;
  Apontador D;
  Inicializa(&D);
  for (i = 0; i < NUM_NODES; i++) {
    Registro Reg;
    Reg.Chave = t++;
    Insere(Reg, &D);
  }
  return D;
}

Apontador genRandomTree(const int NUM_NODES, const int MAX_KEY) {
  Apontador D;
  Inicializa(&D);
  int i;
  for (i = 0; i < NUM_NODES; i++) {
    Registro Reg;
    Reg.Chave = random() % MAX_KEY + 1;
    Insere(Reg, &D);
  }
  return D;
}

RedBlackTree genDegenerateRBT(const int NUM_NODES) {
  static TipoChave t = 0;
  int i;
  RedBlackTree T;
  T = Initialize();
  for (i = 0; i < NUM_NODES; i++) {
    T = Insert(t++, T);
  }
  return T;
}

RedBlackTree genRandomRBT(const int NUM_NODES, const int MAX_KEY) {
  int i;
  RedBlackTree T;
  T = Initialize();
  for (i = 0; i < NUM_NODES; i++) {
    ElementType elem = random() % MAX_KEY + 1;
    T = Insert(elem, T);
  }
  return T;
}
