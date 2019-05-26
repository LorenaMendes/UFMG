#ifndef DIA_H
#define DIA_H
#include "Compromisso.hpp"
#include <iostream>

typedef struct Dia{
	int id;
	int numero_compromissos;
	Compromisso * lista_compromissos;

	Dia(int);
} Dia;

#endif