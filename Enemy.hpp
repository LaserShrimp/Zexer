#ifndef __ENEMY_HPP__
#define __ENEMY_HPP__

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Ship.hpp"

#include "defines.h"

class Enemy : public Ship {
	private:
		Animation animation;
	public:
		Enemy(SDL_Texture *t);
		Enemy();
		
		void setAnimation(SDL_Renderer *r);
		virtual void init(SDL_Renderer *r);
		virtual void move();
		virtual void rerack();
		virtual bool takeDamage(int damage);
		void renderShip(SDL_Renderer *r);
		
		virtual ~Enemy();
};

#endif
