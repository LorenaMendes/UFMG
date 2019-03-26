#include <iostream>
#include <string>
#include <sstream>
#include <map>

int main(){

	std::map<std::string, int> m;
		std::string word;
		// std::cout << word << " ";
		// std::cout << word.size() << std::endl;

	while (std::cin >> word){
		// if(m[word]) std::cout << "tem\n";
		// else{
			// std::cout << "não tem\n";
		// if (!m[word]) std::cout << "Não existe\n";
		m.insert(std::pair<std::string, int>(word, word.size()));
		// }
		if (m[word]) std::cout << "Existe\n";
	}
	std::cout << "\n";
	std::map<std::string, int>::iterator it;
	for (it = m.begin(); it != m.end(); it++) {
		std::cout << it->first << ": " << it->second << std::endl;
	}

	return 0;
}