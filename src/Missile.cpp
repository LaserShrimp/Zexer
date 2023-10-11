#include "Missile.hpp"

Missile::Missile(): Ship{}, ready{true}{
	this->id = "missile";
	this->speed = MISSILE_SPEED;
	this->speedVect.setX(0);
	this->speedVect.setY(-MISSILE_SPEED);
	this->maxHealth = 10;
	this->atk = 10;
	this->cooVect = Vect(0, 0);
	this->synchronizeVectFromCoo();
}

// void Missile::setAnimationNeutral(SDL_Renderer *r){
// 	this->animNeutral.setFrameSize(10, 10);
// 	this->animNeutral.setNumberOfFrames(6);
// 	this->animNeutral.setTexture(r, (char*)"assets/missile.png");
// }

void Missile::setReady(bool r){this->ready = r;};

/**
 * This function put the missile outside of the screen (in the stack)
 */
void Missile::setToStack(){
	this->coo.x = WIN_WIDTH;
	this->coo.y = WIN_HEIGHT;
	this->healCompletely();
	this->setReady(true);
	this->updateHitbox();
	this->synchronizeVectFromCoo();
}

bool Missile::isReady(){return ready;}

/**
 * This function launches the missile if ready. Returns false if not
 */
bool Missile::launch(int startX, int startY){
	if(this->ready){
		this->ready = false;
		this->coo.x = startX;
		this->coo.y = startY;
		this->synchronizeVectFromCoo();
		this->updateHitbox();
		return true;
	} else {
		return false;
	}
}

void Missile::move(){
	//If the ammo reached the top of the screen
	if(this->coo.y < 0 || this->health <= 0){
		this->setToStack();
	} else {
		this->translationMovement();
	}
	this->updateHitbox();
}
bool Missile::takeDamage(int d){
	this->health-= d;
	if(this->health <= 0){
		this->setToStack();
		return true;
	}
	return false;
}


Missile::~Missile(){
}

ostream& operator<<(ostream& out, Missile &m){
	out << "coo.x = " << m.getCoo().x << ", coo.y = " << m.getCoo().y << ", coo.w = " << m.getCoo().w << endl ;
	return out;
}
