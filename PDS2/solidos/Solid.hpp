#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <iostream>
using namespace std;

class Solid{
	public:
		double radius, height, base;
		string type;
		const double pi = 3.14; //Nao modifique este valor.
		
		Solid(double, double, double, string);
		
		virtual double getArea(){return 0};
		virtual double getVolume(){return 0};
		virtual string getType(){return "Unknown Solid"};
};

class Cylinder : public Solid{
	public:
		Cylinder(double, double, double, string);
		double getArea() override;
		double getVolume() override;
		string getType() override;
};

class Sphere : public Solid{
	public:
		Sphere(double, double, double, string);
		double getArea() override;
		double getVolume() override;
		string getType() override;
};

class Cube : public Solid{
	public:
		Cube(double, double, double, string);
		double getArea() override;
		double getVolume() override;
		string getType() override;
};

#endif