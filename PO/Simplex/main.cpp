#include <iostream>
#include <string>
#include "Tableaux.cpp"
using namespace std;

int main(int argc, char const *argv[]){
	
	int n = 0; // restrições
	int m = 0; // variáveis
	cin >> n >> m;
	
	if(n <= 0 || m <= 0) return 0;

	Tableaux Tab(n, m);
	
	// leio a coluna dos ci's
	int val = 0;
	for (int i = 0; i < m; ++i){
		cin >> val;
		Tab.matrix[0][i] = -val;
		Tab.obj_func[i] = val;
	}

	// leio as restrições
	for (int i = 1; i <= n; ++i){
		for (int j = 0; j < m; ++j)
			cin >> Tab.matrix[i][j];
		cin >> Tab.matrix[i][n+n];
	}

	Tableaux Final = Simplex(Tab);
	// int * res = Simplex(Tab);
	// int type = res[0];
	// int aux = res[1];
	
	switch(Final.type){
		case 0:
			PrintOtima(Final);
			break;
		case 1:
			cout << "inviavel" << endl;
			break;
		case 2:
			Ilimitada(Final, Final.aux, 1);
	}

	return 0;
}