#include "Particle.hpp"

Particle::Particle(string name):Ship{}{
	this->id = "particle";
	this->type = name;
	if(name == "explosion1"){
		this->nbFrames = 16;
	}
	else if(name == "atkUp"){
		this->nbFrames = 15;
	}
	else if(name == "smoke"){
		this->nbFrames = 7;
	}
	else if(name == "healing"){
		this->nbFrames = 10;
	}
	this->frame = 0;
}
Particle::Particle(string name, int x, int y):Ship{}{
	this->id = "particle";
	this->type = name;
	if(name == "explosion1"){
		this->nbFrames = 16;
	} else if(name == "atkUp"){
		this->nbFrames = 15;
	}
	else if(name == "smoke"){
		this->nbFrames = 7;
	}
	else if(name == "healing"){
		this->nbFrames = 10;
	}
	this->coo.x = x;
	this->coo.y = y;
	this->frame = 0;
}

Particle::Particle(string name, int x, int y, int w, int h):Ship{}{
	this->id = "particle";
	this->type = name;
	if(name == "explosion1"){
		this->nbFrames = 16;
	}
	else if(name == "atkUp"){
		this->nbFrames = 15;
	}
	else if(name == "smoke"){
		this->nbFrames = 7;
	}
	else if(name == "healing"){
		this->nbFrames = 10;
	}
	this->coo.x = x;
	this->coo.y = y;
	this->coo.w = w;
	this->coo.h = h;
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
