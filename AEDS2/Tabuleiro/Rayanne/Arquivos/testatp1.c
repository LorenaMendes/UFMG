#include <stdio.h>
#include <stdlib.h>
#include "Tabuleiro.c"

int main()
{
int tamanho = 0;
char elemento = ' ';
int i=0;
int j=0;
int aux=0;

Tabuleiro*T=(Tabuleiro*)malloc(sizeof(Tabuleiro));
SetTamanho(T, tamanho);
/*if(nomearq!=' ')
{
FILE*entrada=fopen(nomearq, "r");
if(!entrada)
{
    printf("Erro na leitura do arquivo!\n");
    exit(EXIT_FAILURE);
}

for(i=0;i<T->tamanho; i++)
{
    for(j=0;j<T->tamanho;j++)
    {
        fscanf(entrada,"%c",&elemento);
        if(elemento!= ' ')
        {
            SetElemento(T, i, j, elemento);
            j++;
        }
    }
}
fclose(entrada);

}else{
*/
    char caracteres[6]={'@','%','?','*','#'};
    for(i=0; i<T->tamanho; i++)
    {
        for(j=0; j<T->tamanho; j++)
        {
            aux=rand()%5;
            elemento= caracteres[aux];
            SetElemento(T, i, j, elemento);
        }
    }
}

Imprime(T);

int metadedaslinhas=tamanho/2;
int condicao1=10,condicao2=10, condicao3=10;

elemento=GetElemento(T, 0, 0);
condicao1=TestaDiagonalED(T,elemento);
elemento=GetElemento(T, tamanho-1, tamanho-1);
condicao2=TestaDiagonalDE(T, elemento);
condicao3=TestaDiferente(T, metadedaslinhas);

if(condicao1==1 || condicao2==1 || condicao3==1){
    printf("Bingo!!!");
}else
{
    printf("Tente outra vez...");
}
free(T);

  return 0;
}
