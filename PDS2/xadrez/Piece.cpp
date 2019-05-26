#include "Piece.hpp"
#include <iostream>
#include <vector>
#include <utility>
#include<bits/stdc++.h>
using namespace std;

Piece::Piece(string simbolo, string posAtual, string posCand){
	this->simbolo = simbolo;
	this->posAtual = posAtual;
	this->posCand = posCand;
	this->num_movs = 0;
}

void Piece::setMovements(){
	cout << "Posição atual do Piece:" << this->posAtual << endl;
}

void Piece::setNextPosition(string next){
	this->posCand = next;
}

bool Piece::allowed(pair<char, char> move){
	if(int(move.first) < int('a') || int(move.first) > int('h')) return false;
	else if(int(move.second) < int('1') || int(move.second) > int('8')) return false;
	else return true;
}

bool sortbysec(const pair<char,char> &a, const pair<char,char> &b){ 
    if(a.first < b.first) return (a.second < b.second);
    else return false; 
} 

void Piece::printPossibleMoves(){
	sort(this->movs.begin(), this->movs.end());
	vector<pair<char, char>>::iterator it;
	cout << "(" << this->nome << ") Current position: (" << this->posAtual << ")" << endl;
	cout << "I have " << this->num_movs << " legal movements." << endl;
	for(it=this->movs.begin(); it!=this->movs.end(); it++){
		cout << "(" << this->posAtual << ")" << "->"; 
		cout << "(" << (*it).first << (*it).second << ")" << endl; 
	}
}

void Piece::checkMovement(){
	pair<char, char> cand = make_pair(this->posCand[0],this->posCand[1]);
	vector<pair<char, char>>::iterator it;
	it = find(this->movs.begin(), this->movs.end(), cand);
	if (it != this->movs.end()){
		cout << "Moving from (" << this->posAtual << ") to (" << this->posCand << ")" << endl;
		this->posAtual[0] = cand.first;
		this->posAtual[1] = cand.second;
	} else cout << "I cannot move from (" << this->posAtual << ") to (" << this->posCand << ")" << endl;
	this->num_movs = 0;
	this->movs.clear();
}

Rook::Rook(string simbolo, string posAtual, string posCand) : Piece(simbolo, posAtual, posCand){
	this->nome = "Rook";
	this->simbolo = simbolo;
	this->posAtual = posAtual;
	this->posCand = posCand;
}
Bishop::Bishop(string simbolo, string posAtual, string posCand) : Piece(simbolo, posAtual, posCand){
	this->nome = "Bishop";
	this->simbolo = simbolo;
	this->posAtual = posAtual;
	this->posCand = posCand;
}
Knight::Knight(string simbolo, string posAtual, string posCand) : Piece(simbolo, posAtual, posCand){
	this->nome = "Knight";
	this->simbolo = simbolo;
	this->posAtual = posAtual;
	this->posCand = posCand;
}

void Rook::setMovements(){
	pair<char, char> original = make_pair(this->posAtual[0],this->posAtual[1]);
	pair<char, char> move = original;

	for (int i = 1; i < 8; ++i){
		move.first = char(int(original.first) + i);
		move.second = original.second;
		if(allowed(move)) {this->movs.push_back(move); this->num_movs++;}

		move.first = char(int(original.first) - i);
		move.second = original.second;
		if(allowed(move)) {this->movs.push_back(move); this->num_movs++;}

		move.first = original.first;
		move.second = char(int(original.second) + i);
		if(allowed(move)) {this->movs.push_back(move); this->num_movs++;}

		move.first = original.first;
		move.second = char(int(original.second) - i);
		if(allowed(move)) {this->movs.push_back(move); this->num_movs++;}
	}
}

void Bishop::setMovements(){
	pair<char, char> original = make_pair(this->posAtual[0],this->posAtual[1]);
	pair<char, char> move = original;

	for (int i = 1; i < 8; ++i){
		move.first = char(int(original.first) + i);
		move.second = char(int(original.second) + i);
		if(allowed(move)) {this->movs.push_back(move); this->num_movs++;}

		move.first = char(int(original.first) - i);
		move.second = char(int(original.second) - i);
		if(allowed(move)) {this->movs.push_back(move); this->num_movs++;}

		move.first = char(int(original.first) + i);
		move.second = char(int(original.second) - i);
		if(allowed(move)) {this->movs.push_back(move); this->num_movs++;}

		move.first = char(int(original.first) - i);
		move.second = char(int(original.second) + i);
		if(allowed(move)) {this->movs.push_back(move); this->num_movs++;}
	}
}

void Knight::setMovements(){
	pair<char, char> original = make_pair(this->posAtual[0],this->posAtual[1]);
	pair<char, char> move = original;

	move.first = char(int(original.first) + 2);
	move.second = char(int(original.second) + 1);
	if(allowed(move)) {this->movs.push_back(move); this->num_movs++;}

	move.first = char(int(original.first) + 2);
	move.second = char(int(original.second) - 1);
	if(allowed(move)) {this->movs.push_back(move); this->num_movs++;}

	move.first = char(int(original.first) - 2);
	move.second = char(int(original.second) + 1);
	if(allowed(move)) {this->movs.push_back(move); this->num_movs++;}

	move.first = char(int(original.first) - 2);
	move.second = char(int(original.second) - 1);
	if(allowed(move)) {this->movs.push_back(move); this->num_movs++;}

	move.second = char(int(original.second) + 2);
	move.first = char(int(original.first) + 1);
	if(allowed(move)) {this->movs.push_back(move); this->num_movs++;}

	move.second = char(int(original.second) + 2);
	move.first = char(int(original.first) - 1);
	if(allowed(move)) {this->movs.push_back(move); this->num_movs++;}

	move.second = char(int(original.second) - 2);
	move.first = char(int(original.first) + 1);
	if(allowed(move)) {this->movs.push_back(move); this->num_movs++;}

	move.second = char(int(original.second) - 2);
	move.first = char(int(original.first) - 1);
	if(allowed(move)) {this->movs.push_back(move); this->num_movs++;}
}
