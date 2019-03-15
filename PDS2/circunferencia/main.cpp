#include <iostream>
#include "Circunferencia.hpp"

using namespace std;

int main(){
	Circunferencia * circ1 = new Circunferencia(2, 0, 1);
	Circunferencia * circ2 = new Circunferencia(0, 2, 2);

	cout << circ1->calcularArea() << endl;
	cout << circ1->possuiIntersecao(circ2) << endl;
	delete circ1;
	delete circ2;
	return 0;
}