#include <iostream>
#include "List.hpp"

void printListAndSize(List* L){
	if(L->size == 0) std::cout << '-' << std::endl;
	else L->print();
	std::cout << L->size << std::endl;
}

int main(){
    
    List *L = new List();
    
    int amount, max;
    std::cin >> max >> amount;
    if(max < 0) max = -1;

    // faz inserções
    for (int i = 0; i <= max; ++i) L->insert(i);
	printListAndSize(L);
    
    // remove k primeiros itens
    for (int i = 0; i < amount; ++i) L->removeFirst();
	printListAndSize(L);

	// remove os pares
	for (int i = 0; i <= max-amount; i+=2) L->remove(i);
	printListAndSize(L);

	L->clearList();
    delete L;
    L = NULL;
	return 0;
}