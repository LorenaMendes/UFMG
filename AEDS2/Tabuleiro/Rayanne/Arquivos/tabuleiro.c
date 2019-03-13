#include <stdio.h>
#include <stdlib.h>
#include "Tabuleiro.h"


//Definir o tamanho do tabuleiro que vai ser utilizado
void SetTamanho(Tabuleiro *T, int n)
{
    T->tamanho=n;
}
//Colocar um elemento c em uma posição (i,j) do tabuleiro.
void SetElemento(Tabuleiro *T, int i, int j, char c)
{
    T->matriz[i][j]=c;
}
//Recuperar o elemento de uma posição (i,j) o tabuleiro:
char GetElemento(Tabuleiro *T, int i, int j)
{
    char elemento = ' ';
    elemento=T->matriz[i][j];
    return elemento;
}
//Colocar um mesmo elemento c em todas as posições do tabuleiro
void MarcaTodos(Tabuleiro *T, char c)
{
    int i,j;
    for(i=0; i<T->tamanho;i++)
    {
        for(j=0;j<T->tamanho;i++)
        {
            T->matriz[i][j]=c;
        }
    }
}
//Testar se uma linha i do tabuleiro possui todos os elementos iguais a c, retornando true(1) ou false 0
int TestaLinha(Tabuleiro *T, int i, char c)
{
    int resultado = 10;
    int coluna  = 0;
    for(coluna=0; coluna<T->tamanho; coluna++)
    {
        if(T->matriz[i][coluna]!=c)
        {
        resultado=0;
        return resultado;
        };
        if(coluna==T->tamanho)
            resultado=1;

    }
    if(resultado==10)
    printf("erro!");
    resultado=1;
    return resultado;
}
//Testar se uma coluna j do tabuleiro possui todos os elementos iguais a c, retornando true(1) ou false (0)
int TestaColuna(Tabuleiro *T, int j, char c)
{
    int resultado = 10;
    int linha  = 0;
    for(linha=0; linha<T->tamanho; linha++)
    {
        if(T->matriz[linha][j]!=c)
        {
        resultado=0;
        return resultado;
        };
        if(linha==T->tamanho)
            resultado=1;

    }
    if(resultado==10)
    printf("erro!");
    resultado=1;
    return resultado;
}
//Testar se a diagonal esq-dir possui todos os elementos iguais a c, retornando true(1) ou false (0)
int TestaDiagonalED(Tabuleiro *T, char c)
{
    int resultado = 10;
    int linha  = 0;
    int coluna = 0;
    for(linha=0; linha<T->tamanho; linha++, coluna++)
    {
        if(T->matriz[linha][coluna]!=c)
        {
        resultado=0;
        return resultado;
        };
        if(linha==T->tamanho)
            resultado=1;

    }
    if(resultado==10)
    printf("erro!");
    resultado=1;
    return resultado;
}
//Testar se a diagonal dir-esq possui todos os elementos iguais a c, retornando true(1) ou false (0)
int TestaDiagonalDE(Tabuleiro *T, char c)
{
    int resultado = 10;
    int linha  = 0;
    int coluna = T->tamanho-1;
    for(linha=0;linha<T->tamanho; linha++, coluna--)
    {
        if(T->matriz[linha][coluna]!=c)
        {
        resultado=0;
        return resultado;
        };
        if(linha==T->tamanho)
            resultado=1;
    }
    if(resultado==10)
    printf("erro!");
    resultado=1;
    return resultado;
}
//Testar se uma linha i do tabuleiro possui todos os elementos diferentes, retornando true(1) ou false (0)
int TestaDiferente(Tabuleiro *T, int i)
{
    int resultado = 10;
    int coluna;
    int aux;
    char elemento = ' ';
    for(aux=0; aux<T->tamanho;aux++)
    {
        elemento = T-> matriz[i][aux];
        for(coluna = aux; coluna<T->tamanho; )
        {
            coluna++;
            if(elemento==T->matriz[i][coluna])
            {
                resultado=0;
                return resultado;
            }

        }
    }
    if(aux==T->tamanho)
    resultado = 1;
    return resultado;

}
//Imprimir tabuleiro
void Imprime(Tabuleiro *T)
{

    int linha;
    int coluna;

for (linha=0; linha<T->tamanho;linha++)
{
    for(coluna=0; coluna<T->tamanho; coluna ++)
    {
        printf("%c", T->matriz[linha][coluna]);
    }
    printf("\n");
}

}

