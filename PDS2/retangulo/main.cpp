#include <iostream>
#include <cmath>
#include <iomanip>

float calculaPerimetro(float base, float altura){
	return base*2 + altura*2;
}

float calculaArea(float base, float altura){
	return base * altura;
}

float calculaDiagonal(float base, float altura){
	return sqrt(pow(base,2) + pow(altura,2));
}

int main(){
	
	float base, altura;
	std::cin >> base >> altura;

	float perimetro = calculaPerimetro(base, altura);
	float area = calculaArea(base, altura);
	float diagonal = calculaDiagonal(base, altura);

	std::cout << setiosflags (std::ios::fixed) << std::setprecision(6);
	std::cout << "Lado base = " << base << std::endl;
	std::cout << "Lado altura = " << altura << std::endl;
	std::cout << "Valores calculados" << std::endl;
	std::cout << "Perimetro = " << perimetro << std::endl;
	std::cout << "Area = " << area << std::endl;
	std::cout << "Diagonal = " << diagonal << std::endl;

	return 0;
}