#include <iostream>
#include <string>
#include "Estudante.hpp"

using namespace std;

float Estudante::calcularRSG() {
	int media = 0;
	for (int i = 0; i < 5; ++i) media += notas[i];
	media /= 5;
	return media;
}