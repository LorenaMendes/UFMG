#include <iostream>
#include <string>
#include "Encoder.hpp"

using namespace std;

int main(){
	string line, key;
	getline(cin, key);
	getline(cin, line);
	Encoder::Enc *enc = new Encoder::Enc(key);
	enc->EncodeMessage(line);
	Encoder::print();
	delete enc;
	return 0;
}