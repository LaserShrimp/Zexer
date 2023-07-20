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

Enemy::~Enemy(){
	if(this->texture != NULL){
		SDL_DestroyTexture(this->texture);
	}
}
