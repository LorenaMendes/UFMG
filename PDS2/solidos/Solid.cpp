#include "Solid.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

Solid::Solid(double radius, double height, double base, string type){
	this->radius = radius;
	this->height = height;
	this->base = base;
	this->type = type;
}

Cylinder::Cylinder(double radius, double height, double base, string type):Solid(radius, height, base, type){
	this->radius = radius;
	this->height = height;
	this->base = base;
	this->type = type;
}


double Cylinder::getArea(){
	double areaBase = this->radius * this->radius * this->pi;
	double areaLateral = 2 * this->pi * this->radius * this->height;
	return 2 * areaBase + areaLateral;
}

double Cylinder::getVolume(){
	return this->radius * this->radius * this->pi * this->height;
}

string Cylinder::getType(){
	return this->type;
}

Sphere::Sphere(double radius, double height, double base, string type):Solid(radius, height, base, type){
	this->radius = radius;
	this->height = height;
	this->base = base;
	this->type = type;
}

double Sphere::getArea(){
	return 4 * this->pi * this->radius * this->radius;
}

double Sphere::getVolume(){
	return (4 * this->pi * this->radius * this->radius * this->radius)/3;
}

string Sphere::getType(){
	return this->type;
}

Cube::Cube(double radius, double height, double base, string type):Solid(radius, height, base, type){
	this->radius = radius;
	this->height = height;
	this->base = base;
	this->type = type;
}

double Cube::getArea(){
	cout << fixed << setprecision(2);
	return 6 * this->base * this->base;
}

double Cube::getVolume(){
	return this->base * this->base * this->base;
}

string Cube::getType(){
	return this->type;
}