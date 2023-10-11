#ifndef __ENEMY_HPP__
#define __ENEMY_HPP__

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "defines.h"
#include "gameAddOns.h"
#include "Ship.hpp"

class Enemy : public Ship {
private:
	public:
		Enemy();
		Enemy(const Enemy& e);
		
// 		virtual void setAnimationNeutral(SDL_Renderer *r);
// 		virtual void setAnimationNeutral(SDL_Renderer *r, char* animName, int nbFrames, int frameW, int frameH);
		virtual void init(/*SDL_Renderer *r*/);
		virtual void move();
		virtual void rerack();
		virtual bool takeDamage(int damage);
// 		virtual void renderShip(SDL_Renderer *r) override;
		
		virtual ~Enemy();
};

#endif
