/*
 * This file implements a Set datatype, using an integer array to index the
 * elements. 
 *
 * Author: fernando@dcc.ufmg.br
 * Date: November 3rd, 2017
 */

#include <string.h>
#include <limits.h>
#include <stdlib.h>

#include "Set.h"

struct set_concrete {
  unsigned* array;
};

void initialize(Set* s) {
  *s = (Set)malloc(sizeof(struct set_concrete));
  (*s)->array = (unsigned*)calloc(UINT_MAX, sizeof(unsigned));
}

void insert(Set s, Key element) {
  s->array[(unsigned)element] = 1;
}

int contains(Set s, Key element) {
  unsigned index = element;
  return s->array[index];
}

void close(Set s) {
  free(s->array);
  free(s);
}
