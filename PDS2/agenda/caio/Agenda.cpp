#include <iostream>
#include <fstream>
#include <string>
#include "Agenda.hpp"

using namespace std;

// ############## MÉTODOS DA AGENDA ############## //

// CONSTRUTOR DA AGENDA
Agenda::Agenda(int _ano) {
	ano = _ano;
	meses = NULL;

	// DEFINE O NÚMERO DE DIAS DE FEVEREIRO DE ACORDO COM SER OU NÃO BISSEXTO
	int dias_fevereiro = anoBis(ano) ? 29 : 28;

	// INSERE OS MESES DO ANO
	this->insereMes("janeiro", 31);
	this->insereMes("fevereiro", dias_fevereiro);
	this->insereMes("março", 31);
	this->insereMes("abril", 30);
	this->insereMes("maio", 31);
	this->insereMes("junho", 30);
	this->insereMes("julho", 31);
	this->insereMes("agosto", 31);
	this->insereMes("setembro", 30);
	this->insereMes("outubro", 31);
	this->insereMes("novembro", 30);
	this->insereMes("dezembro", 31);
}

// DEFINE SE O ANO É BISSEXTO OU NÃO
bool Agenda::anoBis(int ano) {
	if (ano % 4 == 0) {
		if (ano % 100 == 0) {
			if (ano % 400 == 0) return true;
			else return false;
		} else return true;
	} else return false;
}

// INSERE UM MÊS NA AGENDA
void Agenda	::insereMes(string _nome, int _dias) {
	Mes * novo_mes = new Mes(_nome, _dias);
	Mes * aux = this->meses;

	if (!aux) this->meses = novo_mes;

	else {
		while (aux->prox) aux = aux->prox;
		aux->prox = novo_mes;
	}
}

// INSERE UM COMPROMISSO NA AGENDA
bool Agenda::insereCompromisso(string _mes, int _dia, int _hora, string _descricao) {
	
	if(!VerificaDados(_mes, _dia, _hora)) return false;
	if(verificaCompromisso(_mes, _dia, _hora)){
		cout << "Já existe compromisso neste horário." << endl;
		return false;
	}

	Mes * mes = this->meses;
	Compromisso * novo = new Compromisso(_hora, _descricao);
	
	string mes_tolower = "";
	for (unsigned int i = 0; i < _mes.size(); ++i) mes_tolower += tolower(_mes[i]);
	while (mes->nome != mes_tolower) mes = mes->prox;

	// CASO EM QUE SERÁ O PRIMEIRO COMPROMISSO A SER INSERIDO
	Compromisso * aux = mes->dias[_dia - 1]->compromisso;


	if (!aux) {
		mes->dias[_dia - 1]->compromisso = novo;
		return true;
	}

	// COLOCAR O COMPROMISSO NO COMEÇO
	if (aux->hora > novo->hora) {
		mes->dias[_dia - 1]->compromisso = novo;
		novo->prox = aux;
		return true;
	}

	// INSERE O COMPROMISSO DE FORMA ORDENADA
	Compromisso * aux2 = aux->prox;
	while (aux2) {
		if (aux2->hora > novo->hora) {
			aux->prox = novo;
			novo->prox = aux2;
			return true;
		}
		aux = aux->prox;
		aux2 = aux2->prox;
	}

	aux->prox = novo;
	return true;
}

// LISTA TODOS OS COMPROMISSOS
void Agenda::listaTodosOsCompromissos() {
	Mes * mes = this->meses;
	Compromisso * comp;
	while (mes) {
		cout << "* " << mes->nome << endl;
		for (int i = 0; i < mes->num_dias; ++i) {
			comp = mes->dias[i]->compromisso;
			while (comp) {
				cout << " >> Descrição: " << comp->descricao << endl;
				cout << "    Dia: " << i + 1 << " de " << mes->nome << " de " << this->ano << endl;
				cout << "    Horário: " << comp->hora << " horas" << endl;
				comp = comp->prox;
			}
		}
		mes = mes->prox;
	}
}

// RETORNA SE EXISTE COMPRIMISSO NO HORÁRIO EM QUESTÃO OU NÃO
bool Agenda::verificaCompromisso(string _mes, int _dia, int _hora) {

	if(!VerificaDados(_mes, _dia, _hora)) return false;

	// PERCORRE TODOS OS COMPROMISSO ATÉ ACHAR OU NÃO O BUSCADO
	Mes * mes = this->meses;

	string mes_tolower = "";
	for (unsigned int i = 0; i < _mes.size(); ++i) mes_tolower += tolower(_mes[i]);
	while (mes->nome != mes_tolower) mes = mes->prox;

	Compromisso * aux = mes->dias[_dia - 1]->compromisso;
	while (aux) {
		if (aux->hora == _hora) return true;
		aux = aux->prox;
	}
	return false;
}

// REMOVE UM COMPROMISSO DA AGENDA
void Agenda::removeCompromisso(string _mes, int _dia, int _hora) {
	
	if(!VerificaDados(_mes, _dia, _hora)) return;
	if(!verificaCompromisso(_mes, _dia, _hora)){
		cout << "Não existe compromisso neste horário." << endl;
		return;
	}

	string mes_tolower = "";
	for (unsigned int i = 0; i < _mes.size(); ++i) mes_tolower += tolower(_mes[i]);
	Mes * mes = this->meses;
	while (mes->nome != mes_tolower) mes = mes->prox;

	// PERCORRE OS COMPRIMISSOS ATÉ ACHAR O QUE SERÁ REMOVIDO
	Compromisso * comp = mes->dias[_dia-1]->compromisso;
	Compromisso * aux = comp;

	while(comp->hora != _hora && comp != NULL){
		aux = comp;
		comp = comp->prox;
	}

	if(aux == comp){
		mes->dias[_dia-1]->compromisso = comp->prox;
		delete(comp);
		cout << endl << "Compromisso removido." << endl;
		return;
	}

	// REMOVE O COMPROMISSO
	aux->prox = comp->prox;
	cout << endl << "Compromisso removido." << endl;
	delete(comp);
}

bool Agenda::VerificaDados(string _mes, int _dia, int _hora){
	// TRATAMENTO DE DADOS INVÁLIDOS
	if(_hora < 0 || _hora > 23){
		cout << "Hora inválida!" << endl;
		return false;
	}
	string mes_tolower = "";
	for (unsigned int i = 0; i < _mes.size(); ++i) mes_tolower += tolower(_mes[i]);

	Mes * mes = this->meses;
	while (mes->nome != mes_tolower) {
		if (mes->nome == "dezembro" && mes->nome != mes_tolower) {
			cout << endl << "O mês digitado não é válido. Está escrito corretamente?" << endl;
			return false;
		}
		mes = mes->prox;
	}

	// TRATAMENTO DE DIAS INVÁLIDOS
	if (_dia < 1 || _dia > mes->num_dias) {
		cout << "Não existe dia " << _dia << " no mês de " << mes_tolower << "!" << endl;
		return false;
	}
	return true;
}

// FECHA A AGENDA E SALVA OS DADOS EM UM ARQUIVO DE SAÍDA
void Agenda::fechaAgenda(){
	ofstream agenda_file;
	agenda_file.open(to_string(this->ano) + ".txt");
	
	if (agenda_file.is_open()){
		Mes * aux = this->meses;
		agenda_file << this->ano << endl;
		Compromisso * comp;
		while (aux) {
			// ESCREVE OS DADOS DA AGENDA NO ARQUIVO DE SAÍDA
			agenda_file << "mes: --------------- " << aux->nome << endl;
			for (int i = 0; i < aux->num_dias; ++i){
				comp = aux->dias[i]->compromisso;
				while(comp){
					agenda_file << ">>compromisso: " << comp->descricao << endl;
					agenda_file << "hora: " << comp->hora << endl;
					agenda_file << "dia: " << i+1 << endl;
					comp = comp->prox;
				}
			}
			aux = aux->prox;
		}
		agenda_file.close();
	}
	else cout << "Problemas ao abrir o arquivo";
}

// DESTRUTOR DO TAD AGENDA (LIBERA A MEMÓRIA)
Agenda::~Agenda() {
	Mes * cabeca = meses;
	Mes * aux = cabeca->prox;
	while (aux) {
		aux = cabeca->prox;
		delete cabeca;
		cabeca = aux;
	}
	delete cabeca;
}

// ############## MÉTODOS DOS MESES ############## //

// CONSTRUTOR DE MESES
Mes::Mes(string _nome, int _dias) {
	nome = _nome;
	num_dias = _dias;
	prox = NULL;

	dias = new Dia*[num_dias];
	for (int i = 0; i < num_dias; i++)
		dias[i] = new Dia(i + 1);
}

// DESTRUTOR DO TAD MES (LIBERA A MEMÓRIA)
Mes::~Mes() {
	for (int i = 0; i < this->num_dias; ++i) delete dias[i];
	delete [] dias;
}

// ############## MÉTODOS DOS DIAS ############## //

// CONSTRUTOR DE DIAS
Dia::Dia(int _id) {
	id = _id;
	compromisso = NULL;
}

// DESTRUTOR DO TAD DIA (LIBERA A MEMÓRIA)
Dia::~Dia() {
	Compromisso * cabeca = compromisso;
	if (!cabeca) return;
	Compromisso * aux = cabeca->prox;
	while (aux) {
		aux = cabeca->prox;
		delete cabeca;
		cabeca = aux;
	}
	delete cabeca;
}

// ############## MÉTODOS DOS COMPROMISSOS ############## //

// CONSTRUTOR DE COMPROMISSOS
Compromisso::Compromisso(int _hora, string _descricao) {
	hora = _hora;
	descricao = _descricao;
	prox = NULL;
}

