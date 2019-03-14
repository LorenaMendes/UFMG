#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include "Estudante.hpp"

using namespace std;

float Estudante::calcularRSG() {
	float media = 0;
	for (int i = 0; i < 5; ++i) media += notas[i];
	media /= 5;
	cout << setiosflags (ios::fixed) << setprecision(2);
	return media;
}