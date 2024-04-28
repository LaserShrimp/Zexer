#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include "defines.h"
#include "gameAddOns.h"
#include "Ship.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include "Missile.hpp"
#include "Unit1.hpp"
#include "InputState.hpp"
#include "GameInterface.hpp"
#include "AnimationHandler.hpp"
#include "Wave.hpp"
#include "Item.hpp"

class Game{
private:
	int score_;
protected:
public:
	Game();
	
	void setScore(int score);
	int getScore();
	
	void start(SDL_Renderer *renderer);
	void pause();
	void endScreen(SDL_Renderer *r, bool win);
	
	virtual ~Game();
};

#endif
