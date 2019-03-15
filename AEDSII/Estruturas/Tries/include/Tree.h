#ifndef _TRIE_H
#define _TRIE_H

typedef struct registro {
  int chave;
  /* outros dados */
} Registro;

typedef struct No *Apontador;

Registro* getReg(Apontador p);

Apontador getEsq(Apontador p);

Apontador getDir(Apontador p);

void inicializa(Apontador *trie);

Registro *pesquisa(Apontador p, int chave);

void insere(Apontador *trie, Registro *reg);

void Central(Apontador p, void (*visitante)(Apontador p));

#endif
