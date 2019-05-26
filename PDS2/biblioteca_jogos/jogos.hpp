#ifndef JOGO_H
#define JOGO_H
#include <iostream>
#include <string>
using namespace std;

class jogo{
public:
	string nome, habilidade, perspectiva;
	string geracao_procedural, online, role_play, tempo_real, simulacao;
	
	jogo(string);

	virtual string get_nome(){return this->nome;}
	virtual string get_habilidade(){return this->habilidade;}
	virtual string get_perspectiva(){return this->perspectiva;}
	virtual string get_geracao_procedural(){return this->geracao_procedural;}
	virtual string get_online(){return this->online;}
	virtual string get_role_play(){return this->role_play;}
	virtual string get_tempo_real(){return this->tempo_real;}
	virtual string get_simulacao(){return this->simulacao;}

	virtual void imprimeNome(){cout << this->nome << endl;}
	void imprimeCaracteristicas();
};

class jogoAction : public jogo{
public:
	jogoAction(string);
	void set_nome(string nome) {this->nome = nome;}
	void set_habilidade(string habilidade) {this->habilidade = habilidade;}
	void set_tempo_real(string tempo_real) {this->tempo_real = tempo_real;}
	void imprimeCaracteristicas();
};

class jogoFPS : public jogoAction{
public:
	jogoFPS(string);
	void set_nome(string nome) {this->nome = nome;}
	void set_perspectiva(string perspectiva) {this->perspectiva = perspectiva;}
	void set_tempo_real(string tempo_real) {this->tempo_real = tempo_real;}
	void imprimeCaracteristicas();
};

class jogoPlatform : public jogoAction{
public:
	jogoPlatform(string);
	void set_nome(string nome) {this->nome = nome;}
	void set_perspectiva(string perspectiva) {this->perspectiva = perspectiva;}
	void set_tempo_real(string tempo_real) {this->tempo_real = tempo_real;}
	void imprimeCaracteristicas();
};

class jogoRPG : public jogo{
public:
	jogoRPG(string);
	void set_nome(string nome) {this->nome = nome;}
	void set_role_play(string role_play) {this->role_play = role_play;}
	void imprimeCaracteristicas();
};

class jogoMMORPG : public jogoRPG{
public:
	jogoMMORPG(string);
	void set_nome(string nome) {this->nome = nome;}
	void set_online(string online) {this->online = online;}
	void set_role_play(string role_play) {this->role_play = role_play;}
	void set_tempo_real(string tempo_real) {this->tempo_real = tempo_real;}
	void imprimeCaracteristicas();
};

class jogoRoguelike : public jogoRPG{
public:
	jogoRoguelike(string);
	void set_nome(string nome) {this->nome = nome;}
	void set_geracao_procedural(string geracao_procedural) {this->geracao_procedural = geracao_procedural;}
	void set_role_play(string role_play) {this->role_play = role_play;}
	void set_tempo_real(string tempo_real) {this->tempo_real = tempo_real;}
	void imprimeCaracteristicas();
};

class jogoRTS : public jogo{
public:
	jogoRTS(string);
	void set_nome(string nome) {this->nome = nome;}
	void set_habilidade(string habilidade) {this->habilidade = habilidade;}
	void set_tempo_real(string tempo_real) {this->tempo_real = tempo_real;}
	void imprimeCaracteristicas();
};

class jogoSports : public jogo{
public:
	jogoSports(string);
	void set_nome(string nome) {this->nome = nome;}
	void set_habilidade(string habilidade) {this->habilidade = habilidade;}
	void set_simulacao(string simulacao) {this->simulacao = simulacao;}
	void imprimeCaracteristicas();
};

#endif