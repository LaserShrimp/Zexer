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
#include "Item.hpp"
#include "Particle.hpp"

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
	virtual void doActions(vector<Ship*>& v, Ship& p);
	virtual void doActions(vector<Ship*>& v, vector<Item*>& vi, vector<Particle*>& vp, Ship& p);
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
	virtual void doActions(vector<Ship*>& v, Ship& p);
	virtual void doActions(vector<Ship*>& v, vector<Item*>& vi, vector<Particle*>& vp, Ship& p);
	virtual void shoot(vector<Ship*>& v);
	virtual ~UnitOmni();
};

class UnitTracker: public Enemy{
private:
protected:
public:
	UnitTracker();
	virtual void init();
	virtual void move(Vect& target);
	virtual void doActions(vector<Ship*>& v, Ship& p);
	virtual void doActions(vector<Ship*>& v, vector<Item*>& vi, vector<Particle*>& vp, Ship& p);
	virtual ~UnitTracker();
};

class UnitDestroyer: public Enemy{
private:
	int landmark; // to set where the destroyer will shoot from
	int shootCooldown;//In frames
	int shCurr;
protected:
public:
	UnitDestroyer();
	virtual void init();
	virtual void move(Vect& target);
	virtual void doActions(vector<Ship*>& v, Ship& p);
	virtual void doActions(vector<Ship*>& v, vector<Item*>& vi, vector<Particle*>& vp, Ship& p);
	virtual void shoot(vector<Ship*>& v);
	virtual ~UnitDestroyer();
};

#endif
