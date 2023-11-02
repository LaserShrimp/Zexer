#ifndef __MISSILE_HPP__
#define __MISSILE_HPP__

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "Ship.hpp"

class Missile: public Ship{
	private:
// 		bool ready; //True if it's in the stack, false otherwise
	protected:
	public:
		Missile();
		Missile(int x, int y);
		
		virtual void launch(int startX, int startY);
		virtual void launch(int startX, int startY, Vect dir);
		virtual void launch(int startX, int startY, string launcherId);
		virtual void launch(int startX, int startY, string launcherId, int atk);
		virtual void move();
		bool takeDamage(int d);
		
		virtual ~Missile();
};

ostream& operator<<(ostream& out, Missile &m);

#endif
