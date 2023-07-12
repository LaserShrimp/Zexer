#include "Missile.hpp"

Missile::Missile(SDL_Texture *t): Ship{t}, ready{true}{
	this->speed = MISSILE_SPEED;
	this->maxHealth = 10;
}

Missile::Missile(): ready{true}{
	this->speed = MISSILE_SPEED;
	this->maxHealth = 10;
}

void Missile::setReady(bool r){this->ready = r;};

/**
 * This function put the missile outside of the screen (in the stack)
 */
void Missile::setToStack(){
	this->coo.x = WIN_WIDTH;
	this->coo.y = WIN_HEIGHT;
	this->healCompletely();
	this->setReady(true);
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
		this->goUp();
		//cout << this->coo.y << endl;
	}
}
void Missile::takeDamage(int d){
	this->health-= d;
	if(this->health <= 0){
		this->setToStack();
		//cout << "restacked missile" << endl;
	}
	cout << this->getX() << " " << this->getY() <<endl;
}


Missile::~Missile(){
	SDL_DestroyTexture(this->texture);
}

ostream& operator<<(ostream& out, Missile &m){
	out << "coo.x = " << m.getCoo().x << ", coo.y = " << m.getCoo().y << ", coo.w = " << m.getCoo().w << endl ;
	return out;
}