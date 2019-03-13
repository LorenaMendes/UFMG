#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main(){
	string line;
	long matr;
	string nome;
	int notas[5];
	while(getline(cin, line)){
		stringstream ss;
		ss << line;
		ss >> matr >> nome;
		for (int i = 0; i < 5; ++i) ss >> notas[i];
		cout << "NOME: " << nome << endl;
		cout << "MATR: " << matr << endl;
		for (int j = 0; j < 5; ++j) cout << notas[j] << " ";
		cout << endl;
	}
	return 0;
}