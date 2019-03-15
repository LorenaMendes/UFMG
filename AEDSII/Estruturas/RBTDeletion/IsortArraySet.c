/*
 * This file implements a Set datatype, using a sorted array to this end.
 * We sort the array whenever we must answer a 'contains' query. We keep the
 * status of the array (sorted or not), and only sort it if it was not sorted
 * before. The array goes from sorted to unsorted whenever we insert something
 * into the set. We use insertion sort to sort, and binary search to search. 
 *
 * Author: fernando@dcc.ufmg.br
 * Date: October 31st, 2017
 */

#include <string.h>
#include <stdlib.h>

#include "Set.h"

struct set_concrete {
  int* array;
  int capacity;
  int counter;
  int sorted;
};

#define INIT_CAPACITY 1024

void initialize(Set* s) {
  *s = (Set)malloc(sizeof(struct set_concrete));
  (*s)->array = (int*)malloc(INIT_CAPACITY * sizeof(int));
  (*s)->capacity = INIT_CAPACITY;
  (*s)->counter = 0;
  (*s)->sorted = 1;
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
  s->sorted = 0;
}

void sort(int* array, int N) {
  int i, j;
  for (i = 0; i < N - 1; i++) {
    for (j = i+1; j < N; j++) {
      if (array[i] > array[j]) {
        int tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
      }
    }
  }
}

int binSearch(const int x, const int* T, const int N) {
  if (!N) {
    return 0;
  } else {
    int i;
    int Esq = 1;
    int Dir = N;
    do {
      i = Esq + (Dir-Esq)/2;
      if (x > T[i])
        Esq = i + 1;
      else
        Dir = i - 1;
    } while ((x != T[i]) && (Esq <= Dir));
    return x == T[i] ? i : 0;
  }
}

int contains(Set s, int element) {
  if (!s->sorted) {
    sort(s->array, s->counter);
    s->sorted = 1;
  }
  return binSearch(element, s->array, s->counter);
}

void close(Set s) {
  free(s->array);
  free(s);
}
