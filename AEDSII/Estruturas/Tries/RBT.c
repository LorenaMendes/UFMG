#include <stdlib.h>

#include "Tree.h"

typedef enum colorType {
    Red, Black
} colorType;

struct No {
  Apontador esq;
  Apontador dir;
  colorType color;
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
 
static Apontador NullNode = NULL;

void Central(Apontador T, void (*visitor)(Apontador)) {
  if (T != NullNode) {
    Central(T->esq, visitor);
    (*visitor)(T);
    Central(T->dir, visitor);
  }
}

Registro* pesquisa(Apontador p, int chave) {
  if (p == NullNode)
    return NULL;
  else if (chave < p->reg->chave)
    return pesquisa(p->esq, chave);
  else if (chave > p->reg->chave)
    return pesquisa(p->dir, chave);
  else
    return p->reg;
}

void makeNull(Apontador T) {
  T->esq = T->dir = NullNode;
  T->color = Black;
  T->reg = (Registro*)malloc(sizeof(Registro));
}

void inicializa(Apontador *p) {
  if (NullNode == NULL) {
    NullNode = malloc(sizeof (struct No));
    makeNull(NullNode);
  }
  *p = malloc(sizeof (struct No));
  makeNull(*p);
}

static Apontador MakeEmptyRec(Apontador T) {
  if (T != NullNode) {
    MakeEmptyRec(T->esq);
    MakeEmptyRec(T->dir);
    free(T);
  }
  return NullNode;
}

Apontador MakeEmpty(Apontador T) {
  T->dir = MakeEmptyRec(T->dir);
  return T;
}

static Apontador SingleRotateWithesq(Apontador K2) {
  Apontador K1;
  K1 = K2->esq;
  K2->esq = K1->dir;
  K1->dir = K2;
  return K1;
}

static Apontador SingleRotateWithdir(Apontador K1) {
  Apontador K2;
  K2 = K1->dir;
  K1->dir = K2->esq;
  K2->esq = K1;
  return K2;
}

static Apontador Rotate(int Item, Apontador Parent) {
  if (Item < Parent->reg->chave)
    return Parent->esq =
      Item < Parent->esq->reg->chave ?
      SingleRotateWithesq(Parent->esq) :
      SingleRotateWithdir(Parent->esq);
  else
    return Parent->dir =
      Item < Parent->dir->reg->chave ?
      SingleRotateWithesq(Parent->dir) :
      SingleRotateWithdir(Parent->dir);
}

static Apontador X, P, GP, GGP;

static void HandleReorient(int Item, Apontador T) {
  X->color = Red;
  X->esq->color = Black;
  X->dir->color = Black;
  if (P->color == Red) {
    GP->color = Red;
    if ((Item < GP->reg->chave) != (Item < P->reg->chave))
      P = Rotate(Item, GP);
    X = Rotate(Item, GGP);
    X->color = Black;
  }
  T->dir->color = Black; /* Make root black */
}

Apontador insere_aux(Registro *Item, Apontador T) {
  X = P = GP = T;
  NullNode->reg->chave = Item->chave;
  while (X->reg->chave != Item->chave) /* Descend down the tree */ {
    GGP = GP;
    GP = P;
    P = X;
    if (Item->chave < X->reg->chave)
      X = X->esq;
    else
      X = X->dir;
    if (X->esq->color == Red && X->dir->color == Red)
      HandleReorient(Item->chave, T);
  }
  if (X != NullNode) {
    makeNull(NullNode);
    return T; /* Duplicate */
  }
  X = malloc(sizeof(struct No));
  X->reg = Item;
  X->esq = X->dir = NullNode;
  if (Item->chave < P->reg->chave) /* Attach to its parent */
    P->esq = X;
  else
    P->dir = X;
  HandleReorient(Item->chave, T); /* color it red; maybe rotate */
  makeNull(NullNode);
  return T;
}

void insere(Apontador *p, Registro *reg) {
  *p = insere_aux(reg, *p);
}
