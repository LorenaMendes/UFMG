#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void token_recognizer(string word){
	cout << word << endl;
}

// função que separa cada palavra de um arquivo
void word_breaker(string file_name){
	ifstream file;
	file.open(file_name);

	char cur_character;
	char aux_character;
	string word = "";
	int number_of_lines = 0;
	int number_of_words = 0;

	while (!file.eof()) {
		
		cur_character = 0;
		// lê um caractere
		file.get(cur_character);
		
		// caso em que lê um comentário do tipo '//'
		if(word == "/" && cur_character == '/'){
			word = "";
			while(cur_character != '\n')
				file.get(cur_character);
		}

		// caso em que lê um comentário do tipo '/**/'
		if(word == "/" && cur_character == '*'){
			word = "";
			file.get(aux_character);
			while(cur_character != '*' || aux_character != '/'){
				cur_character = aux_character;
				file.get(aux_character);
			} file.get(cur_character);
		}

		// separa a palavra lida se encontrar um espaço
		if (cur_character == ' '){
			if(word.length() > 0){
				++number_of_words;
				token_recognizer(word);
			} word = "";
		} 

		// separa a palavra lida se encontrar uma quebra de linha
		else if (cur_character == '\n'){
			if(word.length() > 0){
				++number_of_lines;
				++number_of_words;
				token_recognizer(word);
			} word = "";
		}

		else word += cur_character;
	}

	token_recognizer(word);
	++number_of_words;
	cout << "NUMBER OF LINES: " << number_of_lines << endl;
	cout << "NUMBER OF WORDS: " << number_of_words << endl;
}

int main(int argc, char const *argv[]){
	string file_name;
	
	if(argc > 1) file_name = argv[1];
	else cin >> file_name;
	
	word_breaker(file_name);

	return 0;
}