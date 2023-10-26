#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include <vector>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Ship.hpp"
#include "Missile.hpp"
#include "InputState.hpp"
#include "Item.hpp"

typedef enum movestate{
	RIGHT, UPRIGHT, DOWNRIGHT, LEFT, UPLEFT, DOWNLEFT, UP, DOWN, STATIONNARY
}movestate;

class Player: public Ship{
	private:
		movestate mvState;
		Uint32 shootCooldown; //in milliseconds
		Uint32 startShootCooldown; //in millis
		bool launchMissile;
		
	protected:
	public:
		Player();
		Player(const Player& p);
		
		movestate getMvState() const;
		Uint32 getShootCooldown() const;
		Uint32 getStartShootCooldown() const;
		bool isShooting() const;
		
		void setMoveState(const InputState &is);
		void setShootCooldown(Uint32 cooldown);
		void setStartShootCooldown();
		void setLaunchingState(bool a);
		void doActions(const InputState &is, vector<Ship*> &v);
		virtual void init(int x, int y, int speed, int ammo, int stackSize);
		virtual void init();
		
		void shoot(vector<Ship*> &v);
		void move();
		bool gatherItem(Item& i);
		virtual bool takeDamage(int d);
		
		virtual ~Player();
};

ostream& operator<<(ostream& out, Player &p);

#endif
