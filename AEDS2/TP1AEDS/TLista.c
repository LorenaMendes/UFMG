#include <stdlib.h>
#include <stdio.h>

#include "TLista.h"

#define DEBUG 0

TVetor * ImprimeLista(TLista * lista, TVetor * vetor) {
	TCelula * temp;
	temp = malloc(sizeof(TCelula));
	int posicao = 0;
	if (lista != NULL) temp = lista->primeira;
	else {
		printf("Lista nula.");
		return NULL;
	}
	if (lista->primeira == NULL) printf("\n");
	else {
		do {
			//if (temp->id == 0) printf(" ");
			//else printf("%d ", temp->id);
			vetor->array[vetor->tamanho] = temp->id;
			posicao ++;
			vetor->tamanho ++;
			if (temp->respostas != NULL) {
				//printf("{");
				ImprimeLista(temp->respostas, vetor);
				//printf("}");
			}
			temp = temp->proxima;
		} while (temp != NULL);
	}
	return vetor;
}

//Cria e adiciona um comentário ao final de uma lista e retorna o comentário criado
TCelula * Adiciona(TLista * lista, int id) {
	TCelula * novo;
	novo = malloc(sizeof(TCelula));
	novo->id = id;
	novo->proxima = NULL;
	novo->anterior = NULL;
	novo->respostas = NULL;
	novo->atual = lista;
	// printf("ADICIONA: setei novo->id: %d\n", novo->id);

	TCelula * temp = lista->primeira;
	if (temp == NULL) lista->primeira = novo;
	else {
		while (temp->proxima != NULL) temp = temp->proxima;
		temp->proxima = novo;
		novo->anterior = temp;
		printf("TESTE TUNADO %d %d %d\n", novo->id, novo->anterior->id, temp->id);
	}
	return novo;
}

TCelula * Responde(TLista * lista, int idExistente, int idNovo) {
	TCelula * existente = EncontraComentario(lista, idExistente);
	if (existente == NULL) return NULL;
	if (existente->respostas == NULL) {
		TLista * resps;
		resps = malloc(sizeof(TLista));
		resps->primeira = NULL;
		resps->ultima = NULL;
		existente->respostas = resps;
	}
	return Adiciona(existente->respostas, idNovo);
}

//retorna a célula de um comentário a partir de um id em uma lista
TCelula * EncontraComentario(TLista * lista, int id) {
	TCelula * temp;
	temp = malloc(sizeof(TCelula));
	if (lista != NULL) temp = lista->primeira;
	else {
		printf("Lista nula.");
		return NULL;
	}
	if (lista->primeira == NULL) return NULL;
	else {
		do {
			if (temp->id == id)	return temp;
			if (temp->respostas != NULL) {
				TCelula * temporaria = EncontraComentario(temp->respostas, id);
				if (temporaria != NULL) {
					return temporaria;
				}
			}
			temp = temp->proxima;
		} while (temp != NULL);
	}
	return NULL;
}

void Remove(TCelula * existente) {
	if (existente == NULL) {
		// printf("Não tem\n");
		return;
	}

	if (existente->proxima != NULL) {
		printf("Essa é a primeira\n");
		
		existente->proxima->anterior = existente->anterior;

	}

	
	if (existente->anterior != NULL) {

		existente->anterior->proxima = existente->proxima;
printf("DEBUG A");
	}

	if (existente == existente->atual->primeira) existente->atual->primeira = existente->proxima;
  if(existente->respostas != NULL && existente->respostas->primeira != NULL) {
printf("REMOVENDO SUBFEED");
 	TCelula * temp;
 	do {
 		temp = existente->respostas->primeira->proxima;
 		Remove(existente->respostas->primeira);
 		existente->respostas->primeira = temp;
 		temp = temp->proxima;
 	} while (temp->proxima != NULL);

 	Remove(temp);
	free(existente->respostas);

 }
free(existente);
}
