#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  if (argc != 3) {
    fprintf(stderr, "Syntax: %s table_size num_keys\n", argv[0]);
    return 1;
  } else {
    const int TBL_SIZE = atoi(argv[1]);
    const int NUM_KEYS = atoi(argv[2]);
    double num_empties = (double)TBL_SIZE;
    for (double i = 0.0; i < NUM_KEYS; i++) {
      num_empties *= (1.0 - 1.0/TBL_SIZE);
    }
    printf("\nTable size = %d\nNum keys = %d\nExpected empties = %lf\n",
        TBL_SIZE, NUM_KEYS, num_empties);
    return 0;
  }
}
