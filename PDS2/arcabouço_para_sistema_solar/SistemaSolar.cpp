#include "SistemaSolar.hpp"
#include <iostream>
#include <string>

void SistemaSolar::inserePlaneta(Planeta* planeta) {
	this->planetas.push_back(planeta);
	this->num_planetas++;
}

void SistemaSolar::insereEstrela(Astro* estrela) {
	this->estrelas.push_back(estrela);
	this->num_estrelas++;
}

list<Planeta*> SistemaSolar::getListaPlanetas() {
	return this->planetas;
}

list<Astro*> SistemaSolar::getListaEstrelas() {
	return this->estrelas;
}

Planeta* SistemaSolar::getPlaneta(string nome) {
	list <Planeta*>::iterator it;
	for (it = this->planetas.begin(); it != this->planetas.end(); ++it) {
		if ((*it)->getNome() == nome) return *it;
	}
	return NULL;
}

Astro* SistemaSolar::maiorEstrela() {
	list <Astro*>::iterator it;
	it = this->estrelas.begin();
	Astro* maior = *it;
	for (it = this->estrelas.begin(); it != this->estrelas.end(); ++it)
		if ((*it)->getRaio() > maior->getRaio()) maior = *it;
	return maior;
}

int SistemaSolar::getNumPlanetasSolidos() {
	int cont = 0;
	list <Planeta*>::iterator it;
	for (it = this->planetas.begin(); it != this->planetas.end(); ++it) {
		if (!(*it)->getGasoso()) cont++;
	}
	return cont;
}

Planeta* SistemaSolar::getPlanetaComMaisLuas() {
	list <Planeta*>::iterator it;
	it = this->planetas.begin();
	Planeta* mais_luas = *it;
	for (it = this->planetas.begin(); it != this->planetas.end(); ++it)
		if ((*it)->getNumLuas() > mais_luas->getNumLuas()) mais_luas = *it;
	return mais_luas;
}

Planeta* SistemaSolar::getPlanetaMaisQuente() {
	list <Planeta*>::iterator it;
	it = this->planetas.begin();
	Planeta* mais_quente = *it;
	for (it = this->planetas.begin(); it != this->planetas.end(); ++it)
		if ((*it)->getTemperatura() > mais_quente->getTemperatura()) mais_quente = *it;
	return mais_quente;
}

Planeta* SistemaSolar::getPlanetaMaisFrio() {
	list <Planeta*>::iterator it;
	it = this->planetas.begin();
	Planeta* mais_frio = *it;
	for (it = this->planetas.begin(); it != this->planetas.end(); ++it)
		if ((*it)->getTemperatura() < mais_frio->getTemperatura()) mais_frio = *it;
	return mais_frio;
}

Planeta* SistemaSolar::getPlanetaMaiorRaio() {
	list <Planeta*>::iterator it;
	it = this->planetas.begin();
	Planeta* maior_raio = *it;
	for (it = this->planetas.begin(); it != this->planetas.end(); ++it)
		if ((*it)->getRaio() > maior_raio->getRaio()) maior_raio = *it;
	return maior_raio;
}

Planeta* SistemaSolar::getPlanetaMenorRaio() {
	list <Planeta*>::iterator it;
	it = this->planetas.begin();
	Planeta* menor_raio = *it;
	for (it = this->planetas.begin(); it != this->planetas.end(); ++it)
		if ((*it)->getRaio() < menor_raio->getRaio()) menor_raio = *it;
	return menor_raio;
}