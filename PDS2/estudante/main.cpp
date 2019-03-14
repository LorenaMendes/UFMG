#include <iostream>
#include <string.h>
#include <sstream>
#include "Estudante.hpp"

using namespace std;

void trocaElementos(Estudante *a, Estudante *b){ 
    Estudante temp = *a; 
    *a = *b; 
    *b = temp; 
} 
  
void bubbleSort(Estudante arr[], int n) { 
	for (int i = 0; i < n-1; i++){
		for (int j = 0; j < n-i-1; j++){ 
			if (arr[j].notas[0] < arr[j+1].notas[0]) 
	        	trocaElementos(&arr[j], &arr[j+1]);
	        else if(arr[j].notas[0] == arr[j+1].notas[0]){
	        	if (arr[j].matricula > arr[j+1].matricula){
	        		trocaElementos(&arr[j], &arr[j+1]);
	        	}
	        }
		}
	}
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
		
		// CALCULANDO O RSG E COLOCANDO O VALOR NO NOTAS[0]
		float rsg = estudantes[i].calcularRSG();
		estudantes[i].notas[0] = rsg;
		cout << "RSG: " << estudantes[i].notas[0];
		cout << endl;
	}

	// ORDENANDO O VETOR DE ESTUDANTES
	bubbleSort(estudantes, 10);
	
	// CALCULANDO O RSG
	cout << endl << "RSGs: ";
	for (int i = 0; i < 10; ++i) cout << estudantes[i].notas[0] << " ";
	cout << endl << endl;

	for (int i = 0; i < 3; ++i){
		cout << estudantes[i].matricula << " ";
		cout << estudantes[i].nome << " ";
		cout << estudantes[i].notas[0] << " ";
		cout << endl;
	}

	return 0;
}