/*
 * This file implements a Set datatype, using a sorted array to this end.
 * We sort the array whenever we must answer a 'contains' query. We keep the
 * status of the array (sorted or not), and only sort it if it was not sorted
 * before. The array goes from sorted to unsorted whenever we insert something
 * into the set. We use quicksort to sort, and binary search to search. 
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

void swap(int* a, int* b) {
  int t = *a;
  *a = *b;
  *b = t;
}

int partition (int arr[], const int low, const int high) {
  int pivot = arr[high];
  int i = (low - 1);

  for (int j = low; j <= high - 1; j++) {
    if (arr[j] <= pivot) {
      i++;
      swap(&arr[i], &arr[j]);
    }
  }
  swap(&arr[i + 1], &arr[high]);
  return i + 1;
}

void sort(int arr[], const int low, const int high) {
  if (low < high) {
    int pi = partition(arr, low, high);
    sort(arr, low, pi - 1);
    sort(arr, pi + 1, high);
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
    sort(s->array, 0, s->counter);
    s->sorted = 1;
  }
  return binSearch(element, s->array, s->counter);
}

void close(Set s) {
  free(s->array);
  free(s);
}
