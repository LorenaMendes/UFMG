#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

void iguala_aux(double **pl_aux, double **mat_rest, double *b, int var, int rest){
	for(int i = 0; i < rest; i++){
		for(int j = 0; j < var+rest; j++){
			mat_rest[i][j] = pl_aux[i+1][j];
		}
	}
	for(int i = 0; i < rest; i++){
		b[i] = pl_aux[i+1][var+rest+rest];
	}
}

void acha_certificado_ilimitada(double **tab, int var, int rest, double *d, int *base, int coluna/*negativa*/){
	for(int j = 0; j < var; j++){
		if(j == coluna){
			d[j] = 1;
		}
		else{
			int i;
			for(i = 0; i < rest; i++){
				if(base[i] == j){
					d[j] = (-1)*tab[i+1][coluna];
					break;
				}
			}
			if(i == rest){
				d[j] = 0;
			}
		}
	}
}


void acha_solucao(double *solucao, double **tab, int*base, int var, int rest){
	for(int i = 0; i < var; i++){	
		for(int j = 0; j < rest; j++){
			if(i == base[j]){
				solucao[i] = tab[j+1][var+rest];
				break;
			}
		}
		if(i == var){
			solucao[i] = 0;
		}
	}
}

void pivoteia(double elemento, int linha, int indice, int *base, double **tab, int var, int rest, int registro){//por enqt feita so pra normal
	double *aux = new double[var+rest+registro+1];
	for(int j = 0; j < var+rest+registro+1; j++){
		aux[j] = tab[indice][j];
	}
	for(int j = 0; j < var+rest+registro+1; j++){
		aux[j] = (-1)*elemento*tab[indice][j];
		
	}
	for(int j = 0; j < var+rest+registro+1; j++){
		tab[linha][j] += aux[j];	
	}
	delete[] aux;
}

bool simplex(int coluna, double **tab, int rest, int rest_aux, int var, int *base, int registro){
	double menor = 1000000000;
	int linha_menor = 100000000;
	for(int i = 1; i < rest+1; i++){//achei o elemento q minimiza a divisao
		if(tab[i][var+rest+rest_aux] >= 0 && tab[i][coluna] > 0){
			if(tab[i][var+rest+rest_aux]/tab[i][coluna] < menor){
				menor = tab[i][var+rest+rest_aux]/tab[i][coluna];
				linha_menor = i;
			}
		}
	}

	if(menor == 1000000000){
		return true;
	}
	else{//escolheu o elemento pra pivotear(linha menor da coluna coluna)
		base[linha_menor-1] = coluna;
		double elemento = tab[linha_menor][coluna];//tem q ser menos 1, pq o linha_menor representa no tableuax, e a base smp corresp um indice a menos (começa no 0)
		for(int j = 0; j < var+rest+rest_aux+registro+1; j++){
			tab[linha_menor][j] = tab[linha_menor][j]/elemento;
		}//transformou o menor elemento em 
		for(int i = 0; i < rest+1; i++){
			if(tab[i][coluna] != 0 && i != linha_menor){
				
				pivoteia(tab[i][coluna], i, linha_menor, base, tab, var, rest+rest_aux, registro);//pivoteou tudo lalalala
			}//ai vc tem uma nova base e uma nova solucao otima
		}
		return false;
	}
}

int inicia_simplex(double **tab, int var, int rest, int rest_aux, int registro, int *base){//por enqt feita so pra normal
	for(int i = 0; i < rest; i++){//verifica se a linha de cima esta zerada
		if(base[i] < var+rest+rest_aux


			+registro){
			if(tab[0][base[i]] != 0){
				pivoteia(tab[0][base[i]], 0, i+1, base, tab, var, rest+rest_aux, registro);
			}
		}
	}
	bool ilimitada = false;
	bool acabou = false;
	while(!acabou){
		int j;
		for(j = 0; j < var+rest+rest_aux; j++){
			if(tab[0][j] < 0){
				ilimitada = simplex(j, tab, rest, rest_aux, var, base, registro);
				break;
			}
		}
		if(j == var+rest+rest_aux){
			return -1; 
		}
		else if(ilimitada){
			return j;
		}
	}
}

void monta_tableaux(double *custo, double *b, double **mat_rest, int rest, int var, double **tableaux){//apenas pro original
	for(int j = 0; j < var; j++){
		tableaux[0][j] = (-1)*custo[j];
	}
	//colocou o começo correspondente ao inverso do custo
	for(int j = var; j < var+rest+1; j++){
		tableaux[0][j] = 0;
	}
	//colocou todos os zeros restantes
	//completou a 1 linha
	for(int i = 1; i < rest+1; i++){
		for(int j = 0; j < var+rest; j++){
			tableaux[i][j] = mat_rest[i-1][j];
		}
	}
	//preenchida a matriz de restricoes incluindo as var de folga
	for(int i = 1; i < rest+1; i++){
		tableaux[i][var+rest] = b[i-1];
	}
	//coloquei o b e finalizei a montagem do tableaux 	
}

void acha_base(int *base, int var, int rest, double **tab){
	for(int i = 1; i < rest+1; i++){
		for(int j = 0; j < var+rest; j++){
			if(tab[i][j] == 1){
				bool eh_base = true;
				for(int k = 1; k < rest+1; k++){
					if(tab[k][j] != 0 && k != i) {
						eh_base = false;
						break;
					}
				}
				if(eh_base == true){
					base[i-1] = j; 
					break;
				}
			}
		}
	}
}


void monta_PL_aux(double **aux, int var, int rest, double** mat_rest, double *b){
	for(int j = 0; j < var+rest; j++){
		aux[0][j] = 0;
	}
	for(int j = var+rest; j < var+rest+rest; j++){
		aux[0][j] = 1;
	}
	for(int j = var+rest+rest; j < var+rest+rest+rest+1; j++){
		aux[0][j] = 0;
	}
	//montei a primeira linha
	for(int i = 1; i < rest+1; i++){
		if(b[i-1] < 0){
			for(int j = 0; j < var+rest; j++){
				aux[i][j] = (-1)*mat_rest[i-1][j];
			}
			aux[i][var+rest+rest] = (-1)*b[i-1];
		}
		else{
			for(int j = 0; j < var+rest; j++){
				aux[i][j] = mat_rest[i-1][j];
			}
			aux[i][var+rest+rest] = b[i-1];
		}
	}
	//montei a parte corresp a matriz A original
	for(int i = 1; i < rest+1; i++){
		for(int j = var+rest; j < var+rest+rest; j++){
			if(i-1 == j-(var+rest)){
				aux[i][j] = 1;
			}
			else aux[i][j] = 0;
		}
	}
	//montei a parte corresp a ID nova 
	for(int i = 1; i < rest+1; i++){
		for(int j = var+rest+rest+1; j < var+rest+rest+rest+1; j++){
			if(i-1 == j-(var+rest+rest+1)){
				aux[i][j] = 1;
			}
			else aux[i][j] = 0;
		}
	}//parte correspondente a ID q registra 
}

int main(){
	int var, rest;
	cin>>rest>>var;
	cout<<fixed<<setprecision(2);
	double **mat_rest = new double*[rest];
	for(int i = 0; i < rest; i++){
		mat_rest[i] = new double[rest+var];
	}
	//leitura do vetor de custos
	double *custo = new double[var+rest];
	for(int i = 0; i < var; i++){
		cin>>custo[i];
	}
	double *b = new double[rest];
	bool precisa_aux = false;
	//leitura da matriz de rest e do vetor b
	for(int i = 0; i < rest; i++){
		for(int j = 0; j < var + 1; j++){
			if(j == var){
				cin>>b[i];
				if(b[i] < 0){
					precisa_aux = true;
				}
			} 
			else cin>>mat_rest[i][j];
		}
	}

	//adicionando as variaveis de folga ao vetor C e a matriz de restricoes
	for(int i = var; i < var+rest; i++){
		custo[i] = 0;
	}
	for(int i = 0; i < rest; i++){
		for(int j = var; j < var+rest; j++){
			if(i == j-var){
				mat_rest[i][j] = 1;
			}
			else mat_rest[i][j] = 0;
		}
	}

	int *base = new int[rest];
	bool eh_inviavel = false;
	if(precisa_aux){
		//criando a PL aux (ver se é viavel e ja achar uma sç basica)
		double **pl_aux = new double*[rest+1];
		for(int i = 0; i < rest+1; i++){
			pl_aux[i] = new double[var+rest+rest+rest+1]; 
		}
		monta_PL_aux(pl_aux, var, rest, mat_rest, b);
		for(int i = 0; i < rest; i++){
			base[i] = var+rest+i;
		}
		inicia_simplex(pl_aux, var, rest, rest, rest, base);
		if(pl_aux[0][var+rest+rest] < 0){
			eh_inviavel = true;
			cout<<"inviavel"<<endl;
			for(int j = var+rest+rest+1; j < var+rest+rest+rest+1; j++){
				if(b[j-(var+rest+rest+1)] < 0){
					cout<<(-1)*pl_aux[0][j]<<" ";
				}
				else cout<<pl_aux[0][j]<<" ";
			}
			cout<<endl;//caso da inviavel
		}
		else{
			iguala_aux(pl_aux, mat_rest, b, var, rest);//agora uma nova A e um novo B
		}
		for(int i = 0; i < rest+1; i++){
			delete[] pl_aux[i];
		}
		delete[] pl_aux;
	}
	if(!eh_inviavel){
		double **tableaux = new double*[rest+1];
		for(int i = 0; i < rest+1; i++){
			tableaux[i] = new double[var+rest+1];
		}
		monta_tableaux(custo, b, mat_rest, rest, var, tableaux);
		if(!precisa_aux){
			acha_base(base, var, rest, tableaux);
		}
		int resultado = inicia_simplex(tableaux, var, rest, 0, 0, base);
		double *solucao = new double[var];
		if(resultado == -1){
			cout<<"otima"<<endl;
			cout<<tableaux[0][var+rest]<<endl;
			acha_solucao(solucao, tableaux, base, var, rest);
			for(int i = 0; i < var; i++){
				cout<<solucao[i]<<" ";
			}
			cout<<endl;
			for(int j = var; j < var+rest; j++){
				cout<<tableaux[0][j]<<" ";
			}
			cout<<endl;//certificado de otimo
		}
		else{
			cout<<"ilimitada"<<endl;
			acha_solucao(solucao, tableaux, base, var, rest);
			for(int i = 0; i < var; i++){
				cout<<solucao[i]<<" ";
			}
			cout<<endl;
			double *d = new double[var];
			acha_certificado_ilimitada(tableaux, var, rest, d, base, resultado);
			for(int i = 0; i < var; i++){
				cout<<d[i]<<" ";
			}
			cout<<endl;
			delete[] d;
		}
		for(int i = 0; i < rest+1; i++){
			delete[] tableaux[i];
		}
		delete[] tableaux;
		delete[] solucao;
	}

	delete[] b;
	delete[] custo;
	for(int i = 0; i < rest; i++){
		delete[] mat_rest[i];
	}
	delete[] mat_rest;
	delete[] base;
	return 0;
}