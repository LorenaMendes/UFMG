#ifndef INDICE_H
#define INDICE_H

#include <string>
#include <map>

struct Indice {
	std::map<std::string, int> mapa;
	int size;

	void insert(std::string word);
	void printMap();
};

#endif