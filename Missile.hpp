#ifndef __MISSILE_HPP__
#define __MISSILE_HPP__

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "Ship.hpp"

class Missile: public Ship{
	private:
		bool ready; //True if it's in the stack, false otherwise
	protected:
	public:
		Missile(SDL_Texture *t);
		Missile();
		
		bool isReady();
		void setReady(bool r);
		void setToStack();
		
		bool launch(int startX, int startY);
		virtual void move();
		virtual void takeDamage(int d);
		
		virtual ~Missile();
};

ostream& operator<<(ostream& out, Missile &m);

#endif
