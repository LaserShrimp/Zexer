#ifndef __ITEM_HPP__
#define __ITEM_HPP__

#include <iostream>
#include "Ship.hpp"

class Item: public Ship{
private:
	int nbFramesAlive; //number of frames before it disappears
	int alive; //current time (in frames)
	string type;
	int nbFrames;
protected:
public:
	Item(string name, int x, int y);
	Item(string name, int x, int y, int w, int h);
	
	int getNbFramesAlive();
	int getAlive();
	string getType();
	bool isTimeFinished();
	
	void increaseAlive();
	
	~Item();
};

#endif
