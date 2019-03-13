#include<stdio.h>
#include<stdlib.h>
#include "Tabuleiro.c"

void CacaNiqueis(int tamanho, char *nomearq)
{

char elemento = ' ';
int i=0;
int j=0;
int aux=0;

Tabuleiro*T=(Tabuleiro*)malloc(sizeof(Tabuleiro));
SetTamanho(T, tamanho);
if(nomearq!=' ')
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
}


void Velha(int opcao, char *nomearq)
{

int a=0;
int b=0;
int i=0;
int j=0;
int aux=0;
int casos = 10;
int linha=0;
int coluna=0;
int condicao=0;
int condicao2=0;
char elemento =' ';
Tabuleiro*T=(Tabuleiro*)malloc(sizeof(Tabuleiro));
SetTamanho(T, 3);
MarcaTodos(T,'_');

printf("Selecione a modalidade:\n 1-jogador versus computador.\n 2- 2 jogadores. \n 3- leia o jogo de um arquivo.\n");
scanf("%d", &opcao);

switch (opcao)
{
    //jogador versus computador
case 1:
    Imprime(T); //tirar depois
    //jogar at� preecher toda a matriz
    while(condicao2==0)
    {
    //ter certeza que o jogador n�o est� preenchendo posi��o j� ocupada
    while(condicao==0)
    {
    printf("Usu�rio (X), por favor digite a linha e a coluna\n");
    scanf("%d%d", &linha, &coluna);

    //se estiver ocupada, preenche outra
    if(T->matriz[linha][coluna]!= '_')
    {
        printf("Escolha outra posicao, esta ja esta preenchida\n");
    }else//se n�o for diferente vai preecher
    {
         SetElemento(T,linha,coluna,'X');
         condicao=1;
    }

    }

    condicao=0;//zerar a condi��o para analisar caso O
    linha=0;
    coluna=0;
    Imprime(T);

    //testar se j� acabou o jogo e se X � ganhador
    for(linha=0;linha<3;linha++)
    {
    casos=TestaLinha(T,linha,'X');
    if(casos==1)
    {
        printf("\n O vencedor foi X!\n");
        exit(0);
    }
    for(coluna=0;coluna<3;coluna++)
    {
    casos=TestaColuna(T,linha,'X');
    if(casos==1)
    {
        printf("\n O vencedor foi X!\n");
        exit(0);
    }
    }
    }
    casos=TestaDiagonalDE(T,'X');
    if(casos==1)
    {
        printf("O vencedor foi X! \n");
        exit(0);
    }
        casos=TestaDiagonalED(T,'X');
    if(casos==1)
    {
        printf("O vencedor foi X! \n");
        exit(0);
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
    if(casos!=0)
    {
        condicao2=1;
        printf("\n Deu Velha!\n");
        exit(0);
    }
    //preecher aleatoriamente as posi��es O
    while(condicao==0)
    {
        linha=rand()%2;
        coluna=rand()%2;
        if(T->matriz[linha][coluna]=='_')
        {
            SetElemento(T,linha,coluna,'O');
            condicao=1;
        }
    }
    Imprime(T);
    //testa se jogador O � ganhador
    for(linha=0;linha<3;linha++)
    {
    casos=TestaLinha(T,linha,'O');
    if(casos==1)
    {
        printf("\n O vencedor foi O!\n");
        exit(0);
    }
    for(coluna=0;coluna<3;coluna++)
    {
    casos=TestaColuna(T,linha,'O');
    if(casos==1)
    {
        printf("\n O vencedor foi O!\n");
        exit(0);
    }
    }
    }
    casos=TestaDiagonalDE(T,'O');
    if(casos==1)
    {
        printf("O vencedor foi O! \n");
        exit(0);
    }
    casos=TestaDiagonalED(T,'O');
    if(casos==1)
    {
        printf("O vencedor foi O! \n");
        exit(0);
    }
    casos=0;

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
    if(casos!=0)
    {
        condicao2=1;
        printf("\n Deu Velha!\n");
        exit(0);
    }

    }
    break;

    //2 jogadores
case 2:
    Imprime(T); //tirar depois
    //jogar at� preecher toda a matriz
    while(condicao2==0)
    {
    //ter certeza que o jogador n�o est� preenchendo posi��o j� ocupada
    while(condicao==0)
    {
    printf("Usu�rio (X), por favor digite a linha e a coluna\n");
    scanf("%d%d", &linha, &coluna);

    //se estiver ocupada, preenche outra
    if(T->matriz[linha][coluna]!= '_')
    {
        printf("Escolha outra posicao, esta ja esta preenchida\n");
    }else//se n�o for diferente vai preecher
    {
         SetElemento(T,linha,coluna,'X');
         condicao=1;
    }

    }

    condicao=0;//zerar a condi��o para analisar caso O
    linha=0;
    coluna=0;
    Imprime(T);

    //testar se j� acabou o jogo e se X � ganhador
    for(linha=0;linha<3;linha++)
    {
    casos=TestaLinha(T,linha,'X');
    if(casos==1)
    {
        printf("\n O vencedor foi X!\n");
        exit(0);
    }
    for(coluna=0;coluna<3;coluna++)
    {
    casos=TestaColuna(T,linha,'X');
    if(casos==1)
    {
        printf("\n O vencedor foi X!\n");
        exit(0);
    }
    }
    }
    casos=TestaDiagonalDE(T,'X');
    if(casos==1)
    {
        printf("O vencedor foi X! \n");
        exit(0);
    }
        casos=TestaDiagonalED(T,'X');
    if(casos==1)
    {
        printf("O vencedor foi X! \n");
        exit(0);
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
    if(casos!=0)
    {
        condicao2=1;
        printf("\n Deu Velha!\n");
        exit(0);
    }
    //preecher aleatoriamente as posi��es O
    while(condicao==0)
    {
        printf("Jogador O, digite linha e coluna\n");
        scanf("%d %d", &linha,&coluna);
        if(T->matriz[linha][coluna]!='_')
        {
            printf("Posi��o j� ocupada, escolha outra posi��o\n");

        }else
        {
            SetElemento(T,linha,coluna,'O');
            condicao=1;
        }
    }
    Imprime(T);
    //testa se jogador O � ganhador
    for(linha=0;linha<3;linha++)
    {
    casos=TestaLinha(T,linha,'O');
    if(casos==1)
    {
        printf("\n O vencedor foi O!\n");
        exit(0);
    }
    for(coluna=0;coluna<3;coluna++)
    {
    casos=TestaColuna(T,linha,'O');
    if(casos==1)
    {
        printf("\n O vencedor foi O!\n");
        exit(0);
    }
    }
    }
    casos=TestaDiagonalDE(T,'O');
    if(casos==1)
    {
        printf("O vencedor foi O! \n");
        exit(0);
    }
    casos=TestaDiagonalED(T,'O');
    if(casos==1)
    {
        printf("O vencedor foi O! \n");
        exit(0);
    }
    casos=0;

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
    if(casos!=0)
    {
        condicao2=1;
        printf("\n Deu Velha!\n");
        exit(0);
    }

    }

    break;

    //ler o jogo de um arquivo
case 3:
    casos=0;
    FILE *entrada=fopen(nomearq,"r");
    if(!entrada)
    {
        printf("Erro ao ler entrada\n");
        exit(EXIT_FAILURE);
    }
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;)
        {
            fscanf(entrada,"%c", &elemento);
            if(elemento!='_')
            {
                SetElemento(T,i,j,elemento);
                j++;
            }
        }
    }
    printf("\n");
    Imprime(T);
    //TESTAR
    //testar se j� acabou o jogo e se X � ganhador
    for(linha=0;linha<3;linha++)
    {
    casos=TestaLinha(T,linha,'X');
    if(casos==1)
    {
        printf("\n O vencedor foi X!\n");
        exit(0);
    }
    for(coluna=0;coluna<3;coluna++)
    {
    casos=TestaColuna(T,linha,'X');
    if(casos==1)
    {
        printf("\n O vencedor foi X!\n");
        exit(0);
    }
    }
    }
    casos=TestaDiagonalDE(T,'X');
    if(casos==1)
    {
        printf("O vencedor foi X! \n");
        exit(0);
    }
        casos=TestaDiagonalED(T,'X');
    if(casos==1)
    {
        printf("O vencedor foi X! \n");
        exit(0);
    }
    //TESTAR PARA O:
     for(linha=0;linha<3;linha++)
    {
    casos=TestaLinha(T,linha,'O');
    if(casos==1)
    {
        printf("\n O vencedor foi O!\n");
        exit(0);
    }
    for(coluna=0;coluna<3;coluna++)
    {
    casos=TestaColuna(T,linha,'O');
    if(casos==1)
    {
        printf("\n O vencedor foi O!\n");
        exit(0);
    }
    }
    }
    casos=TestaDiagonalDE(T,'O');
    if(casos==1)
    {
        printf("O vencedor foi O! \n");
        exit(0);
    }
    casos=TestaDiagonalED(T,'O');
    if(casos==1)
    {
        printf("O vencedor foi O! \n");
        exit(0);
    }
    printf("\n Deu Velha!\n");
    fclose(entrada);
    break;
}
free(T);
}

int main()
{
int opcao;
int a=0;
int b=0;
int aux=0;
int casos = 10;
char nome[10];
char nomearq[100];
char recebenomes[100];
printf("Digite:\n CN - para caca niqueis.\nDigite um tamanho impar caso queira jogo CN.\n Digite: Velha - para jogo da velha.\n  Para usar tabuleiro de arquivo, digite o nome do arquivo.\nEx: CN 3 dados.txt\n");
scanf("%s %d %s", &nome, &a, &nomearq);

while(b==0)
{
if(nome=='CN')
{
    //Se � impar
    //SE � menor que 10

    aux=a%2;
    if(aux==0 || a>10)
    {
        if(aux==0 && a<11)
    {
        printf("\nDigite outro valor para tamanho. O valor tem que ser �mpar.");
    }
    if(a>10)
    {
        printf("\nDigite outro valor para tamanho. O valor tem que ser menos ou igual a 10 e �mpar.");
    }
    }
    if(aux!=0 && a<11)
    {
        b=1;
    }
}

if (nome=='Velha')
{
    if(a>3)
    {
        printf("\n AS opcoes de jogo da velha vao ate 3. Digite um valor valido.\n");
    }else
    b=1;
}
if(nome!='Velha' && nome!='CN')
{
    printf("\nNome de jogo invalido!As opcoes sao : CN - Ca�a niqueis ou Velha - jogo da velha \n");
}
}
opcao=nome;
switch(opcao)
{
case 1:
    CacaNiqueis(a, nomearq);


    //PAREI AQUI
    break;

case 2:
    Velha(a,nomearq);

    break;

}



return 0;
}
