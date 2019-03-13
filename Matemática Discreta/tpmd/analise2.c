#include <stdio.h>

void imprimePermutacao(int numerosInteiros[], int tamanho) {
    for(int i=0; i<tamanho; i++) {
        printf("%d ", numerosInteiros[i]);
    }
    printf("\n");
}

void verificaPermutacao(int numerosInteiros[], int r){
	// printf("\tVerificando "); imprimePermutacao(numerosInteiros,r);
	int i,j,imprime;
	for(i=0;i<r;i++){
		for(j=i+1;j<r;j++){
			//compara os valores das posições do array para saber se há iguais.
			if((numerosInteiros[i]==numerosInteiros[j]))
				//encontrados valores iguais, cancela a impressão e retorna.
				return;
		}
	}
	//não havendo iguais, imprime a sequência.
	imprimePermutacao(numerosInteiros,r);
}

void hr() {
    printf("--------------------------------------------------\n");
}

void permutacaoSemRepeticao(int r, int n) {
    hr();
    int numerosInteiros[r];
    for(int i=0; i<r; i++ ) {
        numerosInteiros[i] = 1;
    }
    int indice = r-1;
    verificaPermutacao(numerosInteiros,r);
    do {
        while(numerosInteiros[indice] < n) {
            numerosInteiros[indice]++;
            indice = r-1;
            verificaPermutacao(numerosInteiros,r);
       }
        numerosInteiros[indice] = 1;
        indice--;
    } while(indice >= 0);
    return;
}

int main() {
    int r, n;
    do {
	    hr();
	    printf("Digite o valor de r: ");
	    scanf("%d",&r);
	    printf("Digite o valor de n: ");
	    scanf("%d",&n);
	    fflush(stdin);
	    hr();
	    if((r<2) || (r>10) || (n<1) || (n>20) ) printf("Por favor, r deve estar entre 2 e 10, e n deve estar entre 1 e 20.\nDigite valores dentro dessas faixas.\nTente novamente.\n");
    } while( (r<2) || (r>10) || (n<1) || (n>20) ); // travar o usuario dentro do loop ate ele digitar valor certo para r e para n

    printf("Permutacao com repeticao utilizando r = %d e n = %d.\n",r,n);
    permutacaoSemRepeticao(r,n);
    return 0;
}
