#ifndef __Bancos__
#define __Bancos__

// estrutura de um banco
typedef struct Banco{
	int id; // identificador do banco
	int tipo; // tipo do banco
} Banco;

// função que cria e retorna um banco
Banco CriaBanco(int);
//função que funde todos os bancos
void FundeBancos(Banco*, int, int, int);

#endif