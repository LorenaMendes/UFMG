#include <time.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#include "Tree.h"

/*
 * Get the height of the tree:
 */
int get_height(Apontador p) {
  Apontador esq_p = getEsq(p);
  Apontador dir_p = getDir(p);
  int esq_height = esq_p && esq_p != p ? get_height(esq_p) : 0;
  int dir_height = dir_p && dir_p != p ? get_height(dir_p) : 0;
  return (esq_height > dir_height ? esq_height : dir_height) + 1;
}

/*
 * Counts the number of nodes of the tree:
 */
int num_nodes;
void get_num_nodes_aux(Apontador p) {
  num_nodes++;
}
int get_num_nodes(Apontador p) {
  num_nodes = 0;
  Central(p, &get_num_nodes_aux);
  return num_nodes;
}

int genR(const int MAX_KEY) { return random() % MAX_KEY + 1; }

int genA(const int MAX_KEY) {
  static int counter = 0;
  counter += random() % 4;
  return counter % MAX_KEY + 1;
}

/*
 * Generates a tree:
 */
Apontador gen_tree(const int MAX_NUM_KEYS) {
  Apontador T;
  inicializa(&T);
  for (int i = 0; i < MAX_NUM_KEYS; i++) {
    Registro *reg = (Registro*) malloc(sizeof(Registro));
    reg->chave = genA(MAX_NUM_KEYS);
    insere(&T, reg);
  }
  return T;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "Syntaxe: %s num_nodes\n", argv[0]);
    return 1;
  } else {
    const int MAX_NUM_KEYS = atoi(argv[1]);
    clock_t start, end;
    start = clock();
    Apontador T = gen_tree(MAX_NUM_KEYS);
    end = clock();
    printf("%d, %d, %lf\n",
      get_height(T), get_num_nodes(T), ((double)(end - start))/CLOCKS_PER_SEC);
  }
}
