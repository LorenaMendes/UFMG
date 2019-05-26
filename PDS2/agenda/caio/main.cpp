#include <iostream>
#include <fstream>
#include <string>
#include "Agenda.hpp"

using namespace std;

int main(){

	// CRIANDO O MENU
	Agenda * agenda;
	cout << "Bem-vindo(a) à Agenda Online!" << endl;
	cout << "Deseja abrir a agenda referente a qual ano?" << endl;
	int ano;
	do{
		cin >> ano;
		if(ano < 2000 || ano > 2050) cout << "Escolha um ano entre 2000 e 2050." << endl;
	} while(ano < 2000 || ano > 2050);


	// ABRINDO O ARQUIVO
	ifstream agenda_file;
	string nome_arquivo = to_string(ano) + ".txt";
	agenda_file.open(nome_arquivo);

	// CRIA UM ARQUIVO CASO O DESEJADO NÃO EXISTA
	if(!agenda_file){
		cout << "Criando nova agenda..." << endl;
		ofstream nova_agenda;
		nova_agenda.open(to_string(ano) + ".txt");
		nova_agenda << ano << endl;
		nova_agenda.close();
		agenda = new Agenda(ano);
		agenda->fechaAgenda();
	} else agenda = new Agenda(ano);

	agenda_file.close();
	
	string _mes, _descricao, _comando, _temp;
	int _ano, _dia, _hora;
	
	agenda_file.open(nome_arquivo);
	agenda_file >> _ano;
	
	// LÊ OS DADOS DE UM ARQUIVO E OS CARREGA NA AGENDA ATUAL
	while(!agenda_file.eof()){
		agenda_file >> _comando;
		if(_comando == "mes:"){
			agenda_file >> _temp >> _mes;
		} else if(_comando == ">>compromisso:"){
			getline(agenda_file, _descricao);
			agenda_file >> _temp >> _hora;
			agenda_file >> _temp >> _dia;
			agenda->insereCompromisso(_mes, _dia, _hora, _descricao);
		}
	}

	// OPÇÕES PARA O USUÁRIO INTERAGIR COM A AGENDA 
	int opt;
	bool parada = true;
	while(parada){
		cout << endl;
		cout << "O que você deseja fazer na sua agenda?" << endl;
		cout << "1 - Inserir um compromisso" << endl;
		cout << "2 - Checar se existe compromisso em algum horário" << endl;
		cout << "3 - Remover um compromisso" << endl;
		cout << "4 - Visualizar agenda" << endl;
		cout << "5 - Fechar a agenda" << endl;
		do{
			cout << "Opção desejada: ";
			cin >> opt;
			if(opt < 0 || opt > 5) cout << "Digite uma opção válida." << endl;
		} while(opt < 0 || opt > 5);

		// INSERÇÃO
		if(opt == 1){
			string teste;
			string mes, descricao;
			int dia, hora;
			cout << endl;
			cout << "Digite o nome do mês: ";
			cin >> mes;
			cout << "Digite o dia: ";
			cin >> dia;
			cout << "Digite a hora: ";
			cin >> hora;
			cout << "Digite a descrição: ";
			cin.ignore();
			getline(cin, descricao);
			cout << endl;
			if(agenda->insereCompromisso(mes, dia, hora, descricao))
				cout << "Compromisso inserido." << endl;
		
		// VERIFICAÇÃO DE EXISTÊNCIA DE COMPROMISSO
		} else if(opt == 2){
			cout << endl;
			string mes;
			int dia, hora;
			cout << "Digite o nome do mês: ";
			cin >> mes;
			cout << "Digite o dia: ";
			cin >> dia;
			cout << "Digite a hora: ";
			cin >> hora;
			if(agenda->VerificaDados(mes, dia, hora)){
				if(!agenda->verificaCompromisso(mes, dia, hora))
					cout << endl << "Não existe compromisso às " << hora << " horas do dia " << dia << " de " << mes << "." << endl;
				else cout << endl << "Você tem um compromisso às " << hora << " horas do dia " << dia << " de " << mes << "." << endl;
			}

		// REMOÇÃO	
		} else if(opt == 3){
			cout << endl;
			string mes;
			int dia, hora;
			cout << "Digite o nome do mês: ";
			cin >> mes;
			cout << "Digite o dia: ";
			cin >> dia;
			cout << "Digite a hora: ";
			cin >> hora;
			agenda->removeCompromisso(mes, dia, hora);
		
		// IMPRIME A AGENDA
		} else if(opt == 4){
			cout << endl;
			agenda->listaTodosOsCompromissos();
		
		// FECHA A AGENDA A TUAL
		} else {
			cout << endl;
			agenda->fechaAgenda();
			cout << "Obrigado por usar a Agenda Online!" << endl;
			parada = false;
		}
	}

	// LIBERA O ESPAÇO GASTO PELA AGENDA ATUAL
	delete(agenda);
	return 0;
}