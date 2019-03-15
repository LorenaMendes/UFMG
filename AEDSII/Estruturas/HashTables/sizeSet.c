#include <stdio.h>
#include <limits.h>

#define WORD_SIZE  (8*sizeof(unsigned))
#define ARRAY_SIZE (UINT_MAX/WORD_SIZE)

int array[ARRAY_SIZE];

int main() {
  unsigned long size = sizeof(array);
  printf("%lu\n", size);
}
