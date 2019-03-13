#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printLine(char * line){
	int i;
	for (i=0; line[i] != 0 && line[i] != 10; i++)
		printf("%c", line[i]);
	printf("\n");
}

void stateMachine(int position, char * line, char * lineRes){
	int i;
	//case in which we are seeing the first position
	//uppercasing the fist letter 
	if(position == 0){
		if(line[position] > 96) lineRes[position] = line[position] - 32;
		else lineRes[position] = line[position];
		return;
	}

	for(i=position-1; i>=0; i--){
		//lowercase letter?
		if(lineRes[i] > 96){
			if(line[position] > 96) lineRes[position] = line[position] - 32;
			else lineRes[position] = line[position];
			return;
		}
		//uppercase letter?
		if(lineRes[i] < 91 && lineRes[i] > 64){
			if(line[position] > 96) lineRes[position] = line[position];
			else lineRes[position] = line[position] + 32;
			return;
		}
	}
	//I didn't find any letter, only spaces
	//First letter's case
	// printf("cheguei no caso da primeira letra\n");
	if(line[position] > 96) lineRes[position] = line[position] - 32;
	else lineRes[position] = line[position];
	return;
}

int main(){
	char line[51], lineRes[51];
	int i;
	while(fgets(line, 51, stdin)){
		//It isn't a '\n' neither a '\0'
		for(i=0; line[i] != 0; i++){
			if(line[i] == '\n'){
				lineRes[i] = '\0';
				continue;
			}
			if(line[i] == ' ') lineRes[i] = ' ';
			else stateMachine(i, line, lineRes);
		}
		printLine(lineRes);
	}
	return 0;
}