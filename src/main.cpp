#include <iostream>
#include <cstdlib>
#include <ctime>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include "Game.hpp"

using namespace std;

int main(int argc, char **argv){
	//cout << "Hello World !" << endl;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
		exit(EXIT_FAILURE);
    }
    if(TTF_Init() < 0){
		fprintf(stderr, "Error : %s", TTF_GetError());
		exit(EXIT_FAILURE);
	}
// 	int flags = Mix_Init(MIX_INIT_MP3|MIX_INIT_OGG|MIX_INIT_FLAC|MIX_INIT_MOD|MIX_INIT_MID|MIX_INIT_OPUS);
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)){
		fprintf(stderr, "Error : %s", Mix_GetError());
		exit(EXIT_FAILURE);
	}
	srand(time(nullptr));
	SDL_Window *window;
        SDL_Renderer *renderer;
//         SDL_Event event;
		
    window = SDL_CreateWindow("Shoot'em up",
							SDL_WINDOWPOS_CENTERED,
							SDL_WINDOWPOS_CENTERED,
							WIN_WIDTH, WIN_HEIGHT,
							/*SDL_WINDOW_FULLSCREEN_DESKTOP*/SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, 0);
	if(renderer == NULL){
		cout << "renderer loading error..." << endl;
		exit(EXIT_FAILURE);
	}
	if(SDL_SetRenderTarget(renderer, NULL) < 0){
		cout << "Cannot set renderer target..." << endl;
		exit(EXIT_FAILURE);
	}
	TTF_Font *font = TTF_OpenFont("Hybrid_b.ttf", 50);
	SDL_Surface *sPlayButton = TTF_RenderText_Blended(font, "Press ENTER to play :)", {255, 255, 255, 255});
	SDL_Texture *tPlayButton = SDL_CreateTextureFromSurface(renderer, sPlayButton);
	SDL_Rect cooPlayButton = {.x = WIN_WIDTH/2 - sPlayButton->w/2, .y = WIN_HEIGHT/2 - sPlayButton->h/2, .w = sPlayButton->w, .h = sPlayButton->h};
	
	char bufferScore[30];
	snprintf(bufferScore, 29, "score : %d", 0);
	SDL_Surface *sScore = TTF_RenderText_Blended(font, bufferScore, {255, 255, 255, 255});
	SDL_Texture *tScore = SDL_CreateTextureFromSurface(renderer, sScore);
	SDL_Rect cooScore = {.x = WIN_WIDTH/2 - sScore->w/2, .y = WIN_HEIGHT/2 + sScore->h, .w = sScore->w, .h = sScore->h};
	
	SDL_Event e;
	SDL_PollEvent(&e);
	Game g;
	while(e.type != SDL_QUIT && !(e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)){
		SDL_WaitEvent(&e);
		if(e.type == SDL_KEYUP){
			switch(e.key.keysym.sym){
				case SDLK_RETURN:{
					g.setScore(0);
					g.start(renderer, window);
					snprintf(bufferScore, 29, "score : %d", g.getScore());
					SDL_FreeSurface(sScore);
					SDL_DestroyTexture(tScore);
					sScore = TTF_RenderText_Blended(font, bufferScore, {255, 255, 255, 255});
					tScore = SDL_CreateTextureFromSurface(renderer, sScore);
					break;
				}
				default:
					break;
			}
		}
		
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, tScore, NULL, &cooScore);
		SDL_RenderCopy(renderer, tPlayButton, NULL, &cooPlayButton);
		SDL_RenderPresent(renderer);
	}
	TTF_CloseFont(font);
	SDL_FreeSurface(sPlayButton);
	SDL_DestroyTexture(tPlayButton);
	SDL_FreeSurface(sScore);
	SDL_DestroyTexture(tScore);
    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
	
	return 0;
}
