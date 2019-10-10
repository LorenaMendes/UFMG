#ifndef TABLEAUX_H
#define TABLEAUX_H

#include <iostream>

struct Tableaux{
	int lines, rests;
	int columns, vars;
	float matrix[20][20];
	float obj_func[20];
	int type;
	int aux;

	Tableaux(int, int);
};


bool CreateAuxiliar(Tableaux);
Tableaux Simplex(Tableaux);
int HasNegative(Tableaux, float*);
bool IsBaseColumn(Tableaux, int);
bool ColNegativa(Tableaux);
void PrintTableaux(Tableaux);
float Otima(Tableaux);
void PrintOtima(Tableaux Tab);
void Ilimitada(Tableaux, int, int);
double truncate(double);

#endif