#include "GameInterface.hpp"

GameInterface::GameInterface():health{0}, maxHealth{0}, score{0}, munitions{0}, font{TTF_OpenFont("myFont.ttf", 15)}, coo{.x = 0, .y = 0, .w = 500, .h = 20}{
}

GameInterface::GameInterface(const GameInterface& gi){
	this->health = gi.health;
	this->maxHealth = gi.maxHealth;
	this->score = gi.score;
	this->munitions = gi.munitions;
	this->font = TTF_OpenFont("myFont.ttf", 15);
	this->coo = gi.coo;
}

void GameInterface::loadStatsFromPlayer(Player& p){
	this->health = p.getHealth();
	this->maxHealth = p.getMaxHealth();
	this->munitions = p.getNbAmmo();
}

void GameInterface::increaseScore(){
	this->score++;
}
void GameInterface::increaseScore(int points){
	this->score+= points;
}

void GameInterface::render(SDL_Renderer *r){
	char buffer[200];
	sprintf(buffer, "health : %d/%d  score : %d  ammo : %d", this->health, this->maxHealth, this->score, this->munitions);
	SDL_Texture *t = SDL_CreateTextureFromSurface(r, TTF_RenderText_Blended(this->font, buffer, {255, 255, 255, 255}));
	if(t == NULL){
		cout << "TTF Texture == NULL\n" << endl;
	}
	SDL_RenderCopy(r, t, NULL, &(this->coo));
	SDL_DestroyTexture(t);
}

GameInterface::~GameInterface(){
	cout << "closing font of game interface" << endl;
	if(this->font != NULL)
		TTF_CloseFont(this->font);
}
