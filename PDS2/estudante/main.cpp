#include <iostream>
#include <string.h>
#include <sstream>
#include "Estudante.hpp"

using namespace std;

int compara (const void * a, const void * b){
	Estudante *estudA = (Estudante *)a;
	Estudante *estudB = (Estudante *)b;
	// cout << "testando " << estudA->matricula << " e " << estudB->matricula << endl;
	return ( estudA->notas[0] - estudB->notas[0] );
}

int main(){

	string line;
	Estudante estudantes[10];

	for(int i=0; i<10; ++i){
		
		// PEGANDO UMA LINHA E TRATANDO OS ATRIBUTOS
		getline(cin, line);
		stringstream ss;
		ss << line;
		ss >> estudantes[i].matricula; 
		ss >> estudantes[i].nome;
		for (int j = 0; j < 5; ++j) ss >> estudantes[i].notas[j];
		
		// IMPRIMINDO PARA TESTAR
		cout << "NOME: " << estudantes[i].nome << endl;
		cout << "MATR: " << estudantes[i].matricula << endl;
		for (int j = 0; j < 5; ++j) cout << estudantes[i].notas[j] << " ";
		
		// CALCULANDO O RSG E COLOCANDO O VALOR NO NOTAS[0]
		float rsg = estudantes[i].calcularRSG();
		estudantes[i].notas[0] = rsg;
		cout << "RSG: " << estudantes[i].notas[0];
		cout << endl;
	}

	// ORDENANDO O VETOR DE ESTUDANTES
	// qsort (estudantes, 10, sizeof(struct Estudante), compara);
	// for (int i = 0; i < 10; ++i){
	// 	cout << estudantes[i].notas[0] << " ";
	// }
	return 0;
}