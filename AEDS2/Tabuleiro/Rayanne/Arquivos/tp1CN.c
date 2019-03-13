#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"Tabuleiro.c"

int main(int argc, char *argv[] )
{

char elemento= ' ';
char caracteres[6]={'@','%','?','*','#'};
int tamanho=0;
int i=0;
int j=0;
int aux=0;
int opcao=0;
FILE *arq;
//printf("Tamanho: ");
//scanf("%d", &tamanho);
Tabuleiro *T=(Tabuleiro*)malloc(sizeof(Tabuleiro));
//SetTamanho(T, tamanho);


/*Se apenas o tamanho do tabuleiro for passado como parâmetro, o preenchimento deve ser  aleatório. Se forem passados o tamanho e o nome do
arquivo, os dados devem ser lidos do arquivo.*/

printf("Arquivo?\n1)sim\n2)Nao\n");

scanf("%d", &opcao);

switch(opcao)
{
    case 1:
    FILE *arq = fopen("dados.txt", "r");

    if(arq==NULL)
    {
    printf("Erro ao ler entrada\n");
    system ("pause");
    return 1;
    }else

for(i=0; i<T->tamanho; i++)
{
    for(j=0; j<T->tamanho; )
    {
        fscanf(arq, "%c", &elemento);
        SetElemento(T, i, j, elemento);
        j++;
    }
    fscanf(arq, "%c", &elemento);
}
break;

    case 2:
    printf("Tamanho: ");
    scanf("%d", &tamanho);
    SetTamanho(T, tamanho);
    for(i=0; i<T->tamanho; i++)
    {
        for(j=0; j<T->tamanho; j++)
        {
            aux= rand()%5;
            elemento=caracteres[aux];
            SetElemento(T, i, j, elemento);
        }
    }

break;
}

//O tabuleiro deve ser impresso nos dois casos antes  da  mensagem.
Imprime(T);
/*Caso uma das duas diagonais tenha todos os elementos iguais, ou caso todos os elementos da linha central
sejam diferentes uns dos outros, seu programa deve imprimir “Bingo!!!”. Senão deve imprimir “Tente outra vez...”*/

int metadedaslinhas=tamanho/2;
int condicao1=10;
int condicao2=10;
int condicao3=10;


elemento=GetElemento(T, 0, 0);
condicao1=TestaDiagonalED(T,elemento);
elemento=GetElemento(T, tamanho-1, tamanho-1);
condicao2=TestaDiagonalDE(T, elemento);
condicao3=TestaDiferente(T, metadedaslinhas);


if(condicao1==1 || condicao2==1 || condicao3==1){
    printf("Bingo!!!");
}else{
    printf("Tente outra vez...");
}
free(T);
fclose(arq);
return 0;
}
