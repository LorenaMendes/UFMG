#include<iostream>
#include<string>
#include "Decoder.hpp"
#include "Encoder.hpp"
using namespace std;

namespace Decoder{
	
	string decoded = "";

	Dec::Dec(Encoder::Enc* ptr){
		this->ptr = ptr;
	}

	int Dec::findPosition(char c){
		int position = -1;
		for (int i = 0; i < 36; ++i) if(this->ptr->key[i] == c) position = i;
		return position;
	}

	void Dec::DecodeMessage(string message){
		int position;
		for (int i = 0; i < int(message.length()); ++i){
			position = this->findPosition(message[i]);
			decoded += position == -1 ? message[i] : this->ptr->original[position];
		}
	}

	void print(){
		cout << "Decoded message: " << decoded << endl;
	}

	string getMessage(){
		return decoded;
	}	
}
