#ifndef PIECE_H
#define PIECE_H
using namespace std;
#include <string>
#include <vector>
#include <utility>

class Piece{
	public:
		string simbolo, nome, posAtual, posCand;
		int num_movs;
		vector<pair<char,char>> movs;
		Piece(string, string, string);
		virtual void setMovements();
		bool allowed(pair<char, char>);
		void printPossibleMoves();
		void setNextPosition(string);
		void checkMovement();
};

class Rook : public Piece{
	public:
		Rook(string, string, string);
		void setMovements() override;
};

class Bishop : public Piece{
	public:
		Bishop(string, string, string);
		void setMovements() override;
};

class Knight : public Piece{
	public:
		Knight(string, string, string);
		void setMovements() override;
};

#endif