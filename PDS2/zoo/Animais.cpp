#include "Animal.hpp"
#include <iostream>

void Animal::setNome(string novoNome){
	this->nome = novoNome;
}

string Animal::getNome(){
	return this->nome;
}

void Animal::setPeso(int novoPeso, int novaData){
	this->peso = novoPeso;
	this->dataPesagem = novaData;
}

int Animal::getPeso(){
	return this->peso;
}

int Animal::getTempoPesagem(int hoje){
	return hoje - this->dataPesagem;
}