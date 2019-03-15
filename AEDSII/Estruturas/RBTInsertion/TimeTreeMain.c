#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "Tree.h"
#include "RBT.h"
#include "TreeGen.h"

void print(ElementType e) {
  printf("%d\n", e);
}

int  main(int argc, char** argv) {
  if (argc < 3) {
    fprintf(stderr, "Syntax: %s num_nodes [opts]\n", argv[0]);
    fprintf(stderr, " where opts is\n");
    fprintf(stderr, "  0:tr-degen\n  1:tr-rand\n  2:rbt-gen\n  3:rbt-rand\n");
  } else {
    clock_t start, end;
    const int num_nodes = atoi(argv[1]);
    const int tree_option = atoi(argv[2]);
    start = clock();
    switch(tree_option) {
      case 0: {
        genDegenerateTree(num_nodes);
        break;
      }
      case 1: {
        genRandomTree(num_nodes, 5 * num_nodes);
        break;
      }
      case 2: {
        genDegenerateRBT(num_nodes);
        break;
      }
      case 3: {
        genRandomRBT(num_nodes, 5 * num_nodes);
        break;
      }
      default:
        fprintf(stderr, "Unknown option: %d\n", tree_option);
    }
    end = clock();
    fprintf(stderr, "%lf\n", ((double)(end - start))/CLOCKS_PER_SEC);
  }
}
