#include <stdio.h>
#include <limits.h>

/*
 * This program prints a few numeric bounds used in scalar types in C.
 * For the full list of bounds, see the limits.h header file, available at
 * https://en.wikibooks.org/wiki/C_Programming/limits.h
 */
int main() {
  printf("%d\n", INT_MAX);
  printf("%u\n", UINT_MAX);
  printf("%lu\n", ULONG_MAX);
}
