#include <iostream>

#include "Televisao.hpp"
#include "Controle.hpp"

using namespace std;

int main(){

	Televisao * tv = new Televisao();
    Controle * ct = new Controle(tv);

    string instrucao;
    int valor;

    while(cin >> instrucao){

    	if(instrucao == "SC"){
    		cin >> valor;
    		ct->setCanal(valor);
    	}

    	if(instrucao == "SV"){
    		cin >> valor;
    		ct->setVolume(valor);
    	}

		if(instrucao == "MC") cout << tv->getCanal() << endl;
		if(instrucao == "MV") cout << tv->getVolume() << endl;
		if(instrucao == "AC") ct->aumentaCanal();
		if(instrucao == "AV") ct->aumentaVolume();
		if(instrucao == "DC") ct->diminuiCanal();
		if(instrucao == "DV") ct->diminuiVolume();
    
    }
    
    delete(ct);
    delete(tv);
    return 0;
}