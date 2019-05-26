#ifndef PLANETA_H
#define PLANETA_H
#include "Astro.hpp"
#include <string>
#include <list>

class Planeta : public Astro {
private:
	list<Astro*> luas;
	int num_luas;

public:
	Planeta() {num_luas = 0;}
	int getNumLuas();
	void insereLua(Astro* lua);
};

#endif