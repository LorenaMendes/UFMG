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
			// printf("%d ", temp->id);
			vetor->array[vetor->tamanho] = temp->id;
			posicao ++;
			vetor->tamanho ++;
			if (temp->respostas != NULL) {
				// printf("{");
				ImprimeLista(temp->respostas, vetor);
				// printf("}");
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

	if (existente->anterior == NULL && existente->proxima != NULL) {
		// printf("Essa é a primeira\n");
		existente->proxima->anterior = NULL;
	}

	else if (existente->anterior == NULL && existente->proxima == NULL) {
		// printf("Essa é a primeira e a última\n");
	}

	else if (existente->anterior != NULL && existente->proxima == NULL) {
		// printf("Essa é a última\n");
		existente->anterior->proxima = NULL;
	}

	else if (existente->anterior != NULL && existente->proxima != NULL) {
		// printf("Nem primeira nem última\n");
		existente->anterior->proxima = existente->proxima;
		existente->proxima->anterior = existente->anterior;
	}

	if (existente->respostas == NULL) {
		// printf("Não tem respostas, célula deletada\n");
		if (existente->atual->primeira == existente) existente->atual->primeira = existente->proxima;
	} else {
		TCelula * temp;
		do {
			temp = existente->respostas->primeira->proxima;
			Remove(existente->respostas->primeira);
			existente->respostas->primeira = temp;
			temp = temp->proxima;
		} while (temp->proxima != NULL);
		Remove(temp);

	}
	if (existente->atual->primeira == existente) existente->atual->primeira = NULL;
	free(existente);
}
