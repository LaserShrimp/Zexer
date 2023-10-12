#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include <vector>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Ship.hpp"
#include "Missile.hpp"
#include "InputState.hpp"

typedef enum movestate{
	RIGHT, UPRIGHT, DOWNRIGHT, LEFT, UPLEFT, DOWNLEFT, UP, DOWN, STATIONNARY
}movestate;

class Player: public Ship{
	private:
		int nbAmmo;
		int stackSize;
		vector<Missile*> ammo;
		movestate mvState;
		Uint32 shootCooldown; //in milliseconds
		Uint32 startShootCooldown; //in millis
		bool launchMissile;
		
	protected:
	public:
		Player();
		Player(const Player& p);
		
		int getNbAmmo() const;
		int getStackSize() const;
		movestate getMvState() const;
		Uint32 getShootCooldown() const;
		Uint32 getStartShootCooldown() const;
		Missile* getMissile(int index);
		vector<Missile*>& getAmmo();
		bool isShooting() const;
		
		void setAmmo(vector<Missile*> &mVector);
		void setNbAmmo(int n);
		void setStackSize(int stackSize);
		void setMoveState(const InputState &is);
		void setShootCooldown(Uint32 cooldown);
		void setStartShootCooldown();
		void setLaunchingState(bool a);
		void doActions(const InputState &is);
		virtual void init(int x, int y, int speed, int ammo, int stackSize);
		virtual void init();
		
		void shoot();
		void move();
		void updateAmmos();
		int missileCollidesWith(SDL_Rect target);
		void restackMissile(int index);
		void damageMissile(int index, int damage);
		virtual bool takeDamage(int d);
		
		virtual ~Player();
};

ostream& operator<<(ostream& out, Player &p);

#endif
