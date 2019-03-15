/*
 * This file implements a Set datatype, using a hash table with separate
 * chaining. Items that collidate are placed onto a linked list. 
 * We allow duplicate items per list.
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
  it = malloc(sizeof *it);
  it->key = element;
  it->next = s->table[h];
  s->table[h] = it;
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
  for (int i = 0; i < TABLE_SIZE; i++) {
    struct node *j = s->table[i];
    while (j) {
      struct node *aux = j;
      j = j->next;
      free(aux);
    }
  }
  free(s->table);
  free(s);
}
