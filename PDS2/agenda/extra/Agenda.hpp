#ifndef AGENDA_H
#define AGENDA_H
#include "Mes.hpp"
#include "Dia.hpp"
#include "Compromisso.hpp"

typedef struct Agenda{
	int ano;
	Mes * lista_mes;

	Agenda(int);
	void AdicionaMes(Mes*);
} Agenda;

#endif