#include "Tableaux.hpp"
#include <utility>
#define DEBUG 0
#define def 1000
using namespace std;

Tableaux::Tableaux(int rests, int vars) {
	
	this->rests = rests;
	this->vars = vars;
	this->lines = rests + 1;
	this->columns = rests * 2 + 1;
	this->type = -1;

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

// true para ótima, false para não ótima
bool CreateAuxiliar(Tableaux Tab){
	
	bool isOtima;

	int aux_col = Tab.columns;
	int aux_lin = Tab.lines;

	Tableaux Auxiliar(Tab.rests, Tab.vars);
	
	for (int i = 0; i < aux_lin; ++i){
		for (int j = 0; j < Tab.vars; ++j){
			if(i == 0) Auxiliar.matrix[i][j] = 0;
			else Auxiliar.matrix[i][j] = Tab.matrix[i][j];
		}
	}

	for (int i = 0; i < aux_lin; ++i){
		for (int j = Tab.vars; j < aux_col - 1; ++j){
			if(i == 0) Auxiliar.matrix[i][j] = 1;
			else if (j - i == (Tab.columns - 1) / 2 - 1) Auxiliar.matrix[i][j] = 1;
			else Auxiliar.matrix[i][j] = 0;
		}
	}

	for (int i = 0; i < aux_lin; ++i){
		if(i == 0) Auxiliar.matrix[i][aux_col-1] = 0;
		Auxiliar.matrix[i][aux_col-1] = Tab.matrix[i][Tab.columns-1];
	}

	for (int i = 0; i < aux_lin; ++i){
		if(Auxiliar.matrix[i][aux_col-1] < 0){
			Auxiliar.matrix[i][aux_col-1] *= -1;
			for (int j = 0; j < Tab.vars; ++j)
				Auxiliar.matrix[i][j] *= -1;
		}
	}

	// PrintTableaux(Auxiliar);

	Tableaux Temp = Simplex(Auxiliar);
	if(Temp.type == 0){
		if(Temp.aux == 0) isOtima = true;
		else isOtima = false;
 	}
	
	return isOtima;
}

Tableaux Simplex(Tableaux Tab) {

	/*
	0 = ótima
	1 = inviável
	2 = ilimitada
	*/
	Tab.type = 1;

	bool negative = false;
	for (int i = 1; i < Tab.lines; ++i)
		if(Tab.matrix[i][Tab.columns-1] < 0) negative = true;

	if(negative){
		if(!CreateAuxiliar(Tab)){
			Tab.type = 1;
			return Tab;
		}
	}

	while (1) {

		// representa a coluna pivô
		int col_pivo = -1;

		float pivo = def;

		// par reprensentando <linha pivô, razão>
		pair<int, float> pivot(def, def);

		if ((col_pivo = HasNegative(Tab, Tab.matrix[0])) != -1) {

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
				// É ilimitada
				Ilimitada(Tab, col_pivo, 0);
				Tab.aux = col_pivo;
				Tab.type = 2;
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
			Tab.type = 0;
			Tab.aux = Otima(Tab);
			break;
		}
	}
	return Tab;
}

int HasNegative(Tableaux Tab, float* vec) {
	for (int i = 0; i < Tab.columns; ++i)
		if (vec[i] < 0) return i;
	return -1;
}

bool IsBaseColumn(Tableaux Tab, int col){
	bool flag = true;
	int count = 0;
	for (int i = 0; i < Tab.lines; ++i){
		float val = Tab.matrix[i][col];
		if(val == 1) count++;
		else if(val != 0) return false;
	}
	return count != 1 ? false : true;
}

void Ilimitada(Tableaux Tab, int col_zoada, int flag) {
	if(flag) cout << "Ilimitada" << endl;

	// //achando o certificado
	float cert[Tab.vars];
	cert[col_zoada] = 1;
	int val;

	for (int j = 0; j < Tab.vars; ++j){
		if(j == col_zoada) continue;
		if(IsBaseColumn(Tab, j)){
			for (int i = 0; i < Tab.lines; ++i) if(Tab.matrix[i][j] == 1) val = i;
			cert[j] = 0 - Tab.matrix[val][col_zoada];
		} else cert[j] = 0;
	}
		
	if(flag) for (int i = 0; i < Tab.vars; ++i) cout << cert[i] << " ";

	if(flag) cout << endl;
}

void PrintOtima(Tableaux Tab) {
	float otimo;
	cout << "otima" << endl;
	// imprimindo o valor ótimo
	otimo = Tab.matrix[0][Tab.columns - 1];
	cout << otimo << endl;

	// imprimindo o vetor de valores que maximizam
	for (int j = 0; j < (Tab.vars); ++j) {
		if(!IsBaseColumn(Tab, j)) cout << "0 ";
		else{
			bool value = true;
			for (int i = 1; i < Tab.lines; ++i)
				if (Tab.matrix[i][j] == 1){
					cout << Tab.matrix[i][Tab.columns - 1] << " ";
					value = false;
				}
			if(value) cout << "0 ";
		}
	}
	cout << endl;

	//imprimindo o certificado de otimalidade
	for (int j = (Tab.columns - 1) / 2; j < Tab.columns - 1; ++j)
		cout << Tab.matrix[0][j] << " ";
	cout << endl;
}

float Otima(Tableaux Tab) {
	
	float otimo = Tab.matrix[0][Tab.columns - 1];
	return otimo;
}

void PrintTableaux(Tableaux Tab) {
	cout << endl;
	for (int i = 0; i < Tab.lines; ++i) {
		for (int j = 0; j < Tab.columns; ++j) {
			cout << Tab.matrix[i][j] << " ";
		}
		cout << endl;
	}
}

double truncate (double n) {
	if (n>=0 && n<=1e-04) return 0;
	else if (n>=(-1e-04) && n<=0) return 0;
	else return n;
}