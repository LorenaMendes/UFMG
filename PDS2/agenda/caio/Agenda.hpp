using namespace std;

struct Compromisso{
	int hora;
	string descricao;
	struct Compromisso * prox;

	Compromisso(int, string);
};

struct Dia{
	int id;
	struct Compromisso * compromisso;
	
	Dia(int _id);
	~Dia();
};

struct Mes{
	string nome;
	int num_dias;
	struct Mes * prox;
	struct Dia ** dias;

	Mes(string, int);
	~Mes();
};

struct Agenda{
	int ano;
	bool bissexto;
	Mes * meses;

	Agenda(int);
	~Agenda();
	void insereMes(string, int);
	bool anoBis(int ano);
	bool insereCompromisso(string, int, int, string);
	bool verificaCompromisso(string, int, int);
	void listaTodosOsCompromissos();
	void removeCompromisso(string, int, int);
	void fechaAgenda();
	void abreAgenda();
	bool VerificaDados(string _mes, int _dia, int _hora);
};