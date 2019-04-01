#include <iostream>
#include <string>
#include <map>
#include "Indice.hpp"

int main(){

	Indice * dict = new Indice;
	std::string word;

	while (std::cin >> word){
		dict->size ++;
		for(int i=0; i<int(word.size()); i++) word[i] = tolower(word[i]);
		dict->insert(word);
	}

	dict->printMap();
	return 0;
}