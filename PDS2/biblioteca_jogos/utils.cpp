#include "utils.hpp"

void utils::adicionaJogo(vector<jogo>* v, string nome, string genero)
{	
	map<string,int> genCode;
        
    genCode["Action"] = 1;
    genCode["FPS"] = 2;
    genCode["Platform"] = 3;
    genCode["RPG"] = 4;
    genCode["MMORPG"] = 5;
    genCode["Roguelike"] = 6;
    genCode["RTS"] = 7;
    genCode["Sports"] = 8;
    
    switch(genCode[genero]){
			case 1:	{jogoAction j1(nome);
					v->push_back(j1);
					break;}
			case 2:	{jogoFPS j2(nome);
					v->push_back(j2);
					break;}
			case 3:	{jogoPlatform j3(nome);
					v->push_back(j3);
					break;}
			case 4:	{jogoRPG j4(nome);
					v->push_back(j4);
					break;}
			case 5:	{jogoMMORPG j5(nome);
					v->push_back(j5);
					break;}
			case 6:	{jogoRoguelike j6(nome);
					v->push_back(j6);
					break;}
			case 7:	{jogoRTS j7(nome);
					v->push_back(j7);
					break;}
			case 8:	{jogoSports j8(nome);
					v->push_back(j8);
					break;}
		}			
}