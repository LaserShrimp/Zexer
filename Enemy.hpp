#ifndef __ENEMY_HPP__
#define __ENEMY_HPP__
#include "Ship.hpp"

#include "defines.h"

class Enemy : public Ship {
	private:
		
	public:
		Enemy(SDL_Texture *t);
		Enemy();
		
		virtual void move();
		virtual void rerack();
		virtual void takeDamage(int damage);
		
		virtual ~Enemy();
};

#endif