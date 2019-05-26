#include <iostream>
#include "Animal.hpp"
#include <map>
#include <vector>

using namespace std;

int calculaPorcentagem(int, int);

int main() {

	char comando;
	int semana_atual, semana_anterior=0, peso_bicho;
	string nome_bicho;

	map<string, Animal*> zoo;
	map<string, Animal*>::iterator it;

	while (cin >> comando) {
	
		if (comando == 'S'){
			cin >> semana_atual;
			
			for (it = zoo.begin(); it != zoo.end(); it++){
				if(it->second->getTempoPesagem(semana_anterior) >= 2){
					cout << "Semana " << semana_anterior << ": Aviso! Animal ";
					cout << it->second->getNome() << " nao foi pesado por ";
					cout << it->second->getTempoPesagem(semana_anterior) << " semanas." << endl;
				}
			}
			semana_anterior = semana_atual;
		}
		else {

			cin >> nome_bicho >> peso_bicho;
			
			if (!zoo[nome_bicho]) {
				Animal * animal = new Animal();
				animal->setNome(nome_bicho);
				zoo[nome_bicho] = animal;
			}
		
			if(calculaPorcentagem(peso_bicho, zoo[nome_bicho]->getPeso())){
				cout << "Semana " << semana_atual << ": Aviso! Animal ";
				cout << zoo[nome_bicho]->getNome() << " perdeu 10% ou mais de seu peso." << endl;
			}

			zoo[nome_bicho]->setPeso(peso_bicho, semana_atual);
		}
	}

	for(it = zoo.begin(); it !=zoo.end(); it++){

		if(it->second->getTempoPesagem(semana_anterior) >= 2){
			cout << "Semana " << semana_anterior << ": Aviso! Animal ";
			cout << it->second->getNome() << " nao foi pesado por ";
			cout << it->second->getTempoPesagem(semana_anterior) << " semanas." << endl;
		}
	}

	return 0;
}

int calculaPorcentagem(int novoPeso, int peso){
	if(novoPeso >= peso) return 0;
	int porcentagem = peso * 0.1;
	if(peso - novoPeso >= porcentagem) return 1;
	else return 0;
}