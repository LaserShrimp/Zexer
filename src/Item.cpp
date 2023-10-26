#include "Item.hpp"

Item::Item(string name, int x, int y):Ship{}{
	this->id = "item";
	this->type = name;
	this->nbFrames = 20; //each Item will have 20 frames of animation
	this->coo.x = x;
	this->coo.y = y;
	this->coo.w = 20;
	this->coo.h = 20;
	this->frame = 0;
	this->nbFramesAlive = 7*FPS; //15 seconds
	this->alive = 0;
}
Item::Item(string name, int x, int y, int w, int h):Ship{}{
	this->id = "item";
	this->type = name;
	this->nbFrames = 20; //each Item will have 20 frames
	this->coo.w = 20;
	this->coo.h = 20;
	this->coo.x = x + w/2 - this->coo.w/2;
	this->coo.y = y + h/2 - this->coo.h/2;
	this->frame = 0;
	this->nbFramesAlive = 15*FPS; //15 seconds
	this->alive = 0;
}

int Item::getNbFramesAlive(){
	return this->nbFramesAlive;
}
int Item::getAlive(){
	return this->alive;
}
string Item::getType(){
	return this->type;
}
bool Item::isTimeFinished(){
	return this->alive >= this->nbFramesAlive;
}

void Item::increaseAlive(){
	this->alive++;
}

Item::~Item(){
	
}
