#include "Missile.hpp"

Missile::Missile(): Ship{}{
	this->id = "missile";
	this->speed = MISSILE_SPEED;
	this->speedVect.setX(0);
	this->speedVect.setY(-MISSILE_SPEED);
	this->maxHealth = 1;
	this->atk = 10;
	this->cooVect = Vect(0, 0);
	this->coo.w = 20;
	this->coo.h = 20;
	this->hitbox = this->coo;
	this->hitboxRatio = 1.0;
	this->synchronizeVectFromCoo();
	this->healCompletely();
}
Missile::Missile(int x, int y): Ship{}/*, ready{true}*/{
	this->id = "missile";
	this->speed = MISSILE_SPEED;
	this->speedVect.setX(0);
	this->speedVect.setY(-MISSILE_SPEED);
	this->maxHealth = 1;
	this->atk = 10;
	this->cooVect = Vect(0, 0);
	this->launch(x, y);
	this->coo.w = 20;
	this->coo.h = 20;
	this->hitbox = this->coo;
	this->hitboxRatio = 1.0;
	this->synchronizeVectFromCoo();
	this->healCompletely();
}

/**
 * This function launches the missile
 */
void Missile::launch(int startX, int startY){
	this->coo.x = startX;
	this->coo.y = startY;
	this->synchronizeVectFromCoo();
	this->updateHitbox();
}
void Missile::launch(int startX, int startY, Vect dir){
	this->speedVect = dir;
	this->coo.x = startX;
	this->coo.y = startY;
	this->synchronizeVectFromCoo();
	this->updateHitbox();
}
void Missile::launch(int startX, int startY, string launcherId){
	if(launcherId == "player"){
		this->speedVect.setY(-MISSILE_SPEED);
	} else {
		this->speedVect.setY(MISSILE_SPEED);
	}
	this->coo.x = startX;
	this->coo.y = startY;
	this->synchronizeVectFromCoo();
	this->updateHitbox();
}
void Missile::launch(int startX, int startY, string launcherId, int atk){
	if(launcherId == "player"){
		this->speedVect.setY(-MISSILE_SPEED);
	} else {
		this->speedVect.setY(MISSILE_SPEED);
	}
	this->coo.x = startX;
	this->coo.y = startY;
	this->atk = atk;
	this->synchronizeVectFromCoo();
	this->updateHitbox();
}

void Missile::move(){
	this->translationMovement();
	this->updateHitbox();
}
bool Missile::takeDamage(int d){
	this->health-= d;
	if(this->health <= 0){
		return true;
	}
	return false;
}


Missile::~Missile(){
// 	cout << "Missile destroyed" << endl;
}

ostream& operator<<(ostream& out, Missile &m){
	out << "coo.x = " << m.getCoo().x << ", coo.y = " << m.getCoo().y << ", coo.w = " << m.getCoo().w << endl ;
	return out;
}
