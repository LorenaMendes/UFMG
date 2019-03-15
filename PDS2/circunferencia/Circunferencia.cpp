#include "Circunferencia.hpp"
#include <iostream>

using namespace std;

Circunferencia::Circunferencia(double _x, double _y, double _raio) {
	xc = _x;
	yc = _y;
	raio = _raio;
}

double Circunferencia::calcularArea() {
	return M_PI * pow(raio, 2);
}

bool Circunferencia::possuiIntersecao(Circunferencia * c) {
	double dist_centro = sqrt(pow((c->xc - xc),2) + pow((c->yc - yc),2));
	if (dist_centro > c->raio + raio) return 0;
	else return 1;
}