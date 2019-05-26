#include "Mes.hpp"
#include <iostream>
#include <string>
using namespace std;

Mes::Mes(string nome, int id, int numero_dias){
	this->nome = nome;
	this->id = id;
	this->numero_dias = numero_dias;
	this->vetor_dias = NULL;
	this->seg = NULL;
}