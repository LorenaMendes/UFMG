#ifndef HOUSES_H
#define HOUSES_H

#include<iostream>
#include<string>

using namespace std;

class greatHouse {
  protected:
    string name;

  public:
	void Words();
	void Allegiance();
	void setName(string n);
};

class houseLannister {
  public:  	
	void Words(bool common);
	void Common();	
};

class houseBaratheon {
  public:  	
	void Words();	
};


class houseBaratheonofKingsLanding : public houseBaratheon, public houseLannister{
	using houseBaratheon::Words;
	using houseLannister::Words;
};

#endif