#include <stdio.h>
#include <stdlib.h>

#include "Tree.h"

// Flatten the tree into an array
int* V;
int N;
void tree2array_aux(Apontador p) {
  V[N++] = p->Reg.Chave;
}
int* tree2array(Apontador p, int size) {
  V = (int*)malloc(size * sizeof(int));
  N = 0;
  Central(p, &tree2array_aux);
  return V;
}

// Prints the trees in dot format into file:
//
FILE *file;

void printDot_aux(Apontador p) {
  if (p->Esq)
    fprintf(file, "  %d -> %d\n", p->Reg.Chave, p->Esq->Reg.Chave);
  if (p->Dir)
    fprintf(file, "  %d -> %d\n", p->Reg.Chave, p->Dir->Reg.Chave);
}

void printDot(Apontador p, const char* file_name) {
  file = fopen(file_name, "w");
  fprintf(file, "\ndigraph tree {\n");
  Central(p, &printDot_aux);
  fprintf(file, "\n}\n");
  fclose(file);
}

// Prints the tree:
//
void visita(Apontador p) {
  printf("Key = %8d, Dir? = %d, Esq? = %d\n", p->Reg.Chave, p->Dir != NULL,
      p->Esq != NULL);
}

// Tranforms the array into a tree in O(N):
Apontador array2tree(int* A, int L, int R)  {
  if (L > R) {
    return NULL;
  } else {
    Apontador p = (Apontador) malloc (sizeof(No));
    int mid = L + (R - L)/2;
    p->Reg.Chave = A[mid];
    p->Esq = array2tree(A, L, mid - 1);
    p->Dir = array2tree(A, mid+1, R);
    return p;
  }
}

// Merges two sorted arrays
int* merge(int* A1, int N1, int* A2, int N2, int* size_array) {
  int* A = (int*) malloc(sizeof(int) * (N1 + N2));
  int i1 = 0, i2 = 0, ia = 0;
  while (i1 < N1 && i2 < N2) {
    if (A1[i1] < A2[i2])
      A[ia++] = A1[i1++];
    else if (A1[i1] > A2[i2])
      A[ia++] = A2[i2++];
    else {
      A[ia++] = A2[i2++];
      i1++;
    }
  }
  while (i1 < N1) {
    A[ia++] = A1[i1++];
  }
  while (i2 < N2) {
    A[ia++] = A2[i2++];
  }
  *size_array = ia;
  return A;
}

// Generate random keys to fill up the tree.
//
TipoChave gen(const int MAX_KEY) {
  return random() % MAX_KEY + 1;
}

Apontador createTree(const int NUM_KEYS, int* size_tree) {
  Apontador D;
  Inicializa(&D);
  for (int i = 0; i < NUM_KEYS; i++) {
    Registro Reg;
    Reg.Chave = gen(NUM_KEYS * 2);
    *size_tree += Insere(Reg, &D);
  }
  return D;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "Syntax: %s num_keys\n", argv[0]);
    exit(1);
  } else {
    // Create two trees:
    int size_tree1 = 0;
    Apontador T1 = createTree(atoi(argv[1]), &size_tree1);
    int size_tree2 = 0;
    Apontador T2 = createTree(atoi(argv[1]), &size_tree2);

    // Flatten the trees into an array:
    int* A1 = tree2array(T1, size_tree1);
    int* A2 = tree2array(T2, size_tree2);

    // Merges the two arrays into a big array:
    int size_treeM = 0;
    int* AM = merge(A1, size_tree1, A2, size_tree2, &size_treeM);

    // Transform the merged array back into a tree
    Apontador TM = array2tree(AM, 0, size_treeM - 1);

    // Pretty prints the trees:
    printDot(T1, "T1.dot");
    printDot(T2, "T2.dot");
    printDot(TM, "TM.dot");
  }
}
