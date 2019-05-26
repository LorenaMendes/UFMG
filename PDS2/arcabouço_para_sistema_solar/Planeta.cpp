#include "Planeta.hpp"
#include "Astro.hpp"
#include <string>
#include <iostream>
#include <list>

int Planeta::getNumLuas() {
	return this->num_luas;
}

void Planeta::insereLua(Astro* lua) {
	this->luas.push_back(lua);
	this->num_luas ++;
}