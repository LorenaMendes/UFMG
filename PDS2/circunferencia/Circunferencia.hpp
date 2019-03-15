#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef CIRCUNFERENCIA_H
#define CIRCUNFERENCIA_H
#include <cmath>

struct Circunferencia {
	double xc, yc, raio;
	Circunferencia(double xc, double yc, double raio);
	double calcularArea();
	bool possuiIntersecao(Circunferencia * c);
};

#endif