#include <iostream>
#include <string>
#include "Encoder.hpp"
using namespace std;

namespace Encoder{
	
	string encoded = "";

	Enc::Enc(string key){
		this->key = key;
		this->original = "abcdefghijklmnopqrstuvwxyz0123456789";
	}

	int Enc::findPosition(char c){
		int position = -1;
		for (int i = 0; i < 36; ++i) if(this->original[i] == c) position = i;
		return position;
	}

	void Enc::EncodeMessage(string message){

		int position;
		for (int i = 0; i < int(message.length()); ++i){
			position = this->findPosition(message[i]);
			encoded += position == -1 ? message[i] : this->key[position];
		}
	}

	void print(){
		cout << "Encoded message: " << encoded << endl;
	}

	string getMessage(){
		return encoded;
	}
}