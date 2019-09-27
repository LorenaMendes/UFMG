#ifndef TABLEAUX_H
#define TABLEAUX_H

#include <iostream>

struct Tableaux{
	int lines, rests;
	int columns, vars;
	float matrix[10][10];
	float obj_func[10];

	Tableaux(int, int);
	void Simplex();
	int HasNegative(float*);
	bool IsBaseColumn(int);
	bool ColNegativa();
	void PrintTableaux();
	void Otima();
	void Ilimitada();
};

#endif