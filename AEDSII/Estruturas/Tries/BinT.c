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

void inicializa(Apontador *tree) {
  *tree = NULL;
}

Registro* pesquisa(Apontador p, int chave) { 
  if (p == NULL)
    return NULL;
  else if (chave < p->reg->chave)
    return pesquisa(p->esq, chave);
  else if (chave > p->reg->chave)
    return pesquisa(p->dir, chave);
  else
    return p->reg;
}

void insere(Apontador *p, Registro *x)  { 
  if (*p == NULL)  { 
    *p = (Apontador) malloc (sizeof(struct No));
    (*p)->reg = x;  
    (*p)->esq = NULL; 
    (*p)->dir = NULL;
  } else if (x->chave < (*p)->reg->chave) {
    return insere(&(*p)->esq, x);
  } else if (x->chave > (*p)->reg->chave) {
    return insere(&(*p)->dir, x);
  }
}
