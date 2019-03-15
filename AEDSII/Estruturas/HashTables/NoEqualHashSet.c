/*
 * This file implements a set of integers using a hash table. The only
 * difference to HashSet is that we do not allow duplicates in this case.
 *
 * Author: fernando@dcc.ufmg.br
 * Date: November 3rd, 2017
 */

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#include "Set.h"

struct node {
  Key key;
  struct node *next;
};

struct set_concrete {
  struct node **table;
  size_t size;
};

#define TABLE_SIZE 0xFFFF

void initialize(Set* s) {
  *s = (Set)malloc(sizeof(struct set_concrete));
  (*s)->table = (struct node**)calloc(TABLE_SIZE + 1, sizeof(struct node*));
}

size_t hash(Key element) {
  return element & TABLE_SIZE;
}

void insert(Set s, Key element) {
  struct node* it;
  size_t h = hash(element);
  if (!contains(s, element)) {
    it = malloc(sizeof *it);
    it->key = element;
    it->next = s->table[h];
    s->table[h] = it;
  }
}

int contains(Set s, Key element) {
  size_t h = hash(element);
  if (s->table[h]) {
    struct node *it = s->table[h];
    while (it) {
      if (it->key == element)
        return 1;
      else
        it = it->next;
    }
  }
  return 0;
}

void close(Set s) {
  int num_cells = 0;
  int max_cells = 0;
  int min_cells =INT_MAX;
  int num_emptys = 0;
  for (int i = 0; i < TABLE_SIZE; i++) {
    int counter = 0;
    struct node *j = s->table[i];
    if (!j)
      num_emptys++;
    while (j) {
      struct node *aux = j;
      j = j->next;
      free(aux);
      counter++;
    }
    if (counter > max_cells)
      max_cells = counter;
    if (counter < min_cells)
      min_cells = counter;
    num_cells += counter;
  }
  free(s->table);
  free(s);
  printf("\nTable size = %d\nNum Cells = %d\nNum empty cells = %d\nAvg size = %lf\nMax list = %d\nMin list = %d\n",
      TABLE_SIZE, num_cells, num_emptys, ((double)num_cells)/TABLE_SIZE, max_cells, min_cells);
}
