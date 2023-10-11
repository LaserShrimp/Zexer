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
		Missile();
		
// 		void setAnimationNeutral(SDL_Renderer *r);
		bool isReady();
		void setReady(bool r);
		void setToStack();
		
		bool launch(int startX, int startY);
		virtual void move();
		bool takeDamage(int d);
		
		virtual ~Missile();
};

ostream& operator<<(ostream& out, Missile &m);

#endif
