#include <stdio.h>

#include "Search.h"

void Inicializa(Tabela *T) {      
  T->n = 0;
}

int Pesquisa(TipoChave x, Tabela *T) {        
  int i;
  T->Item[0].Chave = x;
  i = T->n + 1;
  do {
    i--;
  }  while (T->Item[i].Chave != x);
  return i;
}

int Binaria(TipoChave x, Tabela *T) {
  if (T->n == 0)
    return 0;
  else {
    int i;
    int Esq = 1; 
    int Dir = T->n; 
    do { 
      i = (Esq + Dir) / 2; 
      if (x > T->Item[i].Chave) 
        Esq = i + 1;
      else 
        Dir = i - 1;
    } while ((x != T->Item[i].Chave) && (Esq <= Dir));
    return x == T->Item[i].Chave ? i : 0;
  }
}

void Insere(Registro Reg, Tabela *T) { 
  if (MAX == T->n)
    fprintf(stderr, "Erro : tabela cheia\n");
  else {
    T->n++;
    T->Item[T->n] = Reg;
  }
}

void Remove(TipoChave x, Tabela *T) {
  int idx = Pesquisa(x, T);
  if (idx != 0)
    T->Item[idx] = T->Item[T->n--];
}
