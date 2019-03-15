#ifndef _TREE_H
#define _TREE_H

typedef int TipoChave;                               
                    
typedef struct Registro {                   
  TipoChave Chave;                                
  /* outros componentes */
} Registro;                                        

typedef struct No *Apontador;        

typedef struct No {
  Registro Reg;
  Apontador Esq, Dir;
} No;

/*
 * Inicialize the tree, setting its root pointer to null.
 * @param Dicionario: the tree to be initialized.
 */
void Inicializa(Apontador *Dicionario);

/*
 * Searches the tree for a given key.
 * @param Chave: the key we want to find.
 * @param p: the tree where we shall run the search.
 * @return 1 if the key is in the tree, and zero otherwise.
 */
int Pesquisa(TipoChave Chave, Apontador p);

/*
 * Inserts one element in the tree.
 * @param x: the element to be inserted.
 * @param p: the tree that we will update.
 * @return 1 if the element has been inserted, and zero if it was already there.
 */
int Insere(Registro x, Apontador *p);

/*
 * Runs an in-order traversal of the tree.
 * @param p: the root of the tree where we shall start the visit.
 * @param visitante: a function that shall be invoked on each key of the tree
 * during the traversal.
 */
void Central(Apontador p, void (*visitante)(Apontador p));

/*
 * Remove a node from the tree, replacing it with its rightmost descendant from
 * the left subtree.
 * @param x: the key that we want to remove from the tree.
 * @param p: a pointer to the tree that we are modifying.
 * @return 1 if the element was in the tree and was removed, and 0 otherwise.
 */
int Retira(TipoChave x, Apontador *p);

#endif
