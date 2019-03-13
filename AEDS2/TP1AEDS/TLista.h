#ifndef TLista_h
#define TLista_h

typedef struct TLista TLista;
typedef struct TCelula TCelula;
typedef struct TVetor TVetor;

struct TCelula {
	unsigned id;
	TCelula* anterior;
	TCelula* proxima;
	TLista* respostas;
TLista* atual;
};

struct TLista {
	TCelula* primeira;
	TCelula* ultima;
};

struct TVetor {
	int array[1000];
	int tamanho;
};

TCelula * Adiciona(TLista * lista, int id0);

TCelula * Responde(TLista * lista, int idExistente, int idNovo);
void Remove(TCelula * celula);
TCelula * EncontraComentario(TLista * lista, int id);
// TCelula * EncontraAnterior(TLista * lista, int id);
TVetor * ImprimeLista(TLista * lista, TVetor * vetor);

#endif
