#include "Televisao.hpp"
#include <iostream>
// Televisao::Televisao() {}
using namespace std;

void Televisao::setCanal(int c) {
	cout << "c: " << c%100 << endl;
	if (c > 99) this->canal = c%100;
	else if (c < 0) this->canal = 100-((-c)%100);
	else this->canal = c;
}

void Televisao::setVolume(int v) {
	if (v > 20) this->volume = 20;
	else if (v < 0) this->volume = 0;
	else this->volume = v;
}

int Televisao::getCanal() {
	return this->canal;
}

int Televisao::getVolume() {
	return this->volume;
}
