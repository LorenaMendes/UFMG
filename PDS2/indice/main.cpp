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
		if(word.size() >= 3){
			if(mapa[word]) mapa[word]++;
			else mapa[word] = 1;
		}
	}

	std::map<std::string, int>::iterator it1;
	std::map<std::string, int>::iterator it2;
	for (it1 = mapa.begin(); it1 != mapa.end(); it1++){
		for (it2 = mapa.begin(); it2 != mapa.end(); it2++){
			if(it1->first.compare(it2->first)) std::cout << "Comparei\n";
		}
	}

	std::cout << std::setiosflags (std::ios::fixed) << std::setprecision(2);
	std::map<std::string, int>::iterator it;

	for (it = mapa.begin(); it != mapa.end(); it++)
		std::cout << it->first << " " << it->second << " " << (it->second/(float)cont) << std::endl;

	return 0;
}