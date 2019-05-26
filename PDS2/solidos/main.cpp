#include <iostream>
#include "Solid.hpp"

int main(){
	std::string line;
	double radius = 0;
	double height = 0;
	double base = 0;
	while(std::cin>>line){
		Solid *s = NULL;
		if(line == "CY"){
			std::cin>>radius>>height;
			s = new Cylinder(radius, height, base, "Cylinder");
		}
		else if(line == "SP"){
			std::cin>>radius;
			s = new Sphere(radius, height, base, "Sphere");
		}
		else if(line == "CB"){
			std::cin>>base;
			s = new Cube(radius, height, base, "Cube");
		}
		else{
			s = new Solid(radius, height, base, "Unknown Solid");
		}
		std::cout<<s->getType()<<", Area: "<<s->getArea()<<", Volume: "<<s->getVolume()<<std::endl;
	}
	return 0;
}
