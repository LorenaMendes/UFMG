typedef int TipoChave;                               
                    
typedef struct Registro {                   
  TipoChave Chave;                                
  /* outros componentes */
} Registro;                                        

typedef struct No *Apontador;        

typedef struct No {
  Registro Reg;
  Apontador Esq, Dir;
} No;

void Inicializa(Apontador *Dicionario);

int Pesquisa(TipoChave Chave, Apontador p);

int Insere(Registro x, Apontador *p);

void Central(Apontador p, void (*visitante)(Apontador p));
