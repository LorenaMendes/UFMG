#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>

using namespace std;

class Animal{
	
	private:
		string nome;
		int peso;
		int dataPesagem;
			
	public:
		string getNome();
		int getPeso();
		int getTempoPesagem(int hoje);
	
		void setNome(string novoNome);
		void setPeso(int novoPeso, int novaData);
};

#endif