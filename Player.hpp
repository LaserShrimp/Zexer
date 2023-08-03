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
		
		Animation animRight;
		Animation animLeft;
		Animation animUp;
		Animation animDown;
		
	protected:
	public:
		Player();
		Player(const Player& p);
		
		int getNbAmmo() const;
		int getStackSize() const;
		Uint32 getShootCooldown() const;
		Uint32 getStartShootCooldown() const;
		Missile* getMissile(int index);
		vector<Missile*>& getAmmo();
		
		void setMissileTexture(int missileId, const Animation& a);
		void setAmmo(vector<Missile*> &mVector);
		void setNbAmmo(int n);
		void setStackSize(int stackSize);
		void setMoveState(const InputState &is);
		void setShootCooldown(Uint32 cooldown);
		void setStartShootCooldown();
		void setAnimationNeutral(SDL_Renderer *r);
		void setAnimationUp(SDL_Renderer *r);
		void setAnimationDown(SDL_Renderer *r);
		void setAnimationLeft(SDL_Renderer *r);
		void setAnimationRight(SDL_Renderer *r);
		void doActions(const InputState &is);
		void init(int x, int y, int speed, int ammo, int stackSize);
		virtual void init();
		void init(SDL_Texture *missileTexture);
		void init(SDL_Renderer *r);
		
		void shoot();
		void move();
		void updateAmmos();
		virtual void renderShip(SDL_Renderer *r);
		int missileCollidesWith(SDL_Rect target);
		void restackMissile(int index);
		void damageMissile(int index, int damage);
		virtual bool takeDamage(int d);
		
		void changeAlpha(int alpha);
		void resetAlpha();
		
		virtual ~Player();
};

ostream& operator<<(ostream& out, Player &p);

#endif
