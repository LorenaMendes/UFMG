#include <iostream>
#include <string>
#include "jogos.hpp"
using namespace std;

jogo::jogo(string nome){
	this->nome = nome;
}

void jogo::imprimeCaracteristicas(){
	if(this->get_habilidade().length()) cout << "Habilidade " << this->get_habilidade() << endl;
	if(this->get_perspectiva().length()) cout << "Perspectiva " << this->get_perspectiva() << endl;
	if(this->get_geracao_procedural().length()) cout << "GeracaoProcedural " << this->get_geracao_procedural() << endl;
	if(this->get_online().length()) cout << "Online " << this->get_online() << endl;
	if(this->get_role_play().length()) cout << "RolePlay " << this->get_role_play() << endl;
	if(this->get_tempo_real().length()) cout << "TempoReal " << this->get_tempo_real() << endl;
	if(this->get_simulacao().length()) cout << "Simulacao " << this->get_simulacao() << endl;
}

jogoAction::jogoAction(string nome) : jogo(nome){
	this->set_nome(nome);
	this->set_habilidade("HabilidadeMotora");
	this->set_tempo_real("Sim");
}

void jogoAction::imprimeCaracteristicas(){
	cout << "Habilidade " << this->get_habilidade() << endl;
	cout << "TempoReal " << this->get_tempo_real() << endl;
}

jogoFPS::jogoFPS(string nome) : jogoAction(nome){
	this->set_nome(nome);
	this->set_perspectiva("Primeira");
	this->set_tempo_real("Sim");
}

void jogoFPS::imprimeCaracteristicas(){
	cout << "Habilidade (de FPS) " << this->get_habilidade() << endl;
	cout << "Perspectiva (de FPS) " << this->get_perspectiva() << endl;
	cout << "TempoReal (de FPS) " << this->get_tempo_real() << endl;
}

jogoPlatform::jogoPlatform(string nome) : jogoAction(nome){
	this->set_nome(nome);
	this->set_perspectiva("Terceira");
	this->set_tempo_real("Sim");
}

void jogoPlatform::imprimeCaracteristicas(){
	cout << "Habilidade (de plataform) " << this->get_habilidade() << endl;
	cout << "Perspectiva (de plataform) " << this->get_perspectiva() << endl;
	cout << "TempoReal (de plataform) " << this->get_tempo_real() << endl;
}

jogoRPG::jogoRPG(string nome) : jogo(nome){
	this->set_nome(nome);
	this->set_role_play("Sim");
}

void jogoRPG::imprimeCaracteristicas(){
	cout << "RolePlay " << this->get_role_play() << endl;
}

jogoMMORPG::jogoMMORPG(string nome) : jogoRPG(nome){
	this->set_online("Sim");
	this->set_role_play("Sim");
	this->set_tempo_real("Sim");
}

void jogoMMORPG::imprimeCaracteristicas(){
	cout << "Online " << this->get_online() << endl;
	cout << this->get_role_play() << endl;
	cout << "TempoReal " << this->get_tempo_real() << endl;
}

jogoRoguelike::jogoRoguelike(string nome) : jogoRPG(nome){
	this->set_geracao_procedural("Sim");
	this->set_role_play("Sim");
	this->set_tempo_real("Nao");
}

void jogoRoguelike::imprimeCaracteristicas(){
	cout << "GeracaoProcedural (de roguelike) " << this->get_geracao_procedural() << endl;
	cout << "RolePlay (de roguelike) " << this->get_role_play() << endl;
	cout << "TempoReal (de roguelike) " << this->get_tempo_real() << endl;
}

jogoRTS::jogoRTS(string nome) : jogo(nome){
	this->set_nome(nome);
	this->set_habilidade("RaciocinioLogico");
	this->set_tempo_real("Sim");
}

void jogoRTS::imprimeCaracteristicas(){
	cout << "Habilidade " << this->get_habilidade() << endl;
	cout << "TempoReal " << this->get_tempo_real() << endl;
}

jogoSports::jogoSports(string nome) : jogo(nome){
	this->set_nome(nome);
	this->set_habilidade("HabilidadeMotora");
	this->set_simulacao("Sim");
}

void jogoSports::imprimeCaracteristicas(){
	cout << "Habilidade " << this->get_habilidade() << endl;
	cout << "Simulacao " << this->get_simulacao() << endl;
}