#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "Tabuleiro.h"


int main(int argc, const char *argv[] )
{
    Tabuleiro * T = malloc(sizeof(Tabuleiro));
    int tamanho_do_cn = atoi(argv[1]);
    if(tamanho_do_cn%2 == 0)
    {
        printf("Não pode ser par\n");
        return 0;
    }
    //colocar o filtro pro tamanho do CN (ñ pode ser par)
    SetTamanho(T, tamanho_do_cn);
    char elemento= ' ';
    int i, j, aux;
    char caracteres[6]={'@','%','?','*','#'};
    //não tem arquivo
    srand(time(NULL));
    if(argc == 2){
        for(i=0; i<T->tamanho; i++)
        {
            for(j=0; j<T->tamanho; j++)
            {
                aux= rand()%5;
                elemento=caracteres[aux];
                SetElemento(T, i, j, elemento);
            }
        }

    Imprime(*T);
    }
    //tem arquivo
    else if(argc == 3){

        FILE * arq = fopen(argv[2], "r");
        if(arq==NULL)
        {
            printf("Erro ao ler entrada\n");
            system ("pause");
            return 1;
        }else{

            printf("tamanho: %d\n", T->tamanho);
            for(i=0; i<T->tamanho; i++)
            {
                for(j=0; j<T->tamanho; j++)
                {
                    fscanf(arq, "%c ", &elemento);
                    SetElemento(T, i, j, elemento);
                }
            }
        fclose(arq);
        } 
        Imprime(*T);
    }
    int metadedaslinhas=T->tamanho/2;
    int condicao1=10;
    int condicao2=10;
    int condicao3=10;

    elemento=GetElemento(T, 0, 0);
    condicao1=TestaDiagonalED(T,elemento);
    printf("condicao1: %d\n", condicao1);
    elemento=GetElemento(T, 0, T->tamanho-1);
    condicao2=TestaDiagonalDE(T, elemento);
    printf("condicao2: %d\n", condicao2);
    condicao3=TestaDiferente(T, metadedaslinhas);
    printf("condicao3: %d\n", condicao3);


    if(condicao1==1 || condicao2==1 || condicao3==1){
        printf("Bingo!!!\n");
    }else{
        printf("Tente outra vez...\n");
    }
    free(T);
}












//     SRAND(time(NULL));
//     char elemento= ' ';
//     char caracteres[6]={'@','%','?','*','#'};
//     int tamanho=0;
//     int i=0;
//     int j=0;
//     int aux=0;
//     int opcao=0;
//     FILE *arq;
//     //printf("Tamanho: ");
//     //scanf("%d", &tamanho);
//     Tabuleiro *T=(Tabuleiro*)malloc(sizeof(Tabuleiro));
//     //SetTamanho(T, tamanho);


//     /*Se apenas o tamanho do tabuleiro for passado como parâmetro, o preenchimento deve ser  aleatório. Se forem passados o tamanho e o nome do
//     arquivo, os dados devem ser lidos do arquivo.*/

//     printf("Arquivo?\n1)sim\n2)Nao\n");

//     scanf("%d", &opcao);

//     switch(opcao)
//     {
//         case 1:
//         arq = fopen(argv[2], "r");

//         if(arq==NULL)
//         {
//         printf("Erro ao ler entrada\n");
//         system ("pause");
//         return 1;
//         }else

//     for(i=0; i<T->tamanho; i++)
//     {
//         for(j=0; j<T->tamanho; )
//         {
//             fscanf(arq, "%c", &elemento);
//             SetElemento(T, i, j, elemento);
//             j++;
//         }
//         fscanf(arq, "%c", &elemento);
//     }
//     break;

//         case 2:
//         printf("Tamanho: ");
//         scanf("%d", &tamanho);
//         SetTamanho(T, tamanho);
//         for(i=0; i<T->tamanho; i++)
//         {
//             for(j=0; j<T->tamanho; j++)
//             {
//                 aux= rand()%5;
//                 elemento=caracteres[aux];
//                 SetElemento(T, i, j, elemento);
//             }
//         }

//     break;
//     }

//     //O tabuleiro deve ser impresso nos dois casos antes  da  mensagem.
//     Imprime(*T);
//     /*Caso uma das duas diagonais tenha todos os elementos iguais, ou caso todos os elementos da linha central
//     sejam diferentes uns dos outros, seu programa deve imprimir Bingo!!!. Senão deve imprimir Tente outra vez...*/

//     int metadedaslinhas=tamanho/2;
//     int condicao1=10;
//     int condicao2=10;
//     int condicao3=10;


//     elemento=GetElemento(T, 0, 0);
//     condicao1=TestaDiagonalED(T,elemento);
//     elemento=GetElemento(T, tamanho-1, tamanho-1);
//     condicao2=TestaDiagonalDE(T, elemento);
//     condicao3=TestaDiferente(T, metadedaslinhas);


//     if(condicao1==1 || condicao2==1 || condicao3==1){
//         printf("Bingo!!!");
//     }else{
//         printf("Tente outra vez...");
//     }
//     free(T);
//     fclose(arq);
//     return 0;
// }