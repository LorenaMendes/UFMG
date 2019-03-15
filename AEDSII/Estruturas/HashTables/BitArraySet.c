/*
 * This file implements a Set datatype using a bitmap. The largest integer that
 * we can track is largest long.
 *
 * Author: fernando@dcc.ufmg.br
 * Date: November 3rd, 2017
 */

#include <string.h>
#include <limits.h>
#include <stdlib.h>

#include "Set.h"

#define WORD_SIZE  (8*sizeof(unsigned))
#define ARRAY_SIZE (UINT_MAX/WORD_SIZE)

struct set_concrete {
  unsigned* array;
};

void initialize(Set* s) {
  *s = (Set)malloc(sizeof(struct set_concrete));
  (*s)->array = (unsigned*)calloc(ARRAY_SIZE, sizeof(unsigned));
}

void insert(Set s, Key element) {
  unsigned index = element / WORD_SIZE;
  unsigned offset = element % WORD_SIZE;
  unsigned bit = 1 << offset;
  s->array[index] |= bit;
}

int contains(Set s, Key element) {
  unsigned index = element / WORD_SIZE;
  unsigned offset = element % WORD_SIZE;
  unsigned bit = 1 << offset;
  return s->array[index] & bit ? 1 : 0;
}

void close(Set s) {
  free(s->array);
  free(s);
}
