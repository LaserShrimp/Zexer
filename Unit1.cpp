#include "Unit1.hpp"

Unit1::Unit1():shootCooldown{200}, moveCooldown{30}, staticCooldown{120}{
	
}

void Unit1::init(SDL_Renderer *r){
	shCurr = -1;
	mCurr = -1;
	stCurr = 0;
	this->speed = 10.5;
	this->speedVect.setY(0.4);
	this->speedVect.setX(0);
	this->coo.x = rand()%WIN_WIDTH;
	this->coo.y = -50;
	this->coo.w = 50;
	this->coo.h = 50;
	this->setHitboxRatio(1.0);
	this->synchronizeVectFromCoo();
	this->setAnimationNeutral(r, (char*) "assets/unit1.png", 27, 50, 50);
	this->setStayInScreen(true);
	
	this->setMaxHealth(150);
	this->healCompletely();
	this->atk = 10;
	this->invincible = 0;
}

void Unit1::move(){
	if(this->stCurr == this->staticCooldown){
		this->randomDir();
		this->stCurr = -1;
		this->mCurr = 0;
	}
	else if(this->mCurr >= 0){
		this->mCurr++;
		if(this->moveCooldown == this->mCurr){
			this->mCurr = -1;
			this->stCurr = 0;
			this->speedVect.setX(0);
		}
	} else if(this->stCurr >= 0){
		this->stCurr++;
	}
	this->translationMovement();
	this->updateHitbox();
}

/**
 * set a random direction on x axis
 */
void Unit1::randomDir(){
	if(rand()%3 < 2)// 2/3 chances to change the direction
		this->speed = this->speed * (-1);
	this->speedVect.setX(speed);
}

Unit1::~Unit1(){}
