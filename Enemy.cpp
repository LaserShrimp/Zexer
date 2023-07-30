#include "Enemy.hpp"

Enemy::Enemy(SDL_Texture *t): Ship{t, 0, -50}{
	this->speed = ENEMY_SPEED;
	this->coo.x = rand()%WIN_WIDTH;
}
Enemy::Enemy(){
	this->speed = ENEMY_SPEED;
	this->coo.x = rand()%WIN_WIDTH;
	this->coo.y = -50;
}

void Enemy::setAnimation(SDL_Renderer *r){
	this->animation.setFrameSize(WIDTH, HEIGHT);
	this->animation.setNumberOfFrames(12);
	this->animation.setTexture(r, (char*)"assets/asteroidAnimation.png");
}

void Enemy::init(SDL_Renderer *r){
	this->setAnimation(r);
	
	this->speed = ENEMY_SPEED;
	this->coo.x = rand()%WIN_WIDTH;
	this->coo.y = -50;
	this->setMaxHealth(30);
	this->healCompletely();
	this->setHitboxRatio(1.0);
}

void Enemy::move(){
	if(this->coo.y > WIN_HEIGHT){
		this->rerack();
	} else {
		this->goDown();
		//cout << "enemy goes down" << endl;
	}
	this->updateHitbox();
}

/**
 * Resets the ship to fall again
 */
void Enemy::rerack(){
	this->health = this->maxHealth;
	this->coo.y = -50;
	this->coo.x = rand()%(WIN_WIDTH - 100);
	//cout << "enemy reracked : x, y, w, h " << this->getX()  << " " << this->getY() << " " << this->coo.w << " " << this->coo.h << endl;
}

/**
 * returns true if the enemy's dead, false if not
 */
bool Enemy::takeDamage(int damage){
	//cout << "enemy takes damage " << endl << "ennemy health before : " << this->health << endl;
	this->health-= damage;
	if(this->health <= 0){
		this->rerack();
		return true;
	}
	//cout << "enemy's health : " << this->health << endl;
	return false;
}

void Enemy::renderShip(SDL_Renderer *r){
// 	cout << "begun rendering animation" << endl;
	this->animation.renderImage(r, this->coo);
// 	cout << "here" << endl;
	this->animation.nextFrame();
	cout << "finished rendering animation" << endl;
	
	//Drawing health bar only if the ship is damaged
	SDL_Rect hmcoo = this->coo;
	hmcoo.y = this->coo.y - 4;
	hmcoo.h = 4;
	SDL_Rect hcoo = hmcoo;
	hcoo.h = 2;
	hcoo.y = hmcoo.y+1;
	cout << "it's here";
	hcoo.w = this->health*1.0/this->maxHealth*1.0 * hmcoo.w;
	cout << "right here" << endl;
	if(this->health*1.0/this->maxHealth*1.0 > 20.0/100.0){
		SDL_SetRenderDrawColor(r, 255, 200, 50, 255);
	} else {
		SDL_SetRenderDrawColor(r, 255, 0, 0, 0);
	}
	if(this->health < this->maxHealth){
		SDL_RenderFillRect(r, &hcoo);
		SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
		SDL_RenderDrawRect(r, &hmcoo);
	}
	
	SDL_SetRenderDrawColor(r, 0, 0, 0, 0);
}

Enemy::~Enemy(){
	if(this->texture != NULL){
		SDL_DestroyTexture(this->texture);
	}
}
