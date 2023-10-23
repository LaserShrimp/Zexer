#include "Particle.hpp"

Particle::Particle(string name):Ship{}{
	this->id = "particle";
	this->type = name;
	if(name == "explosion1"){
		this->nbFrames = 16;
	}
	this->frame = 0;
}
Particle::Particle(string name, int x, int y):Ship{}{
	this->id = "particle";
	this->type = name;
	if(name == "explosion1"){
		this->nbFrames = 16;
	}
	this->coo.x = x;
	this->coo.y = y;
	this->frame = 0;
}

int Particle::getNbFrames(){
	return this->nbFrames;
}

string Particle::getType(){
	return this->type;
}

Particle::~Particle(){
	
}
