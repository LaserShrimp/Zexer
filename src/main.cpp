#include <iostream>
#include <cstdlib>
#include <ctime>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

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

using namespace std;

int main(int argc, char **argv){
	cout << "Hello World !" << endl;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
		exit(EXIT_FAILURE);
    }
    if(TTF_Init() < 0){
		fprintf(stderr, "Error : %s", TTF_GetError());
		exit(EXIT_FAILURE);
	}
	srand(time(nullptr));
	SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Event event;
		
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
	
	Wave w;
	Player *player = new Player();
	
	player->init();
    vector<Ship*> vEnemy;
	vector<Ship*> vPlayer;
	w.loadLevel(vEnemy, 1);
	w.randomizeShipCoo(vEnemy);
	
	GameInterface *gameInterface = new GameInterface;
	AnimationHandler *aHandler = new AnimationHandler(renderer);
	gameInterface->initBackground(renderer);
	
	InputState inputs;
	int fps = FPS;
	Uint32 frameTime = 1000/fps; //1000 milliseconds/FPS
	Uint32 tick1 = 0;
	Uint32 tick2 = 0;
	
// 	Uint32 timeStampIncrease = SDL_GetTicks();
// 	Uint32 timeEnemyIncrease = SDL_GetTicks();
// 	Uint32 timeHealthIncrease = SDL_GetTicks();
	
	while (player->getHealth() > 0  && !inputs.getquit() && !inputs.getescape() && w.getLevel() <= 3) {
		if(vEnemy.size() == 0){
			w.increaseLevel();
			w.loadLevel(vEnemy, w.getLevel());
			w.randomizeShipCoo(vEnemy);
		}
		tick1 = SDL_GetTicks();
		SDL_PollEvent(&event);
		inputs.setState(event);
		player->doActions(inputs, vPlayer);
		
		int pos = 0;
		for(Ship* e: vEnemy){
			e->doActions(vEnemy);
			if(player->hitShip(e->getHitbox())){
				player->takeDamage(e->getAtk());
			}
			for(Ship* p: vPlayer){
				//an enemy takes damages only if the Ship it collides with has another Id (prevents from missile to missile collisions)
				if(p->hitShip(e->getHitbox()) && p->getId() != e->getId()){
					if(e->takeDamage(p->getAtk())){
						gameInterface->increaseScore();
					} else {
						e->scintillate(10);
					}
					p->takeDamage(e->getAtk());
				}
			}
			pos++;
		}
		for(Ship* m: vPlayer){
			m->move();
		}
		
		//RENDERING
		aHandler->renderOnScreen(*player);
		for(Ship* e: vEnemy){
			aHandler->renderOnScreen(*e);
		}
		for(Ship* e: vPlayer){
			aHandler->renderOnScreen(*e);
		}
		for(long unsigned int i = 0; i < vPlayer.size(); i++){
			//if the ship is out of the screen or has no health
			if(vPlayer[i]->getCoo().y + vPlayer[i]->getCoo().h < 0 || vPlayer[i]->getHealth() <= 0){
				delete vPlayer[i];
				vPlayer.erase(vPlayer.begin()+i);
			}
		}
		for(long unsigned int i = 0; i < vEnemy.size(); i++){
			//if the ship is out of the screen or has no health
			if((vEnemy[i]->getCoo().y > WIN_HEIGHT || vEnemy[i]->getHealth() <= 0)){
				delete vEnemy[i];
				vEnemy.erase(vEnemy.begin()+i);
			}
		}
		gameInterface->loadStatsFromPlayer(*player);
		gameInterface->render(renderer);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
		tick2 = SDL_GetTicks();
		if(tick2 - tick1 < frameTime)
			SDL_Delay(frameTime - (tick2 - tick1));
	}
	cout << "Final score : " << gameInterface->getScore() << endl;
	delete gameInterface;
	delete player;
	for(long unsigned int i = 0; i < vEnemy.size(); i++){
		delete vEnemy[i];
	}
	for(long unsigned int i = 0; i < vPlayer.size(); i++){
		delete vPlayer[i];
	}
	vEnemy.clear();
	vPlayer.clear();
	delete aHandler;
    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
	
	return 0;
}
