#ifndef ASTRO_H
#define ASTRO_H
#include <list>
#include <string>

using namespace std;

class Astro {
private:
	string nome;
	float raio;
	float temperatura;
	float gravidade;
	bool gasoso;

public:
	void setNome(string);
	string getNome();
	void setRaio(float);
	float getRaio();
	void setTemperatura(float);
	float getTemperatura();
	void setGravidade(float);
	float getGravidade();
	void setGasoso(bool);
	bool getGasoso();
};

#endif