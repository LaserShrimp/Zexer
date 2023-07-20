#include "GameInterface.hpp"

GameInterface::GameInterface():health{0}, maxHealth{0}, score{0}, munitions{0}, font{TTF_OpenFont("Hybrid_b.ttf", 15)}, coo{.x = 0, .y = 0, .w = 500, .h = 20}, hcoo{.x = 0, .y = WIN_HEIGHT - 100, .w = 500, .h = 20}, hmcoo{.x = 0, .y = WIN_HEIGHT - 100, .w = 500, .h = 20}, scoo{.x = 0, .y = WIN_HEIGHT - 75, .w = 250, .h = 30}, mcoo{.x = 0, .y = WIN_HEIGHT - 100, .w = 250, .h = 30}{
}

GameInterface::GameInterface(const GameInterface& gi){
	this->health = gi.health;
	this->maxHealth = gi.maxHealth;
	this->score = gi.score;
	this->munitions = gi.munitions;
	this->font = TTF_OpenFont("Hybrid_b.ttf", 15);
	this->coo = gi.coo;
	this->hcoo = gi.hcoo;
	this->hmcoo = gi.hmcoo;
	this->scoo = gi.scoo;
	this->mcoo = gi.mcoo;
}

int GameInterface::getScore(){return this->score;}

void GameInterface::loadStatsFromPlayer(Player& p){
	this->health = p.getHealth();
	this->maxHealth = p.getMaxHealth();
	this->munitions = p.getNbAmmo();
	
	//coordinates
	this->hmcoo.w = p.getMaxHealth()*2;
	this->hcoo.w = p.getHealth()*2;
	this->hmcoo.x = WIN_WIDTH/2 - this->hmcoo.w/2;
	this->hcoo.x = this->hmcoo.x;
}

void GameInterface::increaseScore(){
	this->score++;
}
void GameInterface::increaseScore(int points){
	this->score+= points;
}

void GameInterface::render(SDL_Renderer *r){
	char bufferScore[30], bufferMun[30];
	snprintf(bufferScore, 30, "score : %d", this->score);
	snprintf(bufferMun, 30, "munitions : %d", this->munitions);
	SDL_Texture *ts = SDL_CreateTextureFromSurface(r, TTF_RenderText_Blended(this->font, bufferScore, {255, 255, 255, 255}));
	SDL_Texture *tm = SDL_CreateTextureFromSurface(r, TTF_RenderText_Blended(this->font, bufferMun, {255, 255, 255, 255}));
	if(ts == NULL || tm == NULL){
		cout << "TTF Texture == NULL\n" << endl;
	}
	SDL_RenderCopy(r, ts, NULL, &(this->scoo));
	SDL_RenderCopy(r, tm, NULL, &(this->mcoo));
	
	//Drawing health bar
	SDL_SetRenderDrawColor(r, 255, 125, 50, 255);
	SDL_RenderFillRect(r, &(this->hcoo));
	SDL_RenderDrawRect(r, &(this->hmcoo));
	
	SDL_SetRenderDrawColor(r, 0, 0, 0, 0);
	SDL_DestroyTexture(ts);
	SDL_DestroyTexture(tm);
}

GameInterface::~GameInterface(){
	//cout << "closing font of game interface" << endl;
	if(this->font != NULL)
		TTF_CloseFont(this->font);
}
