#include <string.h>
#include <stdlib.h>

#include "Set.h"

struct set_concrete {
  int* array;
  int capacity;
  int counter;
};

#define INIT_CAPACITY 1024

void initialize(Set* s) {
  *s = (Set)malloc(sizeof(struct set_concrete));
  (*s)->array = (int*)malloc(INIT_CAPACITY * sizeof(int));
  (*s)->capacity = INIT_CAPACITY;
  (*s)->counter = 0;
}

void insert(Set s, int element) {
  if (s->counter >= s->capacity) {
    s->capacity *= 2;
    int* aux = (int*)malloc(s->capacity * sizeof(int));
    memcpy(aux, s->array, sizeof(int) * s->capacity);
    free(s->array);
    s->array = aux;
  }
  s->array[s->counter++] = element;
}

int contains(Set s, int element) {
  for (int i = 0; i < s->counter; i++) {
    if (s->array[i] == element) {
      return 1;
    }
  }
  return 0;
}

void close(Set s) {
  free(s->array);
  free(s);
}
