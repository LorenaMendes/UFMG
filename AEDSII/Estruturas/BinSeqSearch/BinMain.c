/******************************************************************************
  This program shows how the binary search works. We shall generate random keys
  in ascending order, and shall insert them into a table. After that, we shall
  look for these keys.
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "Search.h"

TipoChave gen() {
  static TipoChave counter = 0;
  static const int MAX_KEY = 5;
  counter += random() % MAX_KEY + 1;
  return counter;
}

int main() {
  Tabela T;
  Inicializa(&T);
  TipoChave maxKey;
  int i;
  printf("Inserting:\n");
  for (i = 0; i < MAX; i++) {
    Registro Reg;
    maxKey = Reg.Chave = gen();
    printf("%8d", Reg.Chave);
    Insere(Reg, &T);
  }
  printf("\nSearching:\n");
  for (i = 0; i < maxKey + 1; i++) {
    if (Binaria(i, &T))
      printf("%4d%4s", i, "+");
    else
      printf("%4d%4s", i, "-");
  }
  printf("\nDone!\n");
}
