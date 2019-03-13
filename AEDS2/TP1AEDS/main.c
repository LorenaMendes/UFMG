#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "TLista.h"

#define DEBUG 0

 //ordena o vetor de comentários e o imprime no arquivo
 void Ordena(FILE * output, TVetor * vetor) {
 	if (vetor->tamanho == 0) {
 		printf("-\n");
 		fprintf(output, "-\n");
 		return;
 	}
 	int i, j, tmp;
 	for (i = 0; i < vetor->tamanho; i++) {
 		
		if(vetor->array[i] == 0){
			fprintf(output, " ");
			printf(" "); 
		} else {
			fprintf(output, "%d ", vetor->array[i]);
			printf("%d ", vetor->array[i]);
		}
 	}
 	printf(" - ");
 	fprintf(output, " - ");
 	for (i = 1; i < vetor->tamanho; i++)
 	{
 		tmp = vetor->array[i];
 		for (j = i - 1; j >= 0 && tmp < vetor->array[j]; j--)
 			vetor->array[j + 1] = vetor->array[j];
 		vetor->array[j + 1] = tmp;
 	}
 	for (i = 0; i < vetor->tamanho; i++) {
 		printf("%d ", vetor->array[i]);
 		fprintf(output, "%d ", vetor->array[i]);
 	}
 	printf("\n");
 	fprintf(output, "\n");
 }

 void processaComando(FILE * file, FILE * output) {

 	FILE *temp;
 	// Variaveis auxiliares para conversao de String para Inteiro (funcao atoi) durante o processamento do arquivo de entrada.
 	char idNovoAdd[100], idNovoRes[100], idExistente[100], c;
 	int id_int_Novo, id_int_Existente, posicao = 0, i;

 	TLista * post;
 	post = malloc(sizeof(TLista));
 	post->primeira = NULL;
 	post->ultima = NULL;

 	while (c != EOF)
 	{
 		c = getc(file);
printf("%c", c);
 		switch (c) {

 		case 'A':
 			temp = file;
 			c = getc(temp);
 			do {
 				idNovoAdd[posicao] = c;
 				posicao++;
 				c = getc(temp);
 				if (DEBUG == 2) printf("IdNovo: %s\n", idNovoAdd);
 			} while (c >= 48 && c <= 57);
 			idNovoAdd[posicao] = '\0';
 			if (DEBUG == 2) printf("IdNovoAdd final: %s\n", idNovoAdd);
 			posicao = 0;
 			id_int_Novo = atoi(idNovoAdd);
 			fseek(file, -1, SEEK_CUR);
 			if (DEBUG) printf("[DEBUG] Adiciona, %d\n", id_int_Novo);
printf("%d\n", id_int_Novo);
 			Adiciona(post, id_int_Novo);
 			for (i = 0; idNovoAdd[i] != '\0'; i++) idNovoAdd[i] = '\0';
 			break;

 		case 'R':
 			temp = file;
 			c = getc(temp);
 			do {
 				idExistente[posicao] = c;
 				posicao++;
 				c = getc(temp);
 				if (DEBUG == 2) printf("IdExistente: %s\n", idExistente);
 			} while (c >= 48 && c <= 57);
 			idExistente[posicao] = '\0';
 			posicao = 0;
 			if (c == 44) {
 				c = getc(temp);
 				do {
 					idNovoRes[posicao] = c;
 					posicao++;
 					c = getc(temp);
 					if (DEBUG == 2) printf("IdNovoRes: %s\n", idExistente);
 				} while (c >= 48 && c <= 57);
 				id_int_Novo = atoi(idNovoRes);
 				idNovoRes[posicao] = '\0';
 				posicao = 0;
 			}
 			id_int_Existente = atoi(idExistente);
 			fseek(file, -1, SEEK_CUR);
 			if (DEBUG) printf("[DEBUG] Responde %d em %d\n", id_int_Novo, id_int_Existente);
 			Responde(post, id_int_Existente, id_int_Novo);
 			//for (i = 0; idExistente[i] != '\0'; i++) idExistente[i] = '\0';
 			for (i = 0; idNovoRes[i] != '\0'; i++) idNovoRes[i] = '\0';
 			break;

 		case 'D':
 			temp = file;
 			c = getc(temp);
 			do {
 				idNovoAdd[posicao] = c;
 				posicao++;
 				c = getc(temp);
 				if (DEBUG == 2) printf("IdNovo: %s\n", idNovoAdd);
 			} while (c >= 48 && c <= 57);
 			idNovoAdd[posicao] = '\0';
 			if (DEBUG == 2) printf("IdNovoAdd final: %s\n", idNovoAdd);
 			posicao = 0;
 			id_int_Novo = atoi(idNovoAdd);
 			fseek(file, -1, SEEK_CUR);
 			if (DEBUG) printf("[DEBUG] Remove, %d\n", id_int_Novo);
 			Remove(EncontraComentario(post, id_int_Novo));
 			for (i = 0; idNovoAdd[i] != '\0'; i++) idNovoAdd[i] = '\0';
 			break;
 		case '\n':
 			if (DEBUG) printf("[DEBUG] LINEBREAK.\n");
 			TLista * temp = post;
 			TVetor * vetor;
 			vetor = malloc(sizeof(vetor));
 			vetor->tamanho = 0;
 			Ordena(output, ImprimeLista(temp, vetor));
 			printf("\n");
 			post->primeira = NULL;
 			post->ultima = NULL;
 			break;
 		case EOF:
 			printf("Fim do arquivo\n");
 			break;
 		default:
 			if (DEBUG) printf("[DEBUG] Caractere invalido: %c\n", c);
 			break;
 		}
 	}
 	printf("Parei de ler o arquivo\n");
 	fclose(output);
 	return;
 }

int main(int argc, char *argv[]) {
/*	TLista * lista;
	lista = malloc(sizeof(TLista));
	TVetor * vetor;
	vetor = malloc(sizeof(TVetor));
	vetor->tamanho = 0;
	TCelula * bla;
	bla = malloc(sizeof(TCelula));

	TCelula * ble;
	ble = malloc(sizeof(TCelula));

	Adiciona(lista, 1);
	// vetor->array[vetor->tamanho] = bla->id;
	// vetor->tamanho ++;
	Responde(lista, 1, 14);
	// vetor->array[vetor->tamanho] = ble->id;
	// vetor->tamanho ++;
	// ImprimeLista(lista, vetor);
	Adiciona(lista, 2);
	Responde(lista, 2, 9);
	Responde(lista, 9, 77);
	bla = Responde(lista, 9, 78);
	Responde(lista, 9, 79);
	Responde(lista, 2, 4);
	ble = Adiciona(lista, 3);
	Adiciona(lista, 67);
	Adiciona(lista, 69);
	Responde(lista, 4, 8);
	Responde(lista, 8, 16);
	Responde(lista, 12, 16);
	printf("%d\n", bla->proxima->id);
	printf("%d\n", bla->anterior->id);
	printf("%d\n", ble->proxima->id);
	printf("%d\n", ble->anterior->id);

	Responde(lista, 16, 29);
	Remove(EncontraComentario(lista, 3));
	printf("imprimindo a lista\n");
	// printf("antes de apagar o 3\n");
	// printf("anterior ao %d: %d\n", bla->id, bla->anterior->id);
	// printf("seguinte ao %d: %d\n", bla->id, bla->proxima->id);
	// printf("anterior ao %d: %d\n", ble->id, ble->anterior->id);
	// printf("seguinte ao %d: %d\n", ble->id, ble->proxima->id);
	printf("deletando 9\n");
	if (EncontraComentario(lista, 2) == NULL) printf("não tem mais o 77\n");
	// printf("\ndepois de apagar o 3\n");
	// printf("anterior ao %d: %d\n", bla->id, bla->anterior->id);
	// printf("seguinte ao %d: %d\n", bla->id, bla->proxima->id);
	// printf("anterior ao %d: %d\n", ble->id, ble->anterior->id);
	// printf("seguinte ao %d: %d\n", ble->id, ble->proxima->id);
	// printf("to aqui\n");
	// printf("anterior ao %d: %d\n", bla->id, bla->anterior->id);
	// printf("anterior ao %d: %d\n", ble->id, ble->anterior->id);
	// printf("seguinte ao %d: %d\n", ble->id, ble->proxima->id);
	ImprimeLista(lista, vetor);
	printf("\n\n");
*/

 printf("Argumentos: %d.\n------------------\n", argc);
 for (int i = 0; i < argc; i++) printf("Argumento %d: %s\n", i, argv[i]);
 printf("\n");
 if (argc != 3) {
 	printf("ERRO DE INPUT!\nDigite o nome do arquivo de entrada e o nome do arquivo de saída!\n");
 	return 0;
 }

 if (DEBUG) printf("[DEBUG] Comecei.\n");
 FILE *file;
 file = fopen(argv[1], "r");
 if (file == NULL) {
 	printf("Erro ao abrir o arquivo de entrada.\n");
 	return 0;
 }

 FILE *output;
 output = fopen(argv[2], "w");
 if (output == NULL) {
 	printf("Erro ao abrir o arquivo de saida.\n");
 	return 0;
 }
 if (DEBUG) printf("[DEBUG] Abri o arquivo\n");
 if (file) {
 	if (DEBUG) printf("[DEBUG] Processando arquivo...\n");
 	processaComando(file, output);
 	if (DEBUG) printf("[DEBUG] Processei.\n");
 	fclose(file);
 }

	return 0;
}
