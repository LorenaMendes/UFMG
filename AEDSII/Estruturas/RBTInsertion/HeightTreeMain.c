#include <stdio.h>
#include <stdlib.h>

#include "Tree.h"
#include "RBT.h"
#include "TreeGen.h"

#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))

void print(RedBlackTree T) {
  printf("Node(%p) = %d [%c]\n", T, T->Element, T->Color == Black ? 'b' : 'r');
}

int RBT_Black_Height(RedBlackTree T) {
  if (isNullNode(T)) {
    return 0;
  } else {
    int black_height_esq = RBT_Black_Height(T->Left);
    int black_height_dir = RBT_Black_Height(T->Right);
    // We check if T is not the Root (Element == NegInfinity)
    if (T->Element != NegInfinity && black_height_dir != black_height_esq) {
      printf("Error at node %d (%d vs %d)\n",
          T->Element, black_height_esq, black_height_dir);
    }
    return MAX(black_height_esq, black_height_dir) +
      (T->Color == Black ? 1 : 0);
  }
}

int RBT_Height(RedBlackTree T) {
  int height_esq = 0;
  int height_dir = 0;
  if (!isNullNode(T->Left))
    height_esq = RBT_Height(T->Left);
  if (!isNullNode(T->Right))
    height_dir = RBT_Height(T->Right);
  return MAX(height_esq, height_dir) + 1;
}

int Tree_Height(Apontador T) {
  int height_esq = 0;
  int height_dir = 0;
  if (T->Esq)
    height_esq = Tree_Height(T->Esq);
  if (T->Dir)
    height_dir = Tree_Height(T->Dir);
  return MAX(height_esq, height_dir) + 1;
}

int  main(int argc, char** argv) {
  if (argc < 3) {
    fprintf(stderr, "Syntax: %s num_nodes [opts]\n", argv[0]);
    fprintf(stderr, " where opts is\n");
    fprintf(stderr, "  0:tr-degen\n  1:tr-rand\n  2:rbt-gen\n  3:rbt-rand\n");
  } else {
    const int num_nodes = atoi(argv[1]);
    const int tree_option = atoi(argv[2]);
    switch(tree_option) {
      case 0: {
        Apontador P0 = genDegenerateTree(num_nodes);
        printf("Altura da arvore: %d\n", Tree_Height(P0));
        break;
      }
      case 1: {
        Apontador P1 = genRandomTree(num_nodes, 5 * num_nodes);
        printf("Altura da arvore: %d\n", Tree_Height(P1));
        break;
      }
      case 2: {
        RedBlackTree P2 = genDegenerateRBT(num_nodes);
        printf("Altura da arvore: %d\n", RBT_Height(P2));
        printf("Altura negra da arvore: %d\n", RBT_Black_Height(P2));
        break;
      }
      case 3: {
        RedBlackTree P3 = genRandomRBT(num_nodes, 5 * num_nodes);
        printf("Altura da arvore: %d\n", RBT_Height(P3));
        printf("Altura negra da arvore: %d\n", RBT_Black_Height(P3));
        break;
      }
      default:
        fprintf(stderr, "Unknown option: %d\n", tree_option);
    }
  }
}
