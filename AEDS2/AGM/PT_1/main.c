#include <stdio.h>
#include <stdlib.h>
#include "conexao.h"
#define DEBUG 0

int main(int argc, char const *argv[]){	
	
	//lê o arquivo de entrada passado por parâmetro
	FILE * arq_in = fopen(argv[1], "r");
	
	//caso de erro no arquivo
	if(!arq_in){
		printf("Erro na leitura do arquivo de entrada\n");
		return 0;
	}

	//lê o arquivo de entrada passado por parâmetro
	FILE * arq_out = fopen(argv[2], "w");
	
	//caso de erro no arquivo
	if(!arq_out){
		printf("Erro na leitura do arquivo de saída\n");
		return 0;
	}

	//crio as variáveis
	int v1, v2, peso;
	int vertices, arestas;

	//leio números de vértices e arestas
	fscanf(arq_in, "%d %d", &vertices, &arestas);

	//crio um vetor de arestas
	Aresta * vetor_inicial = (Aresta*)malloc(arestas*sizeof(Aresta));

	//leio os vértices e pesos de cada uma e adiciono ao vetor
	for (int i = 0; i < arestas; ++i){
		fscanf(arq_in, "%d %d %d", &v1, &v2, &peso);
		vetor_inicial[i].v1 = v1;
		vetor_inicial[i].v2 = v2;
		vetor_inicial[i].peso = peso;
	}

	//ordeno as arestas por seus respectivos pesos
	qsort(vetor_inicial, arestas, sizeof(Aresta), Compara);
	
	if(DEBUG) ImprimeArestas(vetor_inicial, arestas);

	//cria uma lista de adjacência com todos os vértices
	Vertice * lista_adj = NovaLista(vertices);

	//insere os vértices na lista de adjacência
	for (int i = 0; i < arestas; ++i) Insere(lista_adj, vetor_inicial[i]);
	// ImprimeAdj(lista_adj, vertices);

	//crio uma lista de adjacências para a AGM
	Vertice * AGM = NovaLista(vertices);
	if(DEBUG) printf("\n");

	int contador = 0;
	for (int i = 0; i < arestas; ++i){
		if(!Pesquisa(AGM, vetor_inicial[i].v1, vetor_inicial[i].v2, arestas)){
			contador ++;
			Insere(AGM, vetor_inicial[i]);
		}
	}
	if(DEBUG) printf("Árvore Geradora Mínima:\n");
	if(DEBUG) ImprimeAdj(AGM, vertices);
	if(DEBUG) printf("Contador: %d\n", contador);

	Aresta * vetor_agm = GeraVetorAgm(AGM, vertices, vetor_agm, contador);
	DefinePeso(vetor_inicial, arestas, vetor_agm, contador);

	if(DEBUG) printf("\nArestas da Arvore: ");
	if(DEBUG) ImprimeArestas(vetor_agm, contador);

	OrdenaVertices(vetor_agm, contador);

	if(DEBUG) printf("\nOrdenado por vertices: ");
	if(DEBUG) ImprimeArestas(vetor_agm, contador);

	fprintf(arq_out, "%d %d\n", vertices, contador);
	for (int i = 0; i < contador; ++i){
		fprintf(arq_out, "%d %d %d\n", vetor_agm[i].v1, vetor_agm[i].v2, vetor_agm[i].peso);
	}

	//fecha os arquivos
	fclose(arq_out);
	fclose(arq_in);
	//libera as alocações
	free(vetor_inicial);
	// free(lista_adj);
	return 0;
}
