#include "Agenda.hpp"
#include "Mes.hpp"
#include "Dia.hpp"
#include "Compromisso.hpp"

#include <iostream>
#include <fstream>
#include <string>

Agenda::Agenda(int ano){
	this->ano = ano;
	Mes * novo;
	string meses[12] = {"31Janeiro", "28Fevereiro", "31Março",
						"30Abril", "31Maio", "30Junho",
						"31Julho", "31Agosto", "30Setembro",
						"31Outubro","30Novembro", "31Dezembro"};
	string dias, nome;
	for (int i = 0; i < 12; i++){
		dias = meses[i].substr(0,2);
		nome = meses[i].substr(2);
		if(i == 1){
			if(ano % 4 == 0 && (ano % 400 == 0 || ano % 100 != 0))
				novo = new Mes(nome,i,29);
			else novo = new Mes(nome,i,28);
		} else novo = new Mes(nome,i,stoi(dias));
	}
	this->AdicionaMes(novo);
}

void Agenda::AdicionaMes(Mes* novo){
	Mes* aux = this->lista_mes;
	if(aux == NULL) this->lista_mes = novo;
	else{
		while(aux->seg != NULL)
			aux = aux->seg;
		aux->seg = novo;
	}
}