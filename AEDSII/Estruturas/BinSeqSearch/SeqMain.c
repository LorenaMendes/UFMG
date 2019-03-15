/******************************************************************************
  This program shows how the sequential search works. We shall generate random
  keys in ascending order, and shall insert them into a table. After that, we
  shall look for these keys.
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "Search.h"

TipoChave gen() {
  static const int MAX_KEY = 100;
  return random() % MAX_KEY + 1;
}

int main() {
  Tabela T;
  Inicializa(&T);
  int i;
  printf("Inserting:\n");
  for (i = 0; i < MAX; i++) {
    Registro Reg;
    Reg.Chave = gen();
    printf("%8d", Reg.Chave);
    Insere(Reg, &T);
  }
  printf("\nSearching:\n");
  for (i = 0; i < MAX; i++) {
    if (Pesquisa(i, &T))
      printf("%4d%4s", i, "+");
    else
      printf("%4d%4s", i, "-");
  }
  printf("\nDone!\n");
}
