#ifndef __SHIP_HPP__
#define __SHIP_HPP__

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "defines.h"

using namespace std;

class Ship{
	protected:
		SDL_Texture *texture;
		SDL_Rect coo;
		int speed;
		int health;
		int maxHealth;
	private :
		
	public:
		Ship();
		Ship(SDL_Texture *t);
		Ship(SDL_Texture *t, int x, int y);
		Ship(SDL_Texture *t, SDL_Rect coo, int speed);
		
		SDL_Texture *getTexture();
		SDL_Rect getCoo();
		int getX();
		int getY();
		int getSpeed();
		int getHealth();
		int getMaxHealth();
		
		void setTexture(SDL_Texture *t);
		void setCoo(SDL_Rect nc);
		void setX(int x);
		void setY(int y);
		void setSpeed(int s);
		void setHealth(int h);
		void setMaxHealth(int m);
		
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
		
		void rerack();
		
		bool hitShip(SDL_Rect s);
		
		virtual ~Ship();
};

ostream& operator<<(ostream& out, Ship &s);

#endif
