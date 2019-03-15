#include <stdlib.h>

#include "Tree.h"

struct No {
  Apontador esq;
  Apontador dir;
  Registro *reg;
};

Registro* getReg(Apontador p) {
  return p->reg;
}

Apontador getEsq(Apontador p) {
  return p->esq;
}

Apontador getDir(Apontador p) {
  return p->dir;
}

void Central(Apontador p, void (*visitante)(Apontador p)) {
  if (p == NULL) return;
  Central(p->esq, visitante);
  (*visitante)(p);
  Central(p->dir, visitante);
}

void inicializa(Apontador *trie) {
  *trie = NULL;
}

Apontador cria_trie(struct registro *reg) {
  Apontador p = (Apontador)malloc(sizeof(struct No));
  p->esq = NULL;
  p->dir = NULL;
  p->reg = reg;
  return p;
}

unsigned int digito(int chave, int index) {
  int bit = 1 << index;
  return chave & bit ? 1 : 0;
}

Registro *pesquisaR(Apontador t, int chave, int p) {
  if (t == NULL)
    return NULL; 
  if (t->esq == NULL && t->dir == NULL) {
    int regchave = t->reg->chave;
    if (regchave == chave) {
      return t->reg;
    } else {
      return NULL;
    }
  }
  if (digito(chave, p) == 0) {
    return pesquisaR(t->esq, chave, p+1);
  } else {
    return pesquisaR(t->dir, chave, p+1);
  }
}

Registro *pesquisa(Apontador trie, int chave) {
  return pesquisaR(trie, chave, 0);
}

Apontador separa(Apontador no1, Apontador no2, int p) {
  Apontador novo = cria_trie(NULL);
  int d1 = digito(no1->reg->chave, p);
  int d2 = digito(no2->reg->chave, p);
  if (d1 == 0 && d2 == 0){
    novo->esq = separa(no1, no2, p+1);
  } else if (d1 == 0 && d2 == 1) {
    novo->esq = no1;
    novo->dir = no2;
  } else if (d1 == 1 && d2 == 0) {
    novo->dir = no1;
    novo->esq = no2;
  } else if (d1 == 1 && d2 == 1) {
    novo->dir = separa(no1, no2, p+1);
  }
  return novo;
}

Apontador insereR(Apontador t, Registro *reg, int p) {
  int chave = reg->chave;
  if (t == NULL)
    return cria_trie(reg);
  else if (t->reg && t->reg->chave == reg->chave)
    return t;
  else if (t->esq == NULL && t->dir == NULL)
    return separa(cria_trie(reg), t, p);
  else {
    if (digito(chave, p) == 0)
      t->esq = insereR(t->esq, reg, p+1);
    else
      t->dir = insereR(t->dir, reg, p+1);
    return t;
  }
}

void insere(Apontador *trie, Registro *reg) {
  *trie = insereR(*trie, reg, 0);
}

void MakeEmpty(Apontador t) {
  if (t != NULL) {
    MakeEmpty(t->esq);
    MakeEmpty(t->dir);
    free(t);
  }
}
