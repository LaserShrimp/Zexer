#ifndef __GAMEINTERFACE_HPP__
#define __GAMEINTERFACE_HPP__

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include "defines.h"
#include "Player.hpp"

#define INT_W	750
#define INT_H	100

class GameInterface{
	private:
		int health;
		int maxHealth;
		int score;
		int munitions;
		
		TTF_Font *font;
		SDL_Texture *renderTexture;
		SDL_Texture *backgroundTexture;
		SDL_Rect coo;
		SDL_Rect hcoo;
		SDL_Rect hmcoo;
		SDL_Rect scoo;
		SDL_Rect mcoo;
	protected:
	public:
		GameInterface();
		GameInterface(const GameInterface &gi);
		
		void initBackground(SDL_Renderer *r);
		
		int getScore();
		
		void loadStatsFromPlayer(Player& p);
		void increaseScore();
		void increaseScore(int points);
		
		void render(SDL_Renderer *r);
		
		virtual ~GameInterface();
};

#endif
