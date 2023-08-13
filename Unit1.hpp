#ifndef __UNIT1_HPP__
#define __UNIT1_HPP__

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "defines.h"
#include "Enemy.hpp"

class Unit1:public Enemy{
private:
	int shootCooldown;//In frames
	int shCurr;
	int moveCooldown;//In frames
	int mCurr;
	int staticCooldown;//In frames
	int stCurr;
protected:
public:
	Unit1();
	
	void init(SDL_Renderer *r);
	void move();
	
	void randomDir();
	
	virtual ~Unit1();
};

#endif
