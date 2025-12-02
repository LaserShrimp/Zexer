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
#include "gameAddOns.hpp"
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
#include "SDLMenu.hpp"

class Game {
private:
	int score_{0};

	bool gameLoopActive_{true};
	bool levelContinues_{true};
	bool gamePaused_{false};
	bool escapeReleased_{true};

	void pauseMenu(SDL_Renderer *renderer);
protected:
	Game() = default;
	static Game *game_;
public:
	static Game* getInstance();
	Game(Game& game) = delete;
	void operator=(Game& game) = delete;
	
	void setScore(int score);
	int getScore();
	
	void start(SDL_Renderer *renderer);
	void pause();
	void endScreen(SDL_Renderer *r, bool win);
	
	virtual ~Game() = default;
};

#endif
