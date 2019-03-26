#include "List.hpp"

List::List(){
	this->size = 0;
	this->head = NULL;
}

void List::insert(int value){
    Node* node = new Node;
	node->value = value;
	node->next = this->head;
	this->head = node;
	this->size ++;
	node = NULL;
}

void List::clearList() {
	if(this->size == 0) return;
	if(this->size == 1){
		delete this->head;
		this->size = 0;
		return;
	}
	Node* aux;
	while(this->head->next != NULL){
		aux = this->head;
		this->head = this->head->next;
		delete aux;
	}
	aux = NULL;
	delete this->head;
	this->size = 0;
}


void List::print(){
	Node* head = this->head;
	if (this->size > 0){
		while(head){
			std::cout << head->value << " ";
			head = head->next;
		}
		std::cout<<std::endl;
	}
	else{
	    std::cout<<std::endl;
	    head = NULL;
		return;
	}
}

int List::removeFirst(){
	if(this->size == 0) return -1;
	Node* current = this->head;
	this->head = (this->head)->next;
	int aux = current->value; 
	delete current;
	current = NULL;
	this->size --;
	return aux;
}

int List::indexOf(int value){
	Node* head;
	if (this->size > 0){
		head = this->head;
		int index = 0;
		while(head && head->next && head->value != value){
			index++;
			head = head->next;
		}
		if (head->value == value){
			head = NULL;
			return index;
		}
		return -1;
	}
	else{
		head = NULL;
		return -1;
	}
}

void List::remove(int value){
	Node* current;
	Node* previous;
	if(this->size == 0){
		current = NULL;
		return;
	}
	else if(this->head->value == value){
		current = this->head;
		this->head = (this->head)->next;
		delete current;
		current = NULL;
		this->size --;
	}
	else{
		previous = this->head;
		current = (this->head)->next;
		while(current != NULL) {
			if(current->value == value) break;
			else {
				previous = current;
				current = current->next;
			}
		}
		if(current == NULL) {
			previous = NULL;
			return;
		}
		else {
			previous->next = current->next;
			delete current;
			current = NULL;
			previous = NULL;
			this->size --;
		}
	}
}