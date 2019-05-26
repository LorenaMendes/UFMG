#include "Piece.hpp"
#include <map>
#include <iostream>

int main(){
	std::string symbol, curPos, nextPos;
	std::map<std::string, Piece*> pieces;
	 
	while(std::cin>>symbol){
		Piece *P = NULL;
		if (symbol != "N" && symbol != "B" && symbol != "R"){ 
			break;
		}
		if (pieces.find(symbol) != pieces.end()){
			P = pieces[symbol];
			std::cin>>nextPos;
			P->setNextPosition(nextPos);
		}
		else{
			std::cin>>curPos>>nextPos;
			if (symbol == "N"){
				P = new Knight("N",curPos,nextPos);
			}
			else if(symbol == "B"){
				P = new Bishop("B",curPos,nextPos);
			}
			else if(symbol == "R"){
				P = new Rook("R",curPos,nextPos);
			}
			pieces[symbol] = P;
		}
		P->setMovements();
		P->printPossibleMoves();
		P->checkMovement();
	}
	for (auto it=pieces.begin(); it!=pieces.end(); ++it){
		pieces.erase(it);
	}
	return 0;
}