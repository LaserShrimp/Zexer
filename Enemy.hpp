#ifndef __ENEMY_HPP__
#define __ENEMY_HPP__

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Ship.hpp"

#include "defines.h"

class Enemy : public Ship {
	private:
		
	public:
		Enemy(SDL_Texture *t);
		Enemy();
		
		virtual void move();
		virtual void rerack();
		virtual bool takeDamage(int damage);
		
		virtual ~Enemy();
};

#endif
