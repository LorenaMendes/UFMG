/*
 * This program shows different ways to compute the largest integer number in
 * the C programming language.
 */

#include <stdio.h>
#include <limits.h>

int use_limits() {
  return INT_MAX;
}

int use_bitwise_arith() {
  unsigned int i = ~0U >> 1;
  return i;
}

int use_bin_search() {
  int acc = 1;
  int inc = 1;
  while (1) {
    if (acc + inc < 0) {
      if (inc == 1)
        return acc;
      else {
        inc = 1;
      }
    } else {
      acc += inc;
      inc *= 2;
    }
  }
}

int main() {
  printf("use_limits = %d\n", use_limits());
  printf("use_bitwise_arith = %d\n", use_bitwise_arith());
  printf("use_bin_search = %d\n", use_bin_search());
}
