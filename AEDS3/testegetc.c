#include <stdio.h>
#include <stdlib.h>

void main() {
char palavra[5];
for (int i = 0; i < 5; ++i){
	palavra[i] = '\0';
}
char ch;
        printf("Digite algo.\n");
        system ("/bin/stty raw");
        for (int i = 0; i < 5; ++i){
        	palavra[i] = getchar();
	        printf("-->");
	        printf("%s", palavra);
        }
        system ("/bin/stty cooked");
}