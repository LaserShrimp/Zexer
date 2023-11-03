#ifndef __PARTICLE_HPP__
#define __PARTICLE_HPP__

#include "Ship.hpp"

class Particle:public Ship{
private:
	string type;
	int nbFrames;
protected:
public:
	Particle(string name);
	Particle(string name, int x, int y);
	Particle(string name, int x, int y, int w, int h);
	
	void initFramesNameId(string name);
	
	int getNbFrames();
	string getType();
	
	~Particle();
};

#endif
