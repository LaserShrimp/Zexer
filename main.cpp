#include <iostream>
#include <cstdlib>
#include <ctime>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include "defines.h"
#include "Ship.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include "Missile.hpp"
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
							SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, 0);
	if(renderer == NULL){
		cout << "renderer loading error..." << endl;
		exit(EXIT_FAILURE);
	}
	if(SDL_SetRenderTarget(renderer, NULL) < 0){
		cout << "Cannot set renderer target..." << endl;
		exit(EXIT_FAILURE);
	}
	
	Uint32 prevTime = SDL_GetTicks();
	Player *ship = new Player(NULL);
	
	ship->init(renderer);
	vector<Missile*> vAmmo;
	for(int i = 0; i < 3; i++){
		//Missile m = Missile(SDL_CreateTextureFromSurface(renderer, IMG_Load("missile.png")));
		vAmmo.push_back(new Missile(SDL_CreateTextureFromSurface(renderer, IMG_Load("missile.png"))));
	}
	ship->setAmmo(vAmmo);
	for(Missile* mi: ship->getAmmo()){
		mi->setTexture(SDL_CreateTextureFromSurface(renderer, IMG_Load("missile.png")));
	}
	//SDL_Texture *texe1 = SDL_CreateTextureFromSurface(renderer, IMG_Load("enemy.png"));
    vector<Enemy*> vEnemy;
	for(int i = 0; i < 5; i++){
		vEnemy.push_back(new Enemy());
// 		vEnemy[i]->setMaxHealth(30);
// 		vEnemy[i]->healCompletely();
		vEnemy[i]->init(renderer);
	}
// 	for(Enemy* e: vEnemy){
// 		e->setTexture(SDL_CreateTextureFromSurface(renderer, IMG_Load("enemy.png")));
// 	}
	
	GameInterface *gameInterface = new GameInterface;
	gameInterface->initBackground(renderer);
	
	InputState inputs;
	int fps = FPS;
	int frameTime = 1000/fps; //1000 milliseconds/FPS
	
	Uint32 timeStampIncrease = SDL_GetTicks();
	Uint32 timeEnemyIncrease = SDL_GetTicks();
	Uint32 timeHealthIncrease = SDL_GetTicks();
	
	while (ship->getHealth() >= 0  && !inputs.getquit()) {
		if(SDL_GetTicks() >= prevTime + frameTime){
			SDL_PollEvent(&event);
			inputs.setState(event);
			ship->doActions(inputs);
			ship->updateAmmos();
			
			for(Enemy* e: vEnemy){
				e->move();
				if(ship->hitShip(e->getHitbox())){
					ship->takeDamage(e->getMaxHealth());
					if(e->takeDamage(ship->getMaxHealth())){
						gameInterface->increaseScore();
					}
				}
				int indexCollision = ship->missileCollidesWith(e->getHitbox());
				if(indexCollision > -1){
					if(e->takeDamage(ship->getMissile(indexCollision)->getMaxHealth())){
						gameInterface->increaseScore();
					}
					ship->damageMissile(indexCollision, e->getMaxHealth());
				}
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
				vEnemy[elem]->setSpeed(vEnemy[elem]->getSpeed()+2);
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
			ship->renderShip(renderer);
			for(Enemy* e: vEnemy){
				e->renderShip(renderer);
			}
			gameInterface->loadStatsFromPlayer(*ship);
			gameInterface->render(renderer);
			SDL_RenderPresent(renderer);
			SDL_RenderClear(renderer);
			prevTime = SDL_GetTicks();
		}
	}
	cout << "Final score : " << gameInterface->getScore() << endl;
	delete gameInterface;
	delete ship;
	for(Enemy* e: vEnemy){
		delete e;
	}
	cout << endl << endl << "HERE !!" << endl << endl;
    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
	
	return 0;
}
