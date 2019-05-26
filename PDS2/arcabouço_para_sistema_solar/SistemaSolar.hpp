#ifndef SISTEMA_SOLAR_H
#define SISTEMA_SOLAR_H

#include "Planeta.hpp"
#include "Astro.hpp"
#include <string>
#include <list>

class SistemaSolar {
private:
	list <Planeta*> planetas;
	int num_planetas;
	list <Astro*> estrelas;
	int num_estrelas;

public:
	SistemaSolar() {num_planetas = 0; num_estrelas = 0;}
	void inserePlaneta(Planeta*);
	void insereEstrela(Astro*);
	list<Planeta*> getListaPlanetas();
	list<Astro*> getListaEstrelas();
	Planeta* getPlaneta(string);
	Astro* maiorEstrela();
	int getNumPlanetasSolidos();
	Planeta* getPlanetaComMaisLuas();
	Planeta* getPlanetaMaisQuente();
	Planeta* getPlanetaMaisFrio();
	Planeta* getPlanetaMaiorRaio();
	Planeta* getPlanetaMenorRaio();
};

#endif