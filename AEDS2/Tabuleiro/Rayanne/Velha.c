#include <stdio.h>
#include <stdlib.h>
#include "Tabuleiro.h"


int TestaGanhador(Tabuleiro *T, char jogador){
    int casos = 10;   
    int linha=0;
    int coluna=0;
    for(linha=0;linha<3;linha++)
    {
        casos=TestaLinha(T,linha,jogador);
        if(casos==1)
        {
            printf("\n O vencedor foi %c!\n", jogador);
            return 1;
        }
        for(coluna=0;coluna<3;coluna++)
        {
            casos=TestaColuna(T,linha,jogador);
            if(casos==1)
            {
                printf("\n O vencedor foi %c!\n", jogador);
                return 1;
            }
        }
    }
    casos=TestaDiagonalDE(T, jogador);
    if(casos==1)
    {
        printf("\n O vencedor foi %c!\n", jogador);
        return 1;
    }
    casos=TestaDiagonalED(T, jogador);
    if(casos==1)
    {
        printf("\n O vencedor foi %c!\n", jogador);
        return 1;
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    int i=0;
    int j=0;
    int aux=0;
    int casos = 10;
    int linha=0;
    int coluna=0;
    int condicao=0;
    int condicao2=0;
    char elemento =' ';
    char jogador;
    Tabuleiro*T=(Tabuleiro*)malloc(sizeof(Tabuleiro));
    SetTamanho(T, 3);
    MarcaTodos(T,'_');

    //com arquivo
    if(argc == 3){
        FILE * arq = fopen(argv[2], "r");
        aux = 0;
        for(i=0;!feof(arq);i++)
        {

            if(aux%2 == 0) jogador = 'X';
            else jogador = 'O';
            fscanf(arq, "%d %d", &linha, &coluna);
            SetElemento(T, linha, coluna, jogador);
            aux++;

        }
        Imprime(*T);
        condicao += TestaGanhador(T, 'X');
        condicao += TestaGanhador(T, 'O');
        if(!condicao){
            printf("Deu velha\n");
            return 0;
        }
        fclose(arq);        
    }
    //sem arquivo
    else if(argc == 2){
        int tipo = atoi(argv[1]);
        if(tipo == 1){
            for(i=0; i<=9;i++){
                int vez_do_jogador = (i%2);
                if(vez_do_jogador == 0) jogador = 'X';
                else jogador = 'O';
                if(TestaGanhador(T, 'X') || TestaGanhador(T, 'O')) return 0;
                if(i==9){
                    printf("Deu velha\n");
                    exit(0);
                }
                if(jogador == 'X'){
                    while(condicao==0)
                    {    
                        printf("Usuário (X), por favor digite a linha e a coluna\n");
                        scanf("%d%d", &linha, &coluna);

                        //se estiver ocupada, preenche outra
                        if(T->matriz[linha][coluna]!= '_')
                        {
                            printf("Escolha outra posicao, esta ja esta preenchida\n");
                        }else//se não for diferente vai preecher
                        {
                             SetElemento(T,linha,coluna,'X');
                             condicao=1;
                        }
                    }
                    condicao=0;
                }
                else{
                    printf("jogador O\n");
                    while(condicao2==0)
                    {
                        int aleatorio = rand() % 9;
                        switch(aleatorio){
                            case 0: linha=0, coluna=0; break;
                            case 1: linha=0, coluna=1; break;
                            case 2: linha=0, coluna=2; break;
                            case 3: linha=1, coluna=0; break;
                            case 4: linha=1, coluna=1; break;
                            case 5: linha=1, coluna=2; break;
                            case 6: linha=2, coluna=0; break;
                            case 7: linha=2, coluna=1; break;
                            case 8: linha=2, coluna=2; break;
                        }
                        elemento = GetElemento(T, linha, coluna);
                        if(elemento=='_'){
                            SetElemento(T, linha, coluna, jogador);
                            condicao2=1;
                        }
                    }
                    condicao2 = 0;
        
                }
                //Testar se todo o tabuleiro foi preenchido
                for(linha=0;linha<3;linha++)
                {
                    for(coluna=0;coluna<3;coluna++)
                    {
                        if(T->matriz[linha][coluna]=='_')
                        {
                            casos=1;
                        }

                    }
                }
                Imprime(*T);
            }
        } else if(tipo == 2){
            for(i=0; i<=9;i++){
                int vez_do_jogador = (i%2);
                if(vez_do_jogador == 0) jogador = 'X';
                else jogador = 'O';
                if(TestaGanhador(T, 'X') || TestaGanhador(T, 'O')) return 0;
                if(i==9){
                    printf("Deu velha\n");
                    exit(0);
                }
                if(jogador == 'X'){
                    while(condicao==0)
                    {    
                        printf("Usuário (X), por favor digite a linha e a coluna\n");
                        scanf("%d%d", &linha, &coluna);

                        //se estiver ocupada, preenche outra
                        if(T->matriz[linha][coluna]!= '_')
                        {
                            printf("Escolha outra posicao, esta ja esta preenchida\n");
                        }else//se não for diferente vai preecher
                        {
                             SetElemento(T,linha,coluna,'X');
                             condicao=1;
                        }
                    }
                    condicao=0;
                }
                else{
                    while(condicao2==0)
                    {    
                        printf("Usuário (O), por favor digite a linha e a coluna\n");
                        scanf("%d%d", &linha, &coluna);

                        //se estiver ocupada, preenche outra
                        if(T->matriz[linha][coluna]!= '_')
                        {
                            printf("Escolha outra posicao, esta ja esta preenchida\n");
                        }else//se não for diferente vai preecher
                        {
                             SetElemento(T,linha,coluna,'O');
                             condicao2=1;
                        }
                    }
                    condicao2=0;
        
                }
                Imprime(*T);
            }
        }
    }
    return 0;
}









//             while(condicao2==0)
//             {
//             //ter certeza que o jogador não está preenchendo posição já ocupada
//            
//                 printf("Usuário (X), por favor digite a linha e a coluna\n");
//                 scanf("%d%d", &linha, &coluna);

//                 //se estiver ocupada, preenche outra
//                 if(T->matriz[linha][coluna]!= '_')
//                 {
//                     printf("Escolha outra posicao, esta ja esta preenchida\n");
//                 }else//se não for diferente vai preecher
//                 {
//                      SetElemento(T,linha,coluna,'X');
//                      condicao=1;
//                 }

//             }

//             condicao=0;//zerar a condição para analisar caso O
//             linha=0;
//             coluna=0;
//             Imprime(*T);

//             //testar se já acabou o jogo e se X é ganhador
//             for(linha=0;linha<3;linha++)
//             {
//             casos=TestaLinha(T,linha,'X');
//             if(casos==1)
//             {
//                 printf("\n O vencedor foi X!\n");
//                 exit(0);
//             }
//             for(coluna=0;coluna<3;coluna++)
//             {
//             casos=TestaColuna(T,linha,'X');
//             if(casos==1)
//             {
//                 printf("\n O vencedor foi X!\n");
//                 exit(0);
//             }
//             }
//             }
//             casos=TestaDiagonalDE(T,'X');
//             if(casos==1)
//             {
//                 printf("O vencedor foi X! \n");
//                 exit(0);
//             }
//                 casos=TestaDiagonalED(T,'X');
//             if(casos==1)
//             {
//                 printf("O vencedor foi X! \n");
//                 exit(0);
//             }
//             //Testar se todo o tabuleiro foi preenchido
//             for(linha=0;linha<3;linha++)
//             {
//                 for(coluna=0;coluna<3;coluna++)
//                 {
//                     if(T->matriz[linha][coluna]=='_')
//                     {
//                         casos=1;
//                     }

//                 }
//             }
//             if(casos!=0)
//             {
//                 condicao2=1;
//                 printf("\n Deu Velha!\n");
//                 exit(0);
//             }
//             //preecher aleatoriamente as posições O
//             while(condicao==0)
//             {
//                 linha=rand()%2;
//                 coluna=rand()%2;
//                 if(T->matriz[linha][coluna]=='_')
//                 {
//                     SetElemento(T,linha,coluna,'O');
//                     condicao=1;
//                 }
//             }
//             Imprime(*T);
//             //testa se jogador O é ganhador
//             for(linha=0;linha<3;linha++)
//             {
//             casos=TestaLinha(T,linha,'O');
//             if(casos==1)
//             {
//                 printf("\n O vencedor foi O!\n");
//                 exit(0);
//             }
//             for(coluna=0;coluna<3;coluna++)
//             {
//             casos=TestaColuna(T,linha,'O');
//             if(casos==1)
//             {
//                 printf("\n O vencedor foi O!\n");
//                 exit(0);
//             }
//             }
//             }
//             casos=TestaDiagonalDE(T,'O');
//             if(casos==1)
//             {
//                 printf("O vencedor foi O! \n");
//                 exit(0);
//             }
//             casos=TestaDiagonalED(T,'O');
//             if(casos==1)
//             {
//                 printf("O vencedor foi O! \n");
//                 exit(0);
//             }
//             casos=0;

//             //Testar se todo o tabuleiro foi preenchido
//             for(linha=0;linha<3;linha++)
//             {
//                 for(coluna=0;coluna<3;coluna++)
//                 {
//                     if(T->matriz[linha][coluna]=='_')
//                     {
//                         casos=1;
//                     }

//                 }
//             }
//             if(casos!=0)
//             {
//                 condicao2=1;
//                 printf("\n Deu Velha!\n");
//                 exit(0);
//             }

//             }

//         } else if(tipo == 2){

//         }
//     }
//     return 0;
// }















// void Velha(int opcao, char *nomearq)
// {

// int a=0;
// int b=0;
// int i=0;
// int j=0;
// int aux=0;
// int casos = 10;
// int linha=0;
// int coluna=0;
// int condicao=0;
// int condicao2=0;
// char elemento =' ';
// Tabuleiro*T=(Tabuleiro*)malloc(sizeof(Tabuleiro));
// SetTamanho(T, 3);
// MarcaTodos(T,'_');

// printf("Selecione a modalidade:\n 1-jogador versus computador.\n 2- 2 jogadores. \n 3- leia o jogo de um arquivo.\n");
// scanf("%d", &opcao);

// switch (opcao)
// {
//     //jogador versus computador
// case 1:
//     Imprime(*T); //tirar depois
//     //jogar até preecher toda a matriz
//     while(condicao2==0)
//     {
//     //ter certeza que o jogador não está preenchendo posição já ocupada
//     while(condicao==0)
//     {
//     printf("Usuário (X), por favor digite a linha e a coluna\n");
//     scanf("%d%d", &linha, &coluna);

//     //se estiver ocupada, preenche outra
//     if(T->matriz[linha][coluna]!= '_')
//     {
//         printf("Escolha outra posicao, esta ja esta preenchida\n");
//     }else//se não for diferente vai preecher
//     {
//          SetElemento(T,linha,coluna,'X');
//          condicao=1;
//     }

//     }

//     condicao=0;//zerar a condição para analisar caso O
//     linha=0;
//     coluna=0;
//     Imprime(*T);

//     //testar se já acabou o jogo e se X é ganhador
//     for(linha=0;linha<3;linha++)
//     {
//     casos=TestaLinha(T,linha,'X');
//     if(casos==1)
//     {
//         printf("\n O vencedor foi X!\n");
//         exit(0);
//     }
//     for(coluna=0;coluna<3;coluna++)
//     {
//     casos=TestaColuna(T,linha,'X');
//     if(casos==1)
//     {
//         printf("\n O vencedor foi X!\n");
//         exit(0);
//     }
//     }
//     }
//     casos=TestaDiagonalDE(T,'X');
//     if(casos==1)
//     {
//         printf("O vencedor foi X! \n");
//         exit(0);
//     }
//         casos=TestaDiagonalED(T,'X');
//     if(casos==1)
//     {
//         printf("O vencedor foi X! \n");
//         exit(0);
//     }
//     //Testar se todo o tabuleiro foi preenchido
//     for(linha=0;linha<3;linha++)
//     {
//         for(coluna=0;coluna<3;coluna++)
//         {
//             if(T->matriz[linha][coluna]=='_')
//             {
//                 casos=1;
//             }

//         }
//     }
//     if(casos!=0)
//     {
//         condicao2=1;
//         printf("\n Deu Velha!\n");
//         exit(0);
//     }
//     //preecher aleatoriamente as posições O
//     while(condicao==0)
//     {
//         linha=rand()%2;
//         coluna=rand()%2;
//         if(T->matriz[linha][coluna]=='_')
//         {
//             SetElemento(T,linha,coluna,'O');
//             condicao=1;
//         }
//     }
//     Imprime(*T);
//     //testa se jogador O é ganhador
//     for(linha=0;linha<3;linha++)
//     {
//     casos=TestaLinha(T,linha,'O');
//     if(casos==1)
//     {
//         printf("\n O vencedor foi O!\n");
//         exit(0);
//     }
//     for(coluna=0;coluna<3;coluna++)
//     {
//     casos=TestaColuna(T,linha,'O');
//     if(casos==1)
//     {
//         printf("\n O vencedor foi O!\n");
//         exit(0);
//     }
//     }
//     }
//     casos=TestaDiagonalDE(T,'O');
//     if(casos==1)
//     {
//         printf("O vencedor foi O! \n");
//         exit(0);
//     }
//     casos=TestaDiagonalED(T,'O');
//     if(casos==1)
//     {
//         printf("O vencedor foi O! \n");
//         exit(0);
//     }
//     casos=0;

//     //Testar se todo o tabuleiro foi preenchido
//     for(linha=0;linha<3;linha++)
//     {
//         for(coluna=0;coluna<3;coluna++)
//         {
//             if(T->matriz[linha][coluna]=='_')
//             {
//                 casos=1;
//             }

//         }
//     }
//     if(casos!=0)
//     {
//         condicao2=1;
//         printf("\n Deu Velha!\n");
//         exit(0);
//     }

//     }
//     break;

//     //2 jogadores
// case 2:
//     Imprime(*T); //tirar depois
//     //jogar até preecher toda a matriz
//     while(condicao2==0)
//     {
//     //ter certeza que o jogador não está preenchendo posição já ocupada
//     while(condicao==0)
//     {
//     printf("Usuário (X), por favor digite a linha e a coluna\n");
//     scanf("%d%d", &linha, &coluna);

//     //se estiver ocupada, preenche outra
//     if(T->matriz[linha][coluna]!= '_')
//     {
//         printf("Escolha outra posicao, esta ja esta preenchida\n");
//     }else//se não for diferente vai preecher
//     {
//          SetElemento(T,linha,coluna,'X');
//          condicao=1;
//     }

//     }

//     condicao=0;//zerar a condição para analisar caso O
//     linha=0;
//     coluna=0;
//     Imprime(*T);

//     //testar se já acabou o jogo e se X é ganhador
//     for(linha=0;linha<3;linha++)
//     {
//     casos=TestaLinha(T,linha,'X');
//     if(casos==1)
//     {
//         printf("\n O vencedor foi X!\n");
//         exit(0);
//     }
//     for(coluna=0;coluna<3;coluna++)
//     {
//     casos=TestaColuna(T,linha,'X');
//     if(casos==1)
//     {
//         printf("\n O vencedor foi X!\n");
//         exit(0);
//     }
//     }
//     }
//     casos=TestaDiagonalDE(T,'X');
//     if(casos==1)
//     {
//         printf("O vencedor foi X! \n");
//         exit(0);
//     }
//         casos=TestaDiagonalED(T,'X');
//     if(casos==1)
//     {
//         printf("O vencedor foi X! \n");
//         exit(0);
//     }
//     //Testar se todo o tabuleiro foi preenchido
//     for(linha=0;linha<3;linha++)
//     {
//         for(coluna=0;coluna<3;coluna++)
//         {
//             if(T->matriz[linha][coluna]=='_')
//             {
//                 casos=1;
//             }

//         }
//     }
//     if(casos!=0)
//     {
//         condicao2=1;
//         printf("\n Deu Velha!\n");
//         exit(0);
//     }
//     //preecher aleatoriamente as posições O
//     while(condicao==0)
//     {
//         printf("Jogador O, digite linha e coluna\n");
//         scanf("%d %d", &linha,&coluna);
//         if(T->matriz[linha][coluna]!='_')
//         {
//             printf("Posição já ocupada, escolha outra posição\n");

//         }else
//         {
//             SetElemento(T,linha,coluna,'O');
//             condicao=1;
//         }
//     }
//     Imprime(*T);
//     //testa se jogador O é ganhador
//     for(linha=0;linha<3;linha++)
//     {
//     casos=TestaLinha(T,linha,'O');
//     if(casos==1)
//     {
//         printf("\n O vencedor foi O!\n");
//         exit(0);
//     }
//     for(coluna=0;coluna<3;coluna++)
//     {
//     casos=TestaColuna(T,linha,'O');
//     if(casos==1)
//     {
//         printf("\n O vencedor foi O!\n");
//         exit(0);
//     }
//     }
//     }
//     casos=TestaDiagonalDE(T,'O');
//     if(casos==1)
//     {
//         printf("O vencedor foi O! \n");
//         exit(0);
//     }
//     casos=TestaDiagonalED(T,'O');
//     if(casos==1)
//     {
//         printf("O vencedor foi O! \n");
//         exit(0);
//     }
//     casos=0;

//     //Testar se todo o tabuleiro foi preenchido
//     for(linha=0;linha<3;linha++)
//     {
//         for(coluna=0;coluna<3;coluna++)
//         {
//             if(T->matriz[linha][coluna]=='_')
//             {
//                 casos=1;
//             }

//         }
//     }
//     if(casos!=0)
//     {
//         condicao2=1;
//         printf("\n Deu Velha!\n");
//         exit(0);
//     }

//     }

//     break;

//     //ler o jogo de um arquivo
// case 3:
//     casos=0;
//     FILE *entrada=fopen(nomearq,"r");
//     if(!entrada)
//     {
//         printf("Erro ao ler entrada\n");
//         exit(EXIT_FAILURE);
//     }
//     for(i=0;i<3;i++)
//     {
//         for(j=0;j<3;)
//         {
//             fscanf(entrada,"%c", &elemento);
//             if(elemento!='_')
//             {
//                 SetElemento(T,i,j,elemento);
//                 j++;
//             }
//         }
//     }
//     printf("\n");
//     Imprime(*T);
//     //TESTAR
//     //testar se já acabou o jogo e se X é ganhador
//     for(linha=0;linha<3;linha++)
//     {
//     casos=TestaLinha(T,linha,'X');
//     if(casos==1)
//     {
//         printf("\n O vencedor foi X!\n");
//         exit(0);
//     }
//     for(coluna=0;coluna<3;coluna++)
//     {
//     casos=TestaColuna(T,linha,'X');
//     if(casos==1)
//     {
//         printf("\n O vencedor foi X!\n");
//         exit(0);
//     }
//     }
//     }
//     casos=TestaDiagonalDE(T,'X');
//     if(casos==1)
//     {
//         printf("O vencedor foi X! \n");
//         exit(0);
//     }
//         casos=TestaDiagonalED(T,'X');
//     if(casos==1)
//     {
//         printf("O vencedor foi X! \n");
//         exit(0);
//     }
//     //TESTAR PARA O:
//      for(linha=0;linha<3;linha++)
//     {
//     casos=TestaLinha(T,linha,'O');
//     if(casos==1)
//     {
//         printf("\n O vencedor foi O!\n");
//         exit(0);
//     }
//     for(coluna=0;coluna<3;coluna++)
//     {
//     casos=TestaColuna(T,linha,'O');
//     if(casos==1)
//     {
//         printf("\n O vencedor foi O!\n");
//         exit(0);
//     }
//     }
//     }
//     casos=TestaDiagonalDE(T,'O');
//     if(casos==1)
//     {
//         printf("O vencedor foi O! \n");
//         exit(0);
//     }
//     casos=TestaDiagonalED(T,'O');
//     if(casos==1)
//     {
//         printf("O vencedor foi O! \n");
//         exit(0);
//     }
//     printf("\n Deu Velha!\n");
//     fclose(entrada);
//     break;
// }
// free(T);
// }

// int main()
// {
// int opcao;
// int a=0;
// int b=0;
// int aux=0;
// int casos = 10;
// char nome[10];
// char nomearq[100];
// char recebenomes[100];
// printf("Digite:\n CN - para caca niqueis.\nDigite um tamanho impar caso queira jogo CN.\n Digite: Velha - para jogo da velha.\n  Para usar tabuleiro de arquivo, digite o nome do arquivo.\nEx: CN 3 dados.txt\n");
// scanf("%s %d %s", &nome, &a, &nomearq);

// while(b==0)
// {
// if(nome=='CN')
// {
//     //Se é impar
//     //SE é menor que 10

//     aux=a%2;
//     if(aux==0 || a>10)
//     {
//         if(aux==0 && a<11)
//     {
//         printf("\nDigite outro valor para tamanho. O valor tem que ser ímpar.");
//     }
//     if(a>10)
//     {
//         printf("\nDigite outro valor para tamanho. O valor tem que ser menos ou igual a 10 e ímpar.");
//     }
//     }
//     if(aux!=0 && a<11)
//     {
//         b=1;
//     }
// }

// if (nome=='Velha')
// {
//     if(a>3)
//     {
//         printf("\n AS opcoes de jogo da velha vao ate 3. Digite um valor valido.\n");
//     }else
//     b=1;
// }
// if(nome!='Velha' && nome!='CN')
// {
//     printf("\nNome de jogo invalido!As opcoes sao : CN - Caça niqueis ou Velha - jogo da velha \n");
// }
// }
// opcao=nome;
// switch(opcao)
// {
// case 1:
//     CacaNiqueis(a, nomearq);


//     //PAREI AQUI
//     break;

// case 2:
//     Velha(a,nomearq);

//     break;

// }



// return 0;
// }