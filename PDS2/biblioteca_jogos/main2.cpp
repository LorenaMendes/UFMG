#include "jogos.hpp"

using namespace std;

int main(int argc, char** argv) {

	jogo * game1;
	jogo * game2;
	game1 = new jogoRTS("Starcraft");
	game1->imprimeNome();
	game1->imprimeCaracteristicas();

	game2 = new jogoSports("Fifa");
	// game2->imprimeNome();
	game2->imprimeCaracteristicas();

	return 0;
}
/*
Starcraft
RTS
AgeOfEmpires
RTS
Fifa
Sports
DragonQuest
RPG
DanceDanceRevolution
Action

Starcraft
Habilidade RaciocinioLogico
Perspectiva
GeracaoProcedural Sim
Online Sim
RolePlay Sim
TempoReal Sim
Simulacao Sim
AgeOfEmpires
Habilidade RaciocinioLogico
Perspectiva
GeracaoProcedural Sim
Online Sim
RolePlay Sim
TempoReal Sim
Simulacao Sim
Fifa
Habilidade HabilidadeMotora
Perspectiva
GeracaoProcedural Sim
Online Sim
RolePlay Sim
TempoReal Sim
Simulacao Sim
DragonQuest
Habilidade
Perspectiva
GeracaoProcedural Sim
Online Sim
RolePlay Sim
TempoReal Sim
Simulacao Sim
DanceDanceRevolution
Habilidade HabilidadeMotora
Perspectiva
GeracaoProcedural Sim
Online Sim
RolePlay Sim
TempoReal Sim
Simulacao Sim
*/