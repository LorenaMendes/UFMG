#include "Controle.hpp"

Controle::Controle(Televisao *t){
	this->tv = t;
}

void Controle::setCanal(int c){
	this->tv->setCanal(c);
}

void Controle::setVolume(int v){
	this->tv->setVolume(v);
}

void Controle::aumentaVolume(){
	this->tv->setVolume(this->tv->getVolume() + 1);
}

void Controle::diminuiVolume(){
	this->tv->setVolume(this->tv->getVolume() - 1);	
}

void Controle::aumentaCanal(){
	this->tv->setCanal(this->tv->getCanal() + 1);
}

void Controle::diminuiCanal(){
	this->tv->setCanal(this->tv->getCanal() - 1);	
}