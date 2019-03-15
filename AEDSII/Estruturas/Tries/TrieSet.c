#include <stdlib.h>

#include "Set.h"
#include "Trie.h"

struct set_concrete {
  struct no* T;
};

void initialize(Set* s) {
  *s = (Set)malloc(sizeof(struct set_concrete));
  (*s)->T = NULL;
}

void insert(Set s, int i) {
  Insert(i, s->T);
}

int contains(Set s, int i) {
  return Contains(i, s->T);
}

void close(Set s) {
  MakeEmpty(s->T);
}
