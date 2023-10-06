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
	
// 	Uint32 prevTime = SDL_GetTicks();
	Player *player = new Player();
	
	player->init(renderer);
	vector<Missile*> vAmmo;
	for(int i = 0; i < 3; i++){
		vAmmo.push_back(new Missile());
	}
	player->setAmmo(vAmmo);
	for(Missile* mi: player->getAmmo()){
		mi->setAnimationNeutral(renderer);
		mi->setToStack();
	}
    vector<Ship*> vEnemy;
	for(int i = 0; i < 6; i++){
		vEnemy.push_back(new Enemy());
		vEnemy[i]->init(renderer);
		if(i == 5){
			Unit1 *u = new Unit1();
			u->init(renderer);
			vEnemy.push_back(u);
		}
	}
	
	GameInterface *gameInterface = new GameInterface;
	gameInterface->initBackground(renderer);
	
	InputState inputs;
	int fps = FPS;
	Uint32 frameTime = 1000/fps; //1000 milliseconds/FPS
	Uint32 tick1 = 0;
	Uint32 tick2 = 0;
	
	Uint32 timeStampIncrease = SDL_GetTicks();
	Uint32 timeEnemyIncrease = SDL_GetTicks();
	Uint32 timeHealthIncrease = SDL_GetTicks();
	
	while (player->getHealth() > 0  && !inputs.getquit() && !inputs.getescape()) {
			tick1 = SDL_GetTicks();
			SDL_PollEvent(&event);
			inputs.setState(event);
			player->doActions(inputs);
			player->updateAmmos();
			
			int pos = 0;
			for(Ship* e: vEnemy){
				e->move();
				if(player->hitShip(e->getHitbox())){
					player->takeDamage(e->getAtk());
				}
				int indexCollision = player->missileCollidesWith(e->getHitbox());
				if(indexCollision > -1){
					if(e->takeDamage(player->getMissile(indexCollision)->getAtk())){
						gameInterface->increaseScore();
					} else {
						e->scintillate(10);
					}
					player->damageMissile(indexCollision, e->getAtk());
				}
				pos++;
			}
			//Adding some difficulty over the time
			if(SDL_GetTicks() - timeEnemyIncrease >= 20000){
				Enemy* n = new Enemy;
				n->init(renderer);
				vEnemy.push_back(n);
				cout << "new enemy : " << vEnemy.size() << " enemies" << endl; 
				timeEnemyIncrease = SDL_GetTicks();
			}
			if(SDL_GetTicks() - timeStampIncrease >= 10000){
				int elem{rand()%(int)vEnemy.size()};
				vEnemy[elem]->setYSpeed(vEnemy[elem]->getYSpeed()+2);
				cout << "speed increased" << endl;
				timeStampIncrease = SDL_GetTicks();
			}
			if(SDL_GetTicks() - timeHealthIncrease >= 15000){
				int elem{rand()%(int)vEnemy.size()};
				vEnemy[elem]->setMaxHealth(vEnemy[elem]->getMaxHealth()+50);
				cout << "health increased" << endl;
				timeHealthIncrease = SDL_GetTicks();
			}
			
			//RENDERING
			player->renderShip(renderer);
			for(Ship* e: vEnemy){
				e->renderShip(renderer);
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
	for(Ship* e: vEnemy){
		delete e;
	}
    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
	
	return 0;
}
