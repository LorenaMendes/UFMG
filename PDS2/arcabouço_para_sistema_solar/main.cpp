#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>
#include "Astro.hpp"
#include "Planeta.hpp"
#include "SistemaSolar.hpp"

using namespace std;

int main() {
	float num_astros = 0;
	float num_planetas = 0;
	float num_luas = 0;
	string fileName, line;
	cin >> fileName;

	ifstream file;
	file.open(fileName);

	SistemaSolar * SS = new SistemaSolar();
	while (getline(file, line)) {
		if (line == "defastro") {
			num_astros++;
			string comando, tipo, nome, temp, raio, grav, orbita;
			bool gas;

			file >> tipo;

			if (tipo == "Lua") {
				num_luas++;
				file >> nome >> comando >> orbita;
			} else file >> nome;

			file >> comando >> temp >> comando >> raio >> comando >> grav >> comando >> comando;
			gas = (comando == "False") ? false : true;

			if (tipo == "Planeta") {
				num_planetas++;
				Planeta* planeta = new Planeta();
				planeta->setNome(nome);
				planeta->setRaio(stof(raio));
				planeta->setTemperatura(stof(temp));
				planeta->setGravidade(stof(grav));
				planeta->setGasoso(gas);
				SS->inserePlaneta(planeta);
			} else {
				Astro* astro = new Astro;
				astro->setNome(nome);
				astro->setRaio(stof(raio));
				astro->setTemperatura(stof(temp));
				astro->setGravidade(stof(grav));
				astro->setGasoso(gas);

				if (tipo == "Lua") (SS->getPlaneta(orbita))->insereLua(astro);
				else SS->insereEstrela(astro);
			}
		}
	}

	Astro * maior = SS->maiorEstrela();
	cout << maior->getNome() << endl;
	cout << maior->getTemperatura() << endl;
	cout << num_astros << endl;
	cout << num_planetas << endl;
	cout << SS->getNumPlanetasSolidos() << endl;
	float m = num_luas / num_planetas;
	m = trunc(m * 100) / 100;
	cout << fixed << setprecision(2) << m << endl;
	cout << (SS->getPlanetaComMaisLuas())->getNome() << endl;
	cout << (SS->getPlanetaMaisQuente())->getNome() << endl;
	cout << (SS->getPlanetaMaisFrio())->getNome() << endl;
	cout << (SS->getPlanetaMaiorRaio())->getNome() << endl;
	cout << (SS->getPlanetaMenorRaio())->getNome() << endl;

	file.close();
	delete(SS);
	return 0;
}