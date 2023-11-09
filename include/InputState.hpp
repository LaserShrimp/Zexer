#ifndef __INPUTSTATE_HPP__
#define __INPUTSTATE_HPP__

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "defines.h"

class InputState{
	private:
		bool z, q, s, d;
		bool right, left, up, down;
		bool spacebar;
		bool escape;
		bool quit;
		//add other inputs if necessary
		//...
	protected:
	
	public:
		InputState();
		void setState(const SDL_Event event);
		void resetState();
		SDL_Event getState();
	
		bool getz() const;
		bool getq() const;
		bool gets() const;
		bool getd() const;
		bool getright() const;
		bool getleft() const;
		bool getup() const;
		bool getdown() const;
		bool getspacebar() const;
		bool getescape() const;
		bool getquit() const;
	
		virtual ~InputState();
};

#endif
