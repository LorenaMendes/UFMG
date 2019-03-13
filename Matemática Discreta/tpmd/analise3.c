#include <stdio.h>

void imprimeCombinacao(int numerosInteiros[], int tamanho) {
    for(int i=0; i<tamanho; i++) {
        printf("%d ", numerosInteiros[i]);
    }
    printf("\n");
}

void verificaCombinacao(int numerosInteiros[], int r){
	// printf("\tVerificando "); imprimeCombinacao(numerosInteiros,r);
	int i,j,imprime;
	for(i=r-1;i>1;i--){
		for(j=i-1;j>0;j--){
			//compara os valores das posições do array para saber se a cada posição os numeros são >=.
			if(
				(numerosInteiros[i]<numerosInteiros[j])||
				(numerosInteiros[i-1]<numerosInteiros[j-1])
			){
				//encontrados valores iguais, cancela a impressão e retorna.
				return;
			}
		}
	}
	//não havendo iguais, imprime a sequência.
	imprimeCombinacao(numerosInteiros,r);
}

void hr() {
    printf("--------------------------------------------------\n");
}

void combinacaoComRepeticao(int r, int n) {
    hr();
    int numerosInteiros[r];
    for(int i=0; i<r; i++ ) {
        numerosInteiros[i] = 1;
    }
    int indice = r-1;
    verificaCombinacao(numerosInteiros,r);
    do {
        while(numerosInteiros[indice] < n) {
            numerosInteiros[indice]++;
            indice = r-1;
            verificaCombinacao(numerosInteiros,r);
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

    printf("Combinacao com repeticao utilizando r = %d e n = %d.\n",r,n);
    combinacaoComRepeticao(r,n);
    return 0;
}
