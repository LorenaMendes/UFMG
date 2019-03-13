#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 1 // Setar DEBUG = 0 para desativar mensagens de debug.

//Cada lutador possui esses atributos.
struct Lutador{
	char nome[100];
	char pais[20];
	char categoria[100];
	int idade;
	char sexo[10];
	float altura;
	float peso;
	int vitorias;
	int derrotas;
	int empates;
};

int menu(char opc){
	//Exibe o menu de opcoes.
	printf("\n******** Menu *******\n");
	printf("1)  Cadastrar lutador\n");
	printf("2)   Exibir lutadores\n");
	printf("3)     Apagar lutador\n");
	printf("4)         Gerar luta\n");
	printf("5)               Sair\n");
	printf("*********************\n");
	//Le a opcao selecionada.
	printf("Escolha o que deseja fazer e aperte enter: ");
	scanf(" %c",&opc);
	return opc;
}

void gerarLuta(struct Lutador *lutador, int n1, int n2){
	int result;
	if(DEBUG) printf("[DEBUG] Gerando um valor aleatorio de 0 a 2... \n");
	result = rand() % 3;
	switch(result){
		case 0:
			lutador[n1].vitorias++;
			lutador[n2].derrotas++;
			printf("\n******************\nVITORIA DE %s!\n******************\n",lutador[n1].nome);
			break;
		case 1:
			lutador[n2].vitorias++;
			lutador[n1].derrotas++;
			printf("\n******************\nVITORIA DE %s!\n******************\n",lutador[n2].nome);
			break;
		case 2:
			lutador[n1].empates++;
			lutador[n2].empates++;
			printf("\n***************\nEMPATOU!\n***************\n");
			break;
	}
	if(DEBUG) printf("[DEBUG] Luta gerada. \n");
}


void marcarLuta(struct Lutador *lutador, int n, int i){
	if(DEBUG) printf("[DEBUG] Marcando luta... \n");
	char lut1[100], lut2[100];
	int n1=-1, n2=-1;
	printf("\nDigite o nome do primeiro lutador: ");
	scanf("%s",&lut1[0]);
	printf("Digite o nome do segundo lutador: ");
	scanf("%s",&lut2[0]);
	if(DEBUG) printf("[DEBUG] Tentando descobrir se a luta está sendo feita entre dois lutadores iguais... \n");
	if(strcmp(lut1,lut2)==0){
		printf("Está tentando fazer uma luta entre %s e ele(a) mesmo(a)?!\n",lut1);
		return;
	}
	if(DEBUG) printf("[DEBUG] Beleza, são diferentes. \n");
	if(DEBUG) printf("[DEBUG] Iterando para achar primeiro lutador... \n");
	for(i=0; i<n; i++){
		if(strcmp(lutador[i].nome, lut1) == 0){
			n1=i;
			if(DEBUG) printf("[DEBUG] Achei o primeiro lutador! \n");
		}
	}
	if(DEBUG) printf("[DEBUG] Iterando para achar o segundo lutador... \n");
	for(i=0; i<n; i++){
		if(strcmp(lutador[i].nome, lut2) == 0){
			n2=i;
			if(DEBUG) printf("[DEBUG] Achei o segundo lutador! \n");
		}
	}
	if(n1==-1) printf("\nPrimeiro lutador nao existe! Escolha a opção 1 do menu para cadastrá-lo(a).\n");	
	if (n2==-1) printf("\nSegundo lutador nao existe! Escolha a opção 1 do menu para cadastrá-lo(a).\n");
	else {
		if(strcmp(lutador[n1].sexo,lutador[n2].sexo)!=0)
			printf("\n*************************************\nOS LUTADORES DEVEM SER DO MESMO SEXO!\n*************************************\n");
		else if(strcmp(lutador[n1].categoria,lutador[n2].categoria)!=0)
			printf("\n******************************************\nOS LUTADORES DEVEM SER DA MESMA CATEGORIA!\n******************************************\n");
		else {
			if(DEBUG) printf("[DEBUG] OK. Gerando luta... \n");
			gerarLuta(lutador, n1, n2);
			}
	}
}

void apagarLutador(struct Lutador *lutador, int *n, int i){
	//Apaga um Lutador
			if(DEBUG) printf("[DEBUG] Iniciando apagarLutador com n=%d e i=%d.\n",*n,i);
			char nome[100];
			int j, cont=-1;
			printf("\nDigite o nome do lutador a ser excluido: ");
			scanf("%s",&nome[0]);
			if(DEBUG) printf("[DEBUG] Procurando %s.\n",nome);
			for(i=0; i<*n; i++){
				if(DEBUG && strcmp(lutador[i].nome, nome)!=0) printf("[DEBUG] Ainda nao...\n");
				if (strcmp(lutador[i].nome, nome)==0){
					if(DEBUG) printf("[DEBUG] Achei o lutador. Agora vou dar shift em todo mundo daqui pra frente.\n");
					for(j=i+1; j<*n; j++){
						if(DEBUG) printf("[DEBUG] Fazendo shift em %s.\n",lutador[j].nome);
						strcpy(lutador[j-1].nome,lutador[j].nome);
						strcpy(lutador[j-1].pais,lutador[j].pais);
						lutador[j-1].idade=lutador[j].idade;
						strcpy(lutador[j-1].sexo,lutador[j].sexo);
						lutador[j-1].altura=lutador[j].altura;
						lutador[j-1].peso=lutador[j].peso;
						lutador[j-1].vitorias=lutador[j].vitorias;
						lutador[j-1].derrotas=lutador[j].derrotas;
						lutador[j-1].empates=lutador[j].empates;
					}
					if(DEBUG) printf("[DEBUG] Terminei os shifts.\n");
					(*n)--;
					i=*n;
					cont=j;
				}
			}
			if(cont==-1) printf("\n***ATENCAO!*** Lutador '%s' nao existe. Verifique se digitou o nome corretamente,\nconsiderando letras maiusculas e minusculas.\n",nome);
			else printf("\nLutador '%s' deletado com sucesso! \n%d lutadores remanescentes.\n", nome, *n);
}

void exibirLutadores(struct Lutador *lutador, int n, int i){
	if(DEBUG) printf("[DEBUG] Exibindo lutadores... \n");
	if(n==0){ printf("Não há lutadores a serem exibidos.\n"); return;}
	for(i=0; i<n; i++){
		printf("\n*** Lutador %d ***\n",i+1);
		printf("Nome: %s\n",lutador[i].nome);
		printf("Pais: %s\n",lutador[i].pais);
		printf("Idade: %d\n",lutador[i].idade);
		printf("Sexo: %s\n",lutador[i].sexo);
		printf("Altura: %.1f\n",lutador[i].altura);
		printf("Peso: %.1f\n",lutador[i].peso);
		printf("Categoria: %s\n",lutador[i].categoria);
		printf("Vitorias: %d\n",lutador[i].vitorias);
		printf("Derrotas: %d\n",lutador[i].derrotas);
		printf("Empates: %d\n",lutador[i].empates);
	}
	if(DEBUG) printf("[DEBUG] Terminei de exibir lutadores. \n");
}

void definirCategoria(struct Lutador *lutador, int n, float peso, char *sexo){
	if(DEBUG) printf("[DEBUG] Definindo categoria deste lutador... \n");
	if(strcmp(lutador[n].sexo,"feminino") == 0){
		if(DEBUG) printf("[DEBUG] Sexo feminino. Checando peso... \n");
		if(lutador[n].peso < 50) strcpy(lutador[n].categoria,"Feminino leve");
		else if(lutador[n].peso < 70) strcpy(lutador[n].categoria,"Feminino medio");
		else strcpy(lutador[n].categoria,"Feminino pesado");
	} else if(strcmp(lutador[n].sexo,"masculino") == 0){
		if(DEBUG) printf("[DEBUG] Sexo masculino. Checando peso... \n");
		if(lutador[n].peso < 60) strcpy(lutador[n].categoria,"Masculino leve");
		else if(lutador[n].peso < 80) strcpy(lutador[n].categoria,"Masculino medio");
		else strcpy(lutador[n].categoria,"Masculino pesado");
	} else {
		strcpy(lutador[n].categoria,"Sem categoria!");
		if(DEBUG) printf("[DEBUG] Sexo nao reconhecido. \n");
		}
	if(DEBUG) printf("[DEBUG] Ok. Ja categorizei. \n");
}

void cadastrarLutador(struct Lutador *lutador, int *n, int *cap){
	if(DEBUG) printf("[DEBUG] Checando se ha capacidade para insercao de lutador... \n");
	if((*n)==(*cap)){
		if(DEBUG) printf("[DEBUG] Capacidade esgotada, devemos aumentar o vetor usando \"realloc\" (ex: dobrar capacidade).\n");
		(*cap) *= 2;
		lutador = realloc(lutador, sizeof(struct Lutador)*(*cap));
	}
	if(DEBUG) printf("[DEBUG] Ainda cabe lutador no vetor. \n");
	if(DEBUG) printf("[DEBUG] Iniciando entrada de dados... \n");
	char nome[100];
	int i, j, cont=-1;
	printf("\nDigite o nome: ");
	scanf("%s",&nome[0]);
	if(DEBUG) printf("[DEBUG] Tentando descobrir se o lutador já está cadastrado... %s.\n",nome);
	for(i=0; i<*n; i++){
		if(DEBUG && strcmp(lutador[i].nome, nome)!=0) printf("[DEBUG] Ainda nao...\n");
		if (strcmp(lutador[i].nome, nome)==0){
			if(DEBUG) printf("[DEBUG] Achei um lutador com esse nome! Nao vai dar para cadastrar...\n");
				printf("\nJá existe um lutador com esse nome! Impossível cadastrar.\n");
				return;
		}
			
	}
	if(DEBUG) printf("[DEBUG] Não encontrei outro lutador com esse nome. Pode continuar o cadastro de %s sem problemas.\n",nome);
	strcpy(lutador[*n].nome,nome);
	printf("->Digite o pais: ");
	scanf(" %[^\n]",lutador[*n].pais);
	printf("->Digite a idade: ");
	scanf("%d",&lutador[*n].idade);
	if(DEBUG) printf("[DEBUG] Checando se o lutador tem idade permitida para o cadastro...\n");
		
	if(lutador[*n].idade < 18){
		if(DEBUG) printf("[DEBUG] Tentou cadastrar uma criança!\n");
		printf("\nNão é permitido o cadastro de pessoas com menos de 18 anos!\n");
		return;
	}
	if(lutador[*n].idade > 100){
		if(DEBUG) printf("[DEBUG] Tentou cadastrar um(a) idoso(a)!\n");
		printf("\nNão é permitido o cadastro de pessoas com mais de 100 anos, sinto muito!\n");
		return;
	}
	if(DEBUG) printf("[DEBUG] Ok. Idade permitida.\n");
	
	do{	
		printf("->Digite o sexo (feminino/masculino): ");
		scanf(" %[^\n]",lutador[*n].sexo);
		if(DEBUG) printf("[DEBUG] Checando se digitou um sexo válido...\n");
		if((strcmp(lutador[*n].sexo,"feminino")!=0) && (strcmp(lutador[*n].sexo,"masculino")!=0)){
			printf("\nSexo inválido! Deve ser feminino ou masculino. Preste atenção nas letras maiúsculas e minúsculas ao digitar.\n\n");
		}
	}while((strcmp(lutador[*n].sexo,"feminino")!=0) && (strcmp(lutador[*n].sexo,"masculino")!=0));

	if(DEBUG) printf("[DEBUG] Ok. está válido.\n");
	do{
		printf("->Digite a altura: ");
		scanf("%f",&lutador[*n].altura);
		if(DEBUG) printf("[DEBUG] Checando se a altura é válida...\n");
		if((lutador[*n].altura < 1) || (lutador[*n].altura > 2.7)){
			printf("\nDigite uma altura válida!\n");
		}
	}while((lutador[*n].altura < 1) || (lutador[*n].altura > 2.7));
	if(DEBUG) printf("[DEBUG] Ok. Pode prosseguir.\n");
	do{
		printf("->Digite o peso: ");
		scanf("%f",&lutador[*n].peso);
		if(DEBUG) printf("[DEBUG] Checando se o peso é válido...\n");
		if((lutador[*n].peso < 20) || (lutador[*n].peso > 130)){
			printf("\nEsse peso não é permitido para o cadastro! Insira um peso válido!\n\n");
		}
	}while((lutador[*n].peso < 20) || (lutador[*n].peso > 130));
	if(DEBUG) printf("[DEBUG] Ok. Peso válido.\n");
	definirCategoria(lutador, *n, lutador[*n].peso, lutador[*n].sexo);
	lutador[*n].vitorias=0;
	lutador[*n].derrotas=0;
	lutador[*n].empates=0;
	if(DEBUG) printf("[DEBUG] Incrementando o numero de registros cadastrados...\n");
	(*n)++;
	printf("Cadatro de %s realizado com sucesso!\n", nome);

}


int main(){
	if(DEBUG) printf("[DEBUG] AVISO!!\n");
	if(DEBUG) printf("[DEBUG] Programa sendo executado em modo DEBUG.\n");
	if(DEBUG) printf("[DEBUG] Para desativa-lo, sete a flag DEBUG=0 e compile novamente.\n");
	//Ponteiro para estrutura. Vai ser o vetor de 
	//estruturas dinamicas com os dados da lutador.
	struct Lutador *lutador;
	int cap; //Capacidade do vetor (tamanho real do vetor).
	int n;   //Numero de Lutadores cadastrados (tamanho usado).
	char opc; //Opcao do menu selecionada.
	int i;
	FILE *fp;

	//Abrindo arquivo em modo de leitura ("r" = read).
	fp = fopen("lutador.dat","r");

	//Se retorna NULL eh pq nao encontrou o arquivo.
	//Isso acontece na primeira vez que rodamos o programa.
	if(fp==NULL){
		n = 0;    //Base de dados inicialmente vazia.
		cap = 20; //Fixamos uma capacidade inicial (ex: 20).

		//Alocammos o vetor de estruturas de forma
		//dinamica conforme a capacidade.
		lutador = (struct Lutador *)malloc(sizeof(struct Lutador)*cap);
	} else{ //Arquivo encontrado, logo procedemos com a leitura.

		//Le o numero de registros.
		fread(&n, sizeof(int), 1, fp);
	    
	    	//A capacidade deve ser maior ou igual a "n" (ex: n*2).
		cap = n*2; 

		//Alocammos o vetor de estruturas de forma
		//dinamica conforme a capacidade.
		lutador = (struct Lutador *)malloc(sizeof(struct Lutador)*cap);
	
		//Leitura dos dados dos registros do arquivo para o vetor.
		fread(lutador, sizeof(struct Lutador), n, fp);
	
		//Fecha arquivo apos leitura.
		fclose(fp);
	}
	do{
		opc = menu(opc);
		if(opc=='1'){
			//Solicita informacoes do usuario e cadastra novo lutador.
			cadastrarLutador(lutador,&n,&cap);
		} else if(opc=='2'){
			//Exibe todos Lutadores cadastrados.
			exibirLutadores(lutador,n,i);
		} else if(opc=='3'){
			//Solicita um nome de lutador para o usuario e apaga
			apagarLutador(lutador,&n,i);
		} else if (opc=='4'){
			//Marca uma luta e define vencedor aleatoriamente.
			marcarLuta(lutador,n, i);
		} else if (opc!='5') // Checa se eh pra sair. Se nao for, da erro e volta porque a opcao eh invalida.
			printf("A opcao %c nao eh valida. Favor digitar um numero entre 1 e 5.",opc);

		//Enquanto nao for opcao de saida continua mostrando menu.
	}while(opc!='5'); 

	if(n>0){
		//Se existe algum Lutador cadastrado 
		//entao grava para o disco.
	
		//Abre arquivo em modo de gravacao ("w" = write).
		fp = fopen("lutador.dat","w");

		//Grava o numero de Lutadores no inicio do arquivo.
		fwrite(&n, sizeof(int), 1, fp);
		    
		//Grava os dados do vetor no arquivo.
		fwrite(lutador, sizeof(struct Lutador), n, fp);
		    
	
		//Fecha arquivo apos a gravacao.
		fclose(fp);
	}

	//Libera a memoria alocada do vetor.
	free(lutador);
  
	return 0;
}
