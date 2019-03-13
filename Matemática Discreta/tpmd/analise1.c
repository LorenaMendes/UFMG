#include <stdio.h>

// imprime uma linha
void hr() {
    printf("--------------------------------------------------\n");
}

// Recebe um vetor de numeros inteiros e imprime todos eles. E depois coloca um \n.
void imprimePermutacao(int numerosInteiros[], int tamanho) {
    for(int i=0; i<tamanho; i++) {
        printf("%d ", numerosInteiros[i]);
    }
    printf("\n");
}

// Funcao principal para imprimir Permutacao com Repeticao
// utiliza logica similar aa logica de um relogio
void permutacaoComRepeticao(int r, int n) {
    hr();

    // Fazemos um vetor para guardar todos os numeros da permutacao atual. Ela contem r numeros.
    int numerosInteiros[r];

    // Agora, eh necessario inicializar todos estes numeros. Colocaremos o valor minimo em todos eles: o valor 1.
    for(int i=0; i<r; i++ ) {
        numerosInteiros[i] = 1;
    }

    // Vamos comecar permutando o numero mais a direita
    int indice = r-1;

    // Antes de comecar, imprimir o primeiro. Sempre vamos ter pelo menos uma impressao, pois n >= 1 e r >= 2.
    permutacao(numerosInteiros,r);

    // Faca o seguinte...
    do {
        // Enquanto couber mais na posicao que estamos trabalhando
        while(numerosInteiros[indice] < n) {

            // Incremente a posicao atual
            numerosInteiros[indice]++;

            // E volte para permutar a mais a direita
            indice = r-1;

            // Aproveite para imprimir como esta ficando...
            imprimePermutacao(numerosInteiros,r);
        }

        // Se nao coube mais...

        // Limpa o nivel atual
        numerosInteiros[indice] = 1;

        // E vamos para o nivel superior.
        indice--;

    // Enquanto nao tivermos enchido o ultimo indice
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
    permutacaoComRepeticao(r,n);
    return 0;
}
