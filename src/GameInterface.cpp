#include "GameInterface.hpp"

GameInterface::GameInterface():health{0}, maxHealth{0}, score{0}, munitions{0}, font{TTF_OpenFont("Hybrid_b.ttf", 30)}, renderTexture{NULL}, backgroundTexture{NULL}, coo{.x = WIN_WIDTH/2 - INT_W/2, .y = WIN_HEIGHT - INT_H, .w = INT_W, .h = INT_H}, hcoo{.x = 0, .y = 15 , .w = INT_W, .h = 20}, hmcoo{.x = 0, .y = 15, .w = 500, .h = 20}, scoo{.x = INT_W/4, .y = INT_H - 50, .w = 150, .h = 30}, mcoo{.x = INT_W/4, .y = INT_H - 70, .w = 150, .h = 30}{
}

GameInterface::GameInterface(const GameInterface& gi){
	this->health = gi.health;
	this->maxHealth = gi.maxHealth;
	this->score = gi.score;
	this->munitions = gi.munitions;
	this->font = TTF_OpenFont("Hybrid_o.ttf", 30);
	this->coo = gi.coo;
	this->hcoo = gi.hcoo;
	this->hmcoo = gi.hmcoo;
	this->scoo = gi.scoo;
	this->mcoo = gi.mcoo;
}

void GameInterface::initBackground(SDL_Renderer *r){
	SDL_Surface *s = IMG_Load("assets/interfaceBackground.png");
 	this->backgroundTexture = SDL_CreateTextureFromSurface(r, s);
	this->renderTexture = SDL_CreateTexture(r, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, INT_W, INT_H);
	SDL_SetTextureBlendMode(this->renderTexture, SDL_BLENDMODE_BLEND);
	SDL_FreeSurface(s);
}

int GameInterface::getScore(){return this->score;}

void GameInterface::loadStatsFromPlayer(Player& p){
	this->health = p.getHealth();
	this->maxHealth = p.getMaxHealth();
// 	this->munitions = p.getNbAmmo();
	
	//coordinates
	this->hmcoo.w = p.getMaxHealth()*4;
	this->hcoo.w = p.getHealth()*4;
	this->hmcoo.x = INT_W/2 - this->hmcoo.w/2;
	this->hcoo.x = this->hmcoo.x;
	
	//We change the transparency if the player is on the lower screen
	if(p.getCoo().y + p.getCoo().h > this->coo.y)
		SDL_SetTextureAlphaMod(this->renderTexture, 0x2F);
	else{
		SDL_SetTextureAlphaMod(this->renderTexture, 0xFF);
	}
}

void GameInterface::increaseScore(){
	this->score++;
}
void GameInterface::increaseScore(int points){
	this->score+= points;
}

void GameInterface::render(SDL_Renderer *r){
	char bufferScore[30]/*, bufferMun[30]*/;
	snprintf(bufferScore, 30, "score : %d", this->score);
	SDL_Surface *s = TTF_RenderText_Blended(this->font, bufferScore, {255, 255, 255, 255});
	SDL_Texture *ts = SDL_CreateTextureFromSurface(r, s);
	if(ts == NULL/* || tm == NULL*/){
		cout << "TTF Texture == NULL\n" << endl;
	}
	SDL_SetRenderTarget(r, this->renderTexture);
	SDL_SetRenderDrawColor(r, 0, 0, 0, 0);
	//SDL_RenderClear(r);
	SDL_RenderCopy(r, this->backgroundTexture, NULL, NULL);
	this->scoo.w = s->w;
	this->scoo.h = s->h;
	SDL_RenderCopy(r, ts, NULL, &(this->scoo));
	
	//Drawing health bar
	if(this->health == this->maxHealth){
		SDL_SetRenderDrawColor(r, 0, 255, 0, 255);
	} else if(this->health*1.0/this->maxHealth*1.0 > 20.0/100.0){
		SDL_SetRenderDrawColor(r, 255, 125, 50, 255);
	} else {
		SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
	}
	SDL_RenderFillRect(r, &(this->hcoo));
	SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
	SDL_RenderDrawRect(r, &(this->hmcoo));
	SDL_SetRenderTarget(r, NULL);
	SDL_RenderCopy(r, this->renderTexture, NULL, &(this->coo));

	if(health <= 20){
		SDL_Texture *textureContour = SDL_CreateTextureFromSurface(r, IMG_Load("assets/redContour.png"));
		SDL_RenderCopy(r, textureContour, NULL, NULL);
	}
	
	SDL_SetRenderDrawColor(r, 0, 0, 0, 0);
	SDL_DestroyTexture(ts);
	SDL_FreeSurface(s);
}

GameInterface::~GameInterface(){
	//cout << "closing font of game interface" << endl;
	if(this->font != NULL)
		TTF_CloseFont(this->font);
	if(this->renderTexture != NULL)
		SDL_DestroyTexture(this->renderTexture);
	if(this->backgroundTexture != NULL)
		SDL_DestroyTexture(this->backgroundTexture);
	
}
