#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include <vector>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Ship.hpp"
#include "Missile.hpp"

class Player: public Ship{
	private:
		int nbAmmo;
		int stackSize;
		vector<Missile> ammo;
	protected:
	public:
		Player(SDL_Texture *t);
		
		int getNbAmmo();
		int getStackSize();
		Missile& getMissile(int index);
		vector<Missile>& getAmmo();
		
		void setMissileTexture(int missileId, SDL_Texture *t);
		void setAmmo(vector<Missile> &mVector);
		void setNbAmmo(int n);
		void setStackSize(int stackSize);
		void init(int x, int y, int speed, int ammo, int stackSize);
		virtual void init();
		void init(SDL_Texture *missileTexture);
		
		void shoot();
		void updateAmmos();
		virtual void renderShip(SDL_Renderer *r);
		int missileCollidesWith(SDL_Rect target);
		void restackMissile(int index);
		void damageMissile(int index, int damage);
		virtual void takeDamage(int d);
		
		~Player();
};

ostream& operator<<(ostream& out, Player &p);

#endif
