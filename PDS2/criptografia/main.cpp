#include <iostream>
#include <string>
#include "Encoder.hpp"
#include "Decoder.hpp"

int main(){
	std::string line, key;
	//std::cin.ignore(); // ATENCAO: ESSA LINHA NAO ESTA COMENTADA NA VPL. FOI NECESSARIA A ADICAO DELA POR PROBLEMAS DE BUFFER NA VPL.
	std::getline(std::cin, key);
	std::getline(std::cin, line);
	Encoder::Enc *enc = new Encoder::Enc(key);
	Decoder::Dec *dec = new Decoder::Dec(enc);
	enc->EncodeMessage(line);
	dec->DecodeMessage(Encoder::getMessage());
	Encoder::print();
	Decoder::print();
	delete enc;
	delete dec;
	return 0;
}