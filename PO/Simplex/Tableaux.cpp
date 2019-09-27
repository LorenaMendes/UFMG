#include "Tableaux.hpp"
#include <utility>
#define DEBUG 0
#define def 1000
using namespace std;

Tableaux::Tableaux(int rests, int vars) {
	
	this->rests = rests;
	this->vars = vars;
	this->lines = rests + 1;
	this->columns = rests * 2 +1;

	if (DEBUG) cout << "linhas: " << lines << endl;
	if (DEBUG) cout << "colunas: " << columns << endl;

	for (int i = 0; i < this->lines; ++i)
		for (int j = 0; j < this->columns; ++j)
			this->matrix[i][j] = 0;

	// coloca as variáveis de folga
	for (int i = 1; i < this->lines; ++i) {
		for (int j = (this->columns - 1) / 2; j < this->columns - 1; ++j)
			if (j - i == (this->columns - 1) / 2 - 1)
				this->matrix[i][j] = 1;
	}
}

void Tableaux::Simplex() {

	while (1) {

		// representa a coluna pivô
		int col_pivo = -1;

		float pivo = def;

		// par reprensentando <linha pivô, razão>
		pair<int, float> pivot(def, def);

		// while((col_pivo = HasNegative(this->matrix[0])) != -1){
		if ((col_pivo = HasNegative(this->matrix[0])) != -1) {

			if (DEBUG) cout << "Coluna pivô: " << col_pivo << endl;

			// encontra o pivô
			for (int i = 1; i < this->lines; ++i) {
				if (this->matrix[i][col_pivo] != 0) {
					float a = this->matrix[i][this->columns - 1];
					float b = this->matrix[i][col_pivo];
					if (a / b >= 0 && a / b < pivot.second) {
						pivot.first = i;
						pivot.second = a / b;
						pivo = this->matrix[pivot.first][col_pivo];
					}
				}
			}

			if (pivo == def) {
				this->Ilimitada();
				break;
			}

			if (DEBUG) cout << "Linha pivô: " << pivot.first << endl;
			if (DEBUG) cout << "Pivô: " << pivo << endl;

			// divide a linha toda pelo pivô
			for (int i = 0; i < this->columns; ++i) {
				this->matrix[pivot.first][i] /= pivo;
			}

			// transforma todo o tableaux a partir da nova linha-pivô
			for (int i = 0; i < this->lines; ++i) {
				if (i != pivot.first) {

					float val = -this->matrix[i][col_pivo];
					for (int j = 0; j < this->columns; ++j)
						this->matrix[i][j] += (val * this->matrix[pivot.first][j]);
				}
			}

		} else {
			// if(!this->ColNegativa())
			this->Otima();
			break;
		}
	}
}

int Tableaux::HasNegative(float* vec) {
	for (int i = 0; i < this->columns; ++i)
		if (vec[i] < 0) return i;
	return -1;
}

bool Tableaux::IsBaseColumn(int col){
	bool flag = true;
	int count = 0;
	for (int i = 0; i < this->lines; ++i){
		float val = this->matrix[i][col];
		if(val == 1) count++;
		else if(val != 0) return false;
	}
	return count != 1 ? false : true;
}

void Tableaux::Ilimitada() {
	cout << "Ilimitada" << endl;

	// //achando o certificado
	// float max = 0;
	// float cert[vars];
	// int index = -1;
	// for (int i = 0; i < this->vars; ++i){}
	// 	// acho o maior elemento positivo
	// 	if(this->obj_func[i] > max){
	// 		index = i;
	// 		max = this->obj_func[i];
	// 	}
	
	// for (int i = 0; i < this->lines; ++i){
	// 	for (int j = 0; j < this->columns; ++j){
	// 		if(j != index){
				
	// 		}
	// 	}
	// }

	cout << endl;
}

void Tableaux::Otima() {
	cout << "otima" << endl;
	// imprimindo o valor ótimo
	cout << this->matrix[0][this->columns - 1] << endl;

	// imprimindo o vetor de valores que maximizam
	for (int j = 0; j < (this->vars); ++j) {
		if(!IsBaseColumn(j)) cout << "0 ";
		else{
			bool value = true;
			for (int i = 1; i < this->lines; ++i)
				if (this->matrix[i][j] == 1){
					cout << this->matrix[i][this->columns - 1] << " ";
					value = false;
				}
			if(value) cout << "0 ";
		}
	}
	cout << endl;

	//imprimindo o certificado de otimalidade
	for (int j = (this->columns - 1) / 2; j < this->columns - 1; ++j)
		cout << this->matrix[0][j] << " ";
	cout << endl;
	this->PrintTableaux();
}

void Tableaux::PrintTableaux() {
	cout << endl;
	for (int i = 0; i < this->lines; ++i) {
		for (int j = 0; j < this->columns; ++j) {
			cout << this->matrix[i][j] << " ";
		}
		cout << endl;
	}
}