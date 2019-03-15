#include <stdlib.h>

#include "Tree.h"

void Inicializa(Apontador *Dicionario) {
  *Dicionario = NULL;
}

int Pesquisa(TipoChave Chave, Apontador p) { 
  if (p == NULL)
    return 0;
  else if (Chave < p->Reg.Chave)
    return Pesquisa(Chave, p->Esq);
  else if (Chave > p->Reg.Chave)
    return Pesquisa(Chave, p->Dir);
  else
    return 1;
}

int Insere(Registro x, Apontador *p)  { 
  if (*p == NULL)  { 
    *p = (Apontador) malloc (sizeof(No));
    (*p)->Reg = x;  
    (*p)->Esq = NULL; 
    (*p)->Dir = NULL;
    return 1;
  }
  else if (x.Chave < (*p)->Reg.Chave)
    return Insere(x, &(*p)->Esq);
  else if (x.Chave > (*p)->Reg.Chave)
    return Insere(x, &(*p)->Dir);
  else
    return 0;
}

void Central(Apontador p, void (*visitante)(Apontador p)) { 
  if (p == NULL) return;
  Central(p->Esq, visitante);
  (*visitante)(p);
  Central(p->Dir, visitante);
}
