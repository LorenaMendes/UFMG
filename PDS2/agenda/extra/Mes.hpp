#ifndef MES_H
#define MES_H
#include "Dia.hpp"
using namespace std;
#include <iostream>

typedef struct Mes{
	string nome;
	int id;
	int numero_dias;
	Dia* vetor_dias;
	Mes* seg;

	Mes(string, int, int);
	void ImprimeMeses();
} Mes;

#endif