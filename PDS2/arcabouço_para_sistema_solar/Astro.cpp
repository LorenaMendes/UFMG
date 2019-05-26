#include "Astro.hpp"
#include <iostream>
#include <string>
using namespace std;

void Astro::setNome(string nome) {
	this->nome = nome;
}

string Astro::getNome() {
	return this->nome;
}

void Astro::setRaio(float raio) {
	this->raio = raio;
}

float Astro::getRaio() {
	return this->raio;
}

void Astro::setTemperatura(float temperatura) {
	this->temperatura = temperatura;
}

float Astro::getTemperatura() {
	return this->temperatura;
}

void Astro::setGravidade(float gravidade) {
	this->gravidade = gravidade;
}

float Astro::getGravidade() {
	return this->gravidade;
}

void Astro::setGasoso(bool gasoso) {
	this->gasoso = gasoso;
}

bool Astro::getGasoso() {
	return this->gasoso;
}

