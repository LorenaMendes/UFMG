#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DEBUG 0

int main() {
	//int DEBUG = 0;

	// If received a NOT NULL parameter,
	// Then activates DEBUG MODE 
	// And keep printing what is going on
	//if(argc>1) DEBUG = atoi(argv[1]);

	char buf[(1024*1024)];
	const char s[2] = " ";
	char *token;
	int i, j;

	// If there are lines remaining on the input,
	// Gets TestCase's header line from input
	while (fgets( buf, (1024*1024), stdin )) {

		// Tokenize it, convert it to integer, 
		// creates array for storing the samples

		int N = atoi(strtok(buf, s));
		int L = atoi(strtok(NULL, s));
		int C = atoi(strtok(NULL, s));

		if(DEBUG) printf("\nP: %d\tL: %d\tC: %d\n",N,L,C);

		int c_cur = 0;
		int l_cur = 1;
		int p_cur = 1;
		int length;

		// Gets TestCase's payload line from input 
		fgets( buf, (1024*1024), stdin );

		if(DEBUG) printf("%s",buf);		

		// Iterates through the payload line tokenizing 
		// the samples and converting them to integer
		
		for(i=0;i<N;i++) {
			// if first iterations, starts tokenizer 
			// and also starts doubly linked list
			if(i==0) token = strtok(buf, s);
			// otherwise, just continues tokenizer
			else token = strtok(NULL, s);

			if(DEBUG) printf("\titerando %s... ",token);

			length=0;
			//count length of string
			for(j=0;token[j]!='\0' && token[j]!='\n';j++) {
				length++;
			}
			if(DEBUG) printf("%d chars.\n",length);

			//if it still fits the current line, count it there.
			if((c_cur+length) <= C) c_cur+=(length+1);
			//otherwise, break the line and count on the following.
			//and don't forget accounting the space after the word.
			//the space must be taken into account, in case some other word
			//is to be added.
			else {
				if(DEBUG) printf("%s nao cabe. Quebrei linha.\n",token);
				c_cur = (length+1);
				//if line still fits the current page, add it.
				//and don't forget accounting the space after the word.
				//the space must be taken into account, in case some other word
				//is to be added.
				if((l_cur+1) <= L) l_cur++;
				//otherwise, increment the current page
				else {
					if(DEBUG) printf("Quebrei pagina.\n");
					p_cur++;
					l_cur=1;
				}
			}
		}
		// if on debug mode, iterates the array 
		// printing the collected values
		if(DEBUG != 0) printf("line: %d, chars: %d, page: ",l_cur,c_cur);

		// And print the number of pages
		printf("%d\n",p_cur);
	}

}
