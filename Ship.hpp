#ifndef __SHIP_HPP__
#define __SHIP_HPP__

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "defines.h"
#include "Animation.hpp"

using namespace std;

class Ship{
	protected:
		SDL_Texture *texture;
		SDL_Rect coo;
		SDL_Rect hitbox;
		int speed;
		int health;
		int maxHealth;
		float hitboxRatio; //to set the size of the hitbox (a a percentage of the whole sprite centered in the middle of the ship)
		
		short frameNb;//number of the current frame (for animation)
		SDL_Rect framePos;
	private :
		
	public:
		Ship();
		Ship(SDL_Texture *t);
		Ship(SDL_Texture *t, int x, int y);
		Ship(SDL_Texture *t, SDL_Rect coo, int speed);
		
		SDL_Texture *getTexture();
		SDL_Rect getCoo();
		SDL_Rect getHitbox();
		int getX();
		int getY();
		int getW();
		int getH();
		int getSpeed();
		int getHealth();
		int getMaxHealth();
		
		void setTexture(SDL_Texture *t);
		void setCoo(SDL_Rect n);
		void setHitbox(SDL_Rect b);
		void setX(int x);
		void setY(int y);
		void setW(int w);
		void setH(int h);
		void setSpeed(int s);
		void setHealth(int h);
		void setMaxHealth(int m);
		void setHitboxRatio(float hr);
		
		void init();
		
		void goLeft();
		void goRight();
		void goUp();
		void goDown();
		void renderShip(SDL_Renderer *r);
		void heal();
		void heal(int a);
		void healCompletely();
		void takeDamage();
		void takeDamage(int d);
		void updateHitbox();
		
		void rerack();
		
		bool hitShip(SDL_Rect s);
		
		virtual ~Ship();
};

ostream& operator<<(ostream& out, Ship &s);

#endif
