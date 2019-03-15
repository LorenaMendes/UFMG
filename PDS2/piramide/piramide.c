#include <stdio.h>

void imprime(int x){
	for (int i = 0; i < x; ++i) printf("*");
	printf("\n");
}

int main(){
	int x;
	scanf("%d", &x);
	for (int i = 1; i <= x; ++i) imprime(i);
	for (int i = x-1; i > 0; --i) imprime(i);
	return 0;
}