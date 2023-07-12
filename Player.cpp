#include "Player.hpp"

Player::Player(SDL_Texture *t):Ship{t}, nbAmmo{0}, stackSize{0}, ammo{vector<Missile>{}}{}

Player::~Player(){}

int Player::getNbAmmo(){return this->nbAmmo;}
int Player::getStackSize(){return this->stackSize;}
Missile &Player::getMissile(int index) {
	return this->ammo[index];
}
vector<Missile> &Player::getAmmo() {
	return this->ammo;
}

void Player::setNbAmmo(int n){
	this->nbAmmo = n;
}
void Player::setStackSize(int stackSize){
	this->stackSize = stackSize;
}
void Player::setMissileTexture(int missileId, SDL_Texture *t){
	this->ammo[missileId].setTexture(t);
}
void Player::setAmmo(vector<Missile> &mVector){
	this->nbAmmo = mVector.size();
	this->stackSize = mVector.size();
	this->ammo = mVector;
	for(Missile &i : this->ammo){
		i.setCoo({.x=0, .y=0, .w=10, .h=10});
		i.setMaxHealth(10);
		i.setToStack();
	}
}
void Player::init(int x, int y, int speed, int ammo, int stackSize){
	this->coo.x = x;
	this->coo.y = y;
	this->speed = speed;
	this->nbAmmo = ammo;
	this->stackSize = stackSize;
}
void Player::init(){
	this->init(WIN_WIDTH/2 - WIDTH/2, WIN_HEIGHT - 1.5*HEIGHT, SPEED, 1, 1); //1, 1 are random
}
void Player::init(SDL_Texture *missileTexture){
	this->init(WIN_WIDTH/2 - WIDTH/2, WIN_HEIGHT - 1.5*HEIGHT, SPEED, 3, 3);//3, 3 are random
}

/**
 * Shoots the first available ammo
 */
void Player::shoot(){
		for(Missile &i : this->ammo){
			if(i.isReady()){
				//We set the next ammo in front of the ship and let it go
				i.launch(this->coo.x + this->coo.w/2 - 2, this->coo.y);
				break;
			}
		}
}

void Player::updateAmmos(){
	for(Missile &i : this->ammo){
		//If the ammo is launched or waiting in the stack
		if(!i.isReady()){
			i.move();
		}
	}
}

void Player::renderShip(SDL_Renderer *r){
	SDL_RenderCopy(r, this->texture, NULL, &(this->coo));
	for(Missile &i : this->ammo){
		if(!i.isReady()){
			i.renderShip(r);
		}
	}
}

/**
 * returns the index of colliding missile, -1 of no collision
 */
int Player::missileCollidesWith(SDL_Rect target){
	int count{0};
	for(Missile &i : this->ammo){
		if(i.hitShip(target))
			return count;
		count++;
	}
	return -1;
}
void Player::restackMissile(int index){
	this->ammo[index].setToStack();
}
void Player::damageMissile(int index, int damage){
	this->ammo[index].takeDamage(damage);
}
void Player::takeDamage(int d){
	this->health-= d;
}

ostream& operator<<(ostream& out, Player &p){
	out << "coo.x = " << p.getCoo().x << ", coo.y = " << p.getCoo().y << ", coo.w = " << p.getCoo().w << ", coo.h = " << p.getCoo().h << ", speed = " << p.getSpeed() << endl << ", nbAmmos = " << p.getNbAmmo() << ", stackSize = " << p.getStackSize() << endl ;
	return out;
}