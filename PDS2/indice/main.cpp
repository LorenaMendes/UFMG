#include <iostream>
#include <iomanip>
#include <string>
#include <map>

int main(){

	std::map<std::string, int> mapa;
	std::string word;

	int cont = 0;
	while (std::cin >> word){
		cont ++;
		for(int i=0; i<int(word.size()); i++) word[i] = tolower(word[i]);
		if(word.size() >= 3){
			if(mapa[word]) mapa[word]++;
			else mapa[word] = 1;
		}
	}

	std::cout << std::setiosflags (std::ios::fixed) << std::setprecision(2);
	std::map<std::string, int>::iterator it;

	for (it = mapa.begin(); it != mapa.end(); it++)
		std::cout << it->first << " " << it->second << " " << (it->second/(float)cont) << std::endl;

	return 0;
}