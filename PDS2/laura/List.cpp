#include "List.hpp"

using namespace std;
List::List(){
	this->size = 0;
	this->head = NULL;
}

void List::insert(int value){
    Node* node = new Node;
	node->value = value;
	node->next = this->head;
	this->head = node;
	this->size++;
	node = NULL;
	delete node;
}

void List::clearList(){
	int tam = this->size;
	for(int i = 0; i < tam; i++){
		this->removeFirst();
	}
	this->head = NULL;
	delete this->head;
}

void List::print(){
	Node* aux = this->head;
	if(this->size > 0){
		while(aux){
			cout << aux->value << " ";
			aux = aux->next;
		}
		std::cout<<std::endl;
		aux = NULL;
		delete aux;
	}
	else{
	    std::cout<<"-"<<endl;
	    aux = NULL;
		delete aux;
		return;
	}
}

int List::removeFirst(){
	if(this->size == 0){
	    return 0;
	}
	else{
	    Node* current = this->head;
	    this->head = this->head->next;
	    int x = current->value;
    	delete current;
    	this->size--;
    	return x;
	}
}

int List::indexOf(int value){
	if(this->size > 0){
		Node* head = this->head;
		int index = 0;
		while(head && head->value != value){
			index++;
			head = head->next;
		}
		if(head->value == value)
			head = NULL;
			delete head;
			return index; 
		head = NULL;
		delete head;
		return -1;
	}
	else{
		return -1;
	}
}

void List::remove(int value){
	if(this->size == 0){
		return;
	}
	else if(this->head->value == value){
		Node* current = this->head;
		this->head = this->head->next;
		this->size--;
		delete current;
	}
	else{
		Node* previous = this->head;
		Node* current = this->head->next;
		while(current != NULL) {
			if(current->value == value) {
				break;
			}
			else {
				previous = current;
				current = current->next;
			}
		}
		if(current == NULL) {
			previous = NULL;
			delete current;
			delete previous;
			return;
		}
		else{
			previous->next = current->next;
			this->size--;
			previous = NULL;
			delete previous;
			delete current;
		}
	}
}