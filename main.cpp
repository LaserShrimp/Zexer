#include <iostream>
#include <cstdlib>
#include <ctime>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "defines.h"
#include "Ship.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include "Missile.hpp"
#include "InputState.hpp"

using namespace std;

int main(int argc, char **argv){
	cout << "Hello World !" << endl;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
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
	Player ship(SDL_CreateTextureFromSurface(renderer, IMG_Load("ship.png")));
	
	ship.init();
	ship.setMaxHealth(100);
	ship.healCompletely();
	vector<Missile> vAmmo;
	for(int i = 0; i < 3; i++){
		//Missile m = Missile(SDL_CreateTextureFromSurface(renderer, IMG_Load("missile.png")));
		cout << "missile created" << endl;
		vAmmo.push_back(Missile(SDL_CreateTextureFromSurface(renderer, IMG_Load("missile.png"))));
	}
	ship.setAmmo(vAmmo);
	for(Missile &mi: ship.getAmmo()){
		mi.setTexture(SDL_CreateTextureFromSurface(renderer, IMG_Load("missile.png")));
	}
	//SDL_Texture *texe1 = SDL_CreateTextureFromSurface(renderer, IMG_Load("enemy.png"));
    vector<Enemy> vEnemy;
	for(int i = 0; i < 5; i++){
		vEnemy.push_back(Enemy());
		vEnemy[i].setMaxHealth(30);
		vEnemy[i].healCompletely();
	}
	for(Enemy &e: vEnemy){
		e.setTexture(SDL_CreateTextureFromSurface(renderer, IMG_Load("enemy.png")));
	}
	
	InputState inputs;
	
	while (ship.getHealth() >= 0  && !inputs.getquit()) {
		if(SDL_GetTicks() >= prevTime + 20){
			SDL_PollEvent(&event);
			inputs.setState(event);
			ship.doActions(inputs);
			ship.updateAmmos();
			
			for(Enemy &e: vEnemy){
				e.move();
				if(ship.hitShip(e.getCoo())){
					ship.takeDamage(e.getMaxHealth());
					e.takeDamage(ship.getMaxHealth());
				}
				int indexCollision = ship.missileCollidesWith(e.getCoo());
				if(indexCollision > -1){
					e.takeDamage(ship.getMissile(indexCollision).getMaxHealth());
					ship.damageMissile(indexCollision, e.getMaxHealth());
				}
			}
			
			//RENDERING
			ship.renderShip(renderer);
			for(Enemy &e: vEnemy){
				e.renderShip(renderer);
			}
			SDL_RenderPresent(renderer);
			SDL_RenderClear(renderer);
			prevTime = SDL_GetTicks();
		}
	}
    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;
}
