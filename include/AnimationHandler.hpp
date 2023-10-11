#ifndef __ANIMATIONHANDLER_HPP__
#define __ANIMATIONHANDLER_HPP__

#include <iostream>
#include <vector>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "Ship.hpp"
#include "Player.hpp"
#include "defines.h"
#include "gameAddOns.h"
#include "Animation.hpp"
#include "Vect.hpp"

using namespace std;

class AnimationHandler{
private:
	vector<Animation*> vAnim;
	vector<Animation*> vAnimPlayer; //animations for the player
	SDL_Renderer *r;
protected:
public:
	AnimationHandler(SDL_Renderer *r);
	void renderOnScreen(Ship &s);
	void renderOnScreen(Player &p);
	void addAnim(const Animation *a);
	void resetAlphaPlayer();
	void changeAlphaPlayer(int alpha);
	
	~AnimationHandler();
};

#endif
