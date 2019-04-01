#include "Indice.hpp"
#include <iomanip>
#include <iostream>


void Indice::printMap(){	
	std::cout << std::setiosflags (std::ios::fixed) << std::setprecision(2);
	std::map<std::string, int>::iterator it;

	for (it = this->mapa.begin(); it != this->mapa.end(); it++)
	std::cout << it->first << " " << it->second << " " << (it->second/(float)this->size) << std::endl;
}

void Indice::insert(std::string word){
	if(word.size() >= 3){
		if(this->mapa[word]) this->mapa[word]++;
		else this->mapa[word] = 1;
	}
}