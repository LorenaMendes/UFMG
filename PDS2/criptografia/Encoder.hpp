#ifndef ENC_H
#define ENC_H
#include <iostream>
#include <string>
using namespace std;

namespace Encoder{
	
	class Enc{
		public:
			string original;
			string key;
			Enc(string key);
			void EncodeMessage(string message);
			int findPosition(char c);
	};
	void print();
	string getMessage();
}

#endif