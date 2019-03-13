#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	char buff[1000];
	char *line1, *line2, *line3;
	int num;
	while (fgets( buff, 1000, stdin )){
		fgets( line1, 10, stdin );
		fgets( line2, 4, stdin );
		fgets( line3, 50, stdin );
	}
	num = atoi(line2);
	printf("Num: %d\n", num);
	printf("%s\n", line1);
	printf("%s\n", line3);
}