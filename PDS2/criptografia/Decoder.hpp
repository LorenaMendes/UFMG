#ifndef DEC_H
#define DEC_H
#include <iostream>
#include <string>
#include "Encoder.hpp"
using namespace std;

namespace Decoder{
	
	class Dec{
		public:
			Encoder::Enc* ptr;
			string message;
			Dec(Encoder::Enc* ptr);
			void DecodeMessage(string);
			int findPosition(char c);
	};
	void print();
	string getMessage();
}

#endif