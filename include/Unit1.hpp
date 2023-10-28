#ifndef __UNIT1_HPP__
#define __UNIT1_HPP__

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "defines.h"
#include "Enemy.hpp"
#include "Ship.hpp"
#include "Missile.hpp"

#define U1_XSPEED		0
#define U1_YSPEED		5
#define U1_LIMIT_MAX	WIN_HEIGHT/3

class Unit1:public Enemy{
private:
	int shootCooldown;//In frames
	int shCurr;
	int moveCooldown;//In frames
	int mCurr;
	int staticCooldown;//In frames
	int stCurr;
	int areaLimit; //the area where it lands before attacking
	bool hasLanded;
protected:
public:
	Unit1();
	
	virtual void init();
	virtual void move();
	virtual void doActions(vector<Ship*>& v);
	virtual void shoot(vector<Ship*>& v);
	
	void randomDir();
	
	virtual ~Unit1();
};

class UnitOmni: public Enemy{
private:
	int shootCooldown;//In frames
	int shCurr;
protected:
public:
	UnitOmni();
	virtual void init();
	virtual void move();
	virtual void doActions(vector<Ship*>& v);
	virtual void shoot(vector<Ship*>& v);
	virtual ~UnitOmni();
};

#endif
