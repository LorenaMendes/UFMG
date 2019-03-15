#ifndef BIN_H
#define BIN_H

# define MAX 80

typedef int TipoChave;

typedef struct {
  TipoChave Chave;
  /* Add other elements to be stored here. */
} Registro;

typedef struct {
  Registro Item[MAX + 1];
  int n;
} Tabela;

/*
 * Initializes a table T setting the number of elements to zero.
 * @param T: the table to be initialized.
 */
void Inicializa(Tabela *T);

/*
 * Inserts an element into the table.
 * @param Reg: the element to be inserted.
 * @param T: the table to be modified with the new element.
 */
void Insere(Registro Reg, Tabela *T);

/*
 * Finds an element within the table, using a sequential search.
 * @param x: the element to be found.
 * @param T: the table to be searched.
 * @return: the index of the element, or zero if not found.
 */
int Pesquisa(TipoChave x, Tabela *T);

/*
 * Finds an element within a sorted table, using a binary search.
 * @param x: the element to be found.
 * @param T: the table to be searched.
 * @return: the index of the element, or zero if not found.
 */
int Binaria(TipoChave x, Tabela *T);

#endif
