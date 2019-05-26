#ifndef COMPROMISSO_H
#define COMPROMISSO_H
using namespace std;
#include <iostream>

typedef struct Compromisso{
	string descricao;
	int horario;
	int dia;
	Compromisso* seg;

	Compromisso(string, int, int);
} Compromisso;

#endif