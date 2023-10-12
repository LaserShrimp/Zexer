#include "Player.hpp"

Player::Player():Ship{}, nbAmmo{0}, stackSize{0}, ammo{vector<Missile*>{}}, mvState{STATIONNARY}, shootCooldown{/*225*/200}, startShootCooldown{0}, launchMissile{false}{}

Player::Player(const Player& p): Ship{}, nbAmmo{p.getNbAmmo()}, stackSize{p.getStackSize()}, ammo{vector<Missile*>{}}, mvState{STATIONNARY}, shootCooldown{p.shootCooldown}, startShootCooldown{0}, launchMissile{false}{
}

Player::~Player(){
}

int Player::getNbAmmo() const {return this->nbAmmo;}
int Player::getStackSize() const {return this->stackSize;}
Uint32 Player::getShootCooldown() const {return this->shootCooldown;}
Uint32 Player::getStartShootCooldown() const {return this->startShootCooldown;}
Missile* Player::getMissile (int index) {
	return this->ammo[index];
}
vector<Missile*> &Player::getAmmo() {
	return this->ammo;
}
bool Player::isShooting() const{
	return launchMissile;
}
movestate Player::getMvState() const{
	return this->mvState;
}
void Player::setNbAmmo(int n){
	this->nbAmmo = n;
}
void Player::setStackSize(int stackSize){
	this->stackSize = stackSize;
}

void Player::setAmmo(vector<Missile*> &mVector){
	this->nbAmmo = mVector.size();
	this->stackSize = mVector.size();
	this->ammo = mVector;
	for(Missile* i : this->ammo){
		i->setCoo({.x=0, .y=0, .w=10, .h=10});
		i->setMaxHealth(10);
		i->setToStack();
	}
}
void Player::setShootCooldown(Uint32 cooldown){
	this->shootCooldown = cooldown;
}
void Player::setStartShootCooldown(){
	this->startShootCooldown = SDL_GetTicks();
}
void Player::init(int x, int y, int speed, int ammo, int stackSize){
	this->coo.x = x;
	this->coo.y = y;
	this->synchronizeVectFromCoo();
	this->speed = speed;
	this->nbAmmo = ammo;
	this->stackSize = stackSize;
}
void Player::init(){
	this->init(WIN_WIDTH/2 - WIDTH/2, WIN_HEIGHT - 1.5*HEIGHT, SPEED, 1, 1); //1, 1 are random
	this->id = "player";
	
	this->setW(75);
	this->setH(75);
	this->setHitboxRatio(.5);
	this->updateHitbox();
	this->setMaxHealth(100);
	this->healCompletely();
	this->setAtk(1);
	
	this->invincible = 0;
}

/**
 * Shoots the first available ammo
 */
void Player::shoot(){
	if(SDL_GetTicks() - this->startShootCooldown >= this->shootCooldown){
// 		for(Missile* i : this->ammo){
// 			if(i->isReady()){
// 				//We set the next ammo in front of the ship and let it go
// 				i->launch(this->coo.x + this->coo.w/2 - 2, this->coo.y);
// 				break;
// 			}
// 		}
		this->launchMissile = true;
		this->startShootCooldown = SDL_GetTicks();
	}
}

void Player::move(){
	switch(this->mvState){
		case RIGHT:
			if(this->coo.x+this->coo.w < WIN_WIDTH){
				this->setXSpeed(this->speed);
				this->setYSpeed(0);
			} else {
				this->setXSpeed(0);
			}
			break;
		case LEFT:
			if(this->coo.x > 0){
				this->setXSpeed(-this->speed);
				this->setYSpeed(0);
			} else {
				this->setXSpeed(0);
			}
			break;
		case UP:
			if(this->coo.y > 0){
				this->setXSpeed(0);
				this->setYSpeed(-this->speed);
			} else {
				this->setYSpeed(0);
			}
			break;
		case DOWN:
			if(this->coo.y+this->coo.h < WIN_HEIGHT){
				this->setXSpeed(0);
				this->setYSpeed(this->speed);
			} else {
				this->setYSpeed(0);
			}
			break;
		case UPRIGHT:
			if(this->coo.y > 0)
				this->setYSpeed(-this->speed);
			else {
				this->setYSpeed(0);
			}
			if(this->coo.x+this->coo.w < WIN_WIDTH)
				this->setXSpeed(this->speed);
			else {
				this->setXSpeed(0);
			}
			break;
		case UPLEFT:
			if(this->coo.y > 0)
				this->setYSpeed(-this->speed);
			else {
				this->setYSpeed(0);
			}
			if(this->coo.x > 0)
				this->setXSpeed(-this->speed);
			else {
				this->setXSpeed(0);
			}
			break;
		case DOWNRIGHT:
			if(this->coo.y+this->coo.h < WIN_HEIGHT)
				this->setYSpeed(this->speed);
			else {
				this->setYSpeed(0);
			}
			if(this->coo.x+this->coo.w < WIN_WIDTH)
				this->setXSpeed(this->speed);
			else {
				this->setXSpeed(0);
			}
			break;
		case DOWNLEFT:
			if(this->coo.y+this->coo.h < WIN_HEIGHT)
				this->setYSpeed(this->speed);
			else {
				this->setYSpeed(0);
			}
			if(this->coo.x > 0)
				this->setXSpeed(-this->speed);
			else {
				this->setXSpeed(0);
			}
			break;
		case STATIONNARY:
			this->setXSpeed(0);
			this->setYSpeed(0);
			break;
		default:
			break;
	}
	this->translationMovement();
}

void Player::setMoveState(const InputState &is){
	if(is.getq()||is.getleft()){
		if(is.getz()||is.getup()){
			this->mvState = UPLEFT;
		}
		else if(is.gets()||is.getdown()){
			this->mvState = DOWNLEFT;
		}
		else{
			this->mvState = LEFT;
		}
	}
	else if(is.getd()||is.getright()){
		if(is.getz()||is.getup()){
			this->mvState = UPRIGHT;
		}
		else if(is.gets()||is.getdown()){
			this->mvState = DOWNRIGHT;
		}
		else{
			this->mvState = RIGHT;
		}
	}
	else if(is.getz()||is.getup()){
		this->mvState = UP;
	}
	else if(is.gets()||is.getdown()){
		this->mvState = DOWN;
	}
	else{
		this->mvState = STATIONNARY;
	}
}

void Player::setLaunchingState(bool a){
	this->launchMissile = a;
}

/**
 * This method will allow the player to do everything he is meant to do (move, shoot, etc...)
 */
void Player::doActions(const InputState &is){
	this->setMoveState(is);
	this->move();
	this->updateHitbox();
	if(is.getspacebar()){
		this->shoot();
	}
}

void Player::updateAmmos(){
	int count = 0;
	for(Missile* i : this->ammo){
		//If the ammo is launched or waiting in the stack
		if(!i->isReady()){
			i->move();
		} else {
			count++;
		}
	}
	this->nbAmmo = count;
}

/**
 * returns the index of colliding missile, -1 of no collision
 */
int Player::missileCollidesWith(SDL_Rect target){
	int count{0};
	for(Missile* i : this->ammo){
		if(i->hitShip(target))
			return count;
		count++;
	}
	return -1;
}
void Player::restackMissile(int index){
	this->ammo[index]->setToStack();
}
void Player::damageMissile(int index, int damage){
	this->ammo[index]->takeDamage(damage);
}
bool Player::takeDamage(int d){
	if(this->invincible == 0){
		this->health-= d;
		this->scintillate(60);
	}
	if(this->health <= 0)
		return true;
	return false;
}

ostream& operator<<(ostream& out, Player &p){
	out << "health = " << p.getHealth() << ", maxHealth = " << p.getMaxHealth() << endl << ", nbAmmos = " << p.getNbAmmo() << ", stackSize = " << p.getStackSize() << endl ;
	return out;
}
