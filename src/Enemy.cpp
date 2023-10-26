#include "Enemy.hpp"

Enemy::Enemy(){
	this->speed = ENEMY_SPEED;
	this->coo.w = WIDTH;
	this->coo.h = HEIGHT;
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

void Enemy::init(){
	
	this->id = "asteroid";
	this->speed = ENEMY_SPEED;
	this->atk = 20;
	this->strength = 20;
	this->coo.x = rand()%WIN_WIDTH;
	this->coo.y = -50;
	this->coo.w = WIDTH;
	this->coo.h = HEIGHT;
	this->setMaxHealth(30);
	this->healCompletely();
	this->setHitboxRatio(1.0);
	this->invincible = 0;
}

void Enemy::move(){
	this->translationMovement();
	this->updateHitbox();
}

/**
 * returns true if the enemy's dead, false if not
 */
bool Enemy::takeDamage(int damage){
	this->health-= damage;
	if(this->health <= 0){
		return true;
	}
	return false;
}

Enemy::~Enemy(){
// 	cout << "enemy deleted" << endl;
}
