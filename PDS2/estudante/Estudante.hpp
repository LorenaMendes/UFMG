#ifndef ESTUDANTE_H
#define ESTUDANTE_H

#include <string>

struct Estudante {
	std::string nome;
	long matricula;
	float notas[5];

	float calcularRSG();
};

#endif