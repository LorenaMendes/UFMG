#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#include "Tree.h"

/*
 * Generate a binary representation of the key.
 */
char* int2bin(int num) {
  // Remember: sizeof(char) == 1 always, always (defined in the C standard).
  int num_bits = CHAR_BIT * sizeof(int);
  char* str = (char*)malloc(num_bits + 1);
  str[num_bits] = '\0';
  for (int i = 0; i < num_bits; i++) {
    str[i] = num & (1 << i) ? '1' : '0';
  }
  return str;
}

/*
 * Prints the tree in dot format, using the auxiliary function printDot_aux.
 */
FILE* file;

void printDot_aux(Apontador p) {
  if (!(getReg(p))) {
    fprintf(file, "  %lu [shape = point];\n", (long)p);
  } else {
    fprintf(file, "  %lu [shape = box, label = \"%s(%d)\"];\n",
		    (long)p, int2bin(getReg(p)->chave), getReg(p)->chave);
  }
  if (getEsq(p))
    fprintf(file, "  %lu -> %lu [label = 0]\n", (long)p, (long)getEsq(p));
  if (getDir(p))
    fprintf(file, "  %lu -> %lu [label = 1]\n", (long)p, (long)getDir(p));
}

void printDot(Apontador p, char* file_name) {
  file = fopen(file_name, "w");
  fprintf(file, "\ndigraph tree {\n  graph[rankdir=LR]\n");
  Central(p, &printDot_aux);
  fprintf(file, "}\n");
}

int gen(const int MAX_KEY) {
  return random() % MAX_KEY + 1;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "Syntaxe: %s num_nodes\n", argv[0]);
    return 1;
  } else {
    Apontador T;
    inicializa(&T);
    int i;
    const int MAX_NUM_KEYS = atoi(argv[1]);
    //
    // Inserts elements in the tree.
    for (i = 0; i < MAX_NUM_KEYS; i++) {
      Registro *reg = (Registro*) malloc(sizeof(Registro));
      reg->chave = gen(MAX_NUM_KEYS);
      insere(&T, reg);
    }
    //
    // Print the tree in dot format:
    printDot(T, "file.dot");
    //
    // Searches elements in the tree.
    printf("\nSearching:\n");
    for (i = 0; i < MAX_NUM_KEYS; i++) {
      int chave = i;
      if (pesquisa(T, chave))
        printf("%4d%4s", i, "+");
      else
        printf("%4d%4s", i, "-");
    }
    printf("\n");
  }
}
