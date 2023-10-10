#include "Enemy.hpp"

Enemy::Enemy(){
	this->speed = ENEMY_SPEED;
	this->coo.x = rand()%WIN_WIDTH;
	this->coo.y = -50;
	this->cooVect.setX(rand()%WIN_WIDTH);
	this->cooVect.setY(-50);
	this->speedVect.setX(0);
	this->speedVect.setY(ENEMY_SPEED);
}
Enemy::Enemy(const Enemy& e){
	this->speed = e.speed;
	this->coo.x = e.coo.x;
	this->coo.y = e.coo.y;
}

void Enemy::setAnimationNeutral(SDL_Renderer *r){
	this->animNeutral.setFrameSize(WIDTH, HEIGHT);
	this->animNeutral.setNumberOfFrames(12);
	this->animNeutral.setTexture(r, (char*)"assets/asteroidAnimation.png");
}
void Enemy::setAnimationNeutral(SDL_Renderer *r, char* animName, int nbFrames, int frameW, int frameH){
	this->animNeutral.setFrameSize(frameW, frameH);
	this->animNeutral.setNumberOfFrames(nbFrames);
	this->animNeutral.setTexture(r, animName);
}

void Enemy::init(SDL_Renderer *r){
	this->setAnimationNeutral(r);
	
	this->id = "asteroid";
	this->speed = ENEMY_SPEED;
	this->atk = 20;
	this->coo.x = rand()%WIN_WIDTH;
	this->coo.y = -50;
	this->setMaxHealth(30);
	this->healCompletely();
	this->setHitboxRatio(1.0);
	this->invincible = 0;
}

void Enemy::move(){
	if(this->coo.y > WIN_HEIGHT){
		this->rerack();
	} else {
		this->translationMovement();
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
	this->synchronizeVectFromCoo();
}

/**
 * returns true if the enemy's dead, false if not
 */
bool Enemy::takeDamage(int damage){
	this->health-= damage;
	if(this->health <= 0){
		this->rerack();
		return true;
	}
	return false;
}

void Enemy::renderShip(SDL_Renderer *r){
	if(!isOnCamera(this->coo))
		return;
	//	changing the alpha if it took damages
	if(this->invincible > 0){
		this->animNeutral.changeAlpha(rand()%255);
		this->invincible++;
		if(this->invincible == this->nbFramesInvincible)
			this->invincible = 0;
	} else {
		this->animNeutral.resetAlpha();
	}
	this->animNeutral.renderImage(r, this->coo);
	this->animNeutral.nextFrame();
	
	//Drawing health bar only if the ship is damaged
	SDL_Rect hmcoo = this->coo;
	hmcoo.y = this->coo.y - 4;
	hmcoo.h = 4;
	SDL_Rect hcoo = hmcoo;
	hcoo.h = 2;
	hcoo.y = hmcoo.y+1;
	hcoo.w = this->health*1.0/this->maxHealth*1.0 * hmcoo.w;
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
}
