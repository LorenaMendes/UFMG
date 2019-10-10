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

void Tableaux::CreateAuxiliar(){
	int aux_col = this->columns;
	int aux_lin = this->lines;

	float Auxiliar[aux_lin][aux_col];
	
	for (int i = 0; i < aux_lin; ++i){
		for (int j = 0; j < this->vars; ++j){
			if(i == 0) Auxiliar[i][j] = 0;
			else Auxiliar[i][j] = this->matrix[i][j];
		}
	}

	for (int i = 0; i < aux_lin; ++i){
		for (int j = this->vars; j < aux_col - 1; ++j){
			if(i == 0) Auxiliar[i][j] = 1;
			else if (j - i == (this->columns - 1) / 2 - 1) Auxiliar[i][j] = 1;
			else Auxiliar[i][j] = 0;
		}
	}

	for (int i = 0; i < aux_lin; ++i){
		if(i == 0) Auxiliar[i][aux_col-1] = 0;
		Auxiliar[i][aux_col-1] = this->matrix[i][this->columns-1];
	}

	for (int i = 0; i < aux_lin; ++i){
		if(Auxiliar[i][aux_col-1] < 0){
			Auxiliar[i][aux_col-1] *= -1;
			for (int j = 0; j < this->vars; ++j)
				Auxiliar[i][j] *= -1;
		}
	}

	cout << endl;
	for (int i = 0; i < aux_lin; ++i) {
		for (int j = 0; j < aux_col; ++j) {
			cout << Auxiliar[i][j] << " ";
		}
		cout << endl;
	}

	// return Auxiliar;
}

void Tableaux::Simplex(Tableaux Tab) {

	// this->CreateAuxiliar();
	
	// if(!IsViable()){
	// 	cout << "Inviavel" << endl;
	// 	return;
	// }

	while (1) {

		// representa a coluna pivô
		int col_pivo = -1;

		float pivo = def;

		// par reprensentando <linha pivô, razão>
		pair<int, float> pivot(def, def);

		if ((col_pivo = HasNegative(Tab.matrix[0])) != -1) {

			if (DEBUG) cout << "Coluna pivô: " << col_pivo << endl;

			// encontra o pivô
			for (int i = 1; i < Tab.lines; ++i) {
				if (Tab.matrix[i][col_pivo] != 0) {
					float a = Tab.matrix[i][Tab.columns - 1];
					float b = Tab.matrix[i][col_pivo];
					if (a / b >= 0 && a / b < pivot.second) {
						pivot.first = i;
						pivot.second = a / b;
						pivo = Tab.matrix[pivot.first][col_pivo];
					}
				}
			}

			if (pivo == def) {
				Tab.Ilimitada(col_pivo);
				break;
			}

			if (DEBUG) cout << "Linha pivô: " << pivot.first << endl;
			if (DEBUG) cout << "Pivô: " << pivo << endl;

			// divide a linha toda pelo pivô
			for (int i = 0; i < Tab.columns; ++i) {
				Tab.matrix[pivot.first][i] /= pivo;
			}

			// transforma todo o tableaux a partir da nova linha-pivô
			for (int i = 0; i < Tab.lines; ++i) {
				if (i != pivot.first) {

					float val = -Tab.matrix[i][col_pivo];
					for (int j = 0; j < Tab.columns; ++j)
						Tab.matrix[i][j] += (val * Tab.matrix[pivot.first][j]);
				}
			}

		} else {
			// if(!Tab.ColNegativa())
			Tab.Otima();
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

// bool Tableaux::IsViable(){
// 	bool flag = true;
	
// 	return flag;
// }

void Tableaux::Ilimitada(int col_zoada) {
	cout << "Ilimitada" << endl;

	// //achando o certificado
	float cert[vars];
	cert[col_zoada] = 1;
	int val;

	for (int j = 0; j < this->vars; ++j){
		if(j == col_zoada) continue;
		if(IsBaseColumn(j)){
			for (int i = 0; i < this->lines; ++i) if(this->matrix[i][j] == 1) val = i;
			cert[j] = 0 - this->matrix[val][col_zoada];
		} else cert[j] = 0;
	}
		
	for (int i = 0; i < this->vars; ++i) cout << cert[i] << " ";

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

double Tableaux::truncate (double n) {
	if (n>=0 && n<=1e-04) return 0;
	else if (n>=(-1e-04) && n<=0) return 0;
	else return n;
}