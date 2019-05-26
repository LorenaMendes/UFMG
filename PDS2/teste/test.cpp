#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char const *argv[]){
	if(argc != 3){
		return 0;
	}
	string entrada = argv[1];
	string saida = argv[2];
	cout << saida << endl;
}