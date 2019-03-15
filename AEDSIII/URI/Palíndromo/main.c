#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	countOdds(int * alphabet){
	int i, counter = 0;
	for (i=0; i<26; i++) if(alphabet[i]%2) counter++;
	return counter;
}


int main(){
	int i, alphabet[26];
	char input[1001];
	while(fgets(input, 1001, stdin)){
		for(i=0; i<26; i++) alphabet[i] = 0;
		for(i=0; input[i] != '\0'; i++) alphabet[input[i]-97]++;
		int odds = countOdds(alphabet);
		if(!odds%2) printf("%d\n", odds);
		else printf("%d\n", odds-1);
	}
}