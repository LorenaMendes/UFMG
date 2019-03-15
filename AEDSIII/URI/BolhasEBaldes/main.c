#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int count = 0;

void intercala (int p, int q, int r, int v[], int tam) {
  int i, j, k;
  int w[tam];
  i = p; 
  j = q;
  k = 0;
  while (i < q && j <= r) {
    if (v[i] <= v[j])  
      w[k++] = v[i++];
    else {
	    w[k++] = v[j++];
	  	count += (q-i);
    }
  }
  while (i < q)  
    w[k++] = v[i++];
  while (j <= r)  
    w[k++] = v[j++];
  for (i = p; i <= r; i++)  
    v[i] = w[i-p];
}

void mergesort (int p, int r, int v[], int tam) {
  if (p < r) {
    int q = (p + r)/2;
    mergesort (p, q, v, tam);
    mergesort (q+1, r, v, tam);
    intercala (p, q+1, r, v, tam);
  }
}

int main(){
	int i, tam;
	while(!feof(stdin)){
		scanf("%d", &tam);
		if(!tam) break;
		int vetor[100000];
		for(i=0; i<tam; i++) scanf(" %d", &vetor[i]);
		mergesort(0, tam-1, vetor, tam);
		// printf("%d\n", count);
		if((!(count%2)) || count == 0) printf("Carlos\n");
		else printf("Marcelo\n");
		count = 0;
	}
	return 0;
}
