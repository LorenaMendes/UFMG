/*
 * This file implements a set as a red-black tree.
 *
 * author: fernando@dcc.ufmg.br
 * Date: October 31st, 2017
 */

#include <stdlib.h>

#include "Set.h"
#include "RBT.h"

struct set_concrete {
  RedBlackTree T;
};

void initialize(Set* s) {
  *s = (Set)malloc(sizeof(struct set_concrete));
  (*s)->T = Initialize();
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
