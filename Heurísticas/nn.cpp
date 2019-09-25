#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
int cost = 0;

float EucDis(float* city_x, float* city_y, int begin, int cur, string type){
	float x = city_x[begin] - city_x[cur];
	float y = city_y[begin] - city_y[cur];
	if(type == "EUC_2D") return pow((pow(x,2) + pow(y,2)),0.5);
	else return pow(((x*x + y*y)/10),0.5);
}

void EucNN(float* city_x, float* city_y, int a, int b, int dimension, bool* done, string type){
	int dif, nn = -1, begin = a, cur = b, min = 9999999;
	for (int i = 0; i < dimension; ++i)
		if(!done[i]) dif = EucDis(city_x, city_y, cur, i, type), if(dif < min) min = dif, nn = i;
	if(nn < 0) cost += EucDis(city_x, city_y, begin, cur, type);
	else cost += min, done[nn] = true, EucNN(city_x, city_y, begin, nn, dimension, done, type);
}

int main(int argc, char const *argv[]){
	
	ifstream file;
	file.open(argv[1]);
	string name, type, temp; int dimension;

	file >> temp >> temp; if(temp == ":") file >> name; else name = temp;
	while(temp[0] != 'D') file >> temp;
	file >> temp; if(temp == ":") file >> dimension; else dimension = stoi(temp);
	file >> temp >> temp; if(temp == ":") file >> type; else type = temp;
	file >> temp;

	int id; float city_x[dimension], city_y[dimension];
	for (int i = 0; i < dimension; ++i){
		file >> id >> city_x[i] >> city_y[i]; // reads coordinates
		if(i == 0) cout << id << " " << city_x[i] << " " << city_y[i] << " " << endl;
	}

	bool done[dimension];
	int min_cost = 999999999;

	for (int i = 0; i < dimension; ++i){
		for (int j = 0; j < dimension; ++j) done[j] = false;
		done[i] = true,	cost = 0;
		EucNN(city_x, city_y, i, i, dimension, done, type);
		if(cost < min_cost) min_cost = cost;
	}

	cout << "Best cost: " << min_cost << endl;

	return 0;
}
