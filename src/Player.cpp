#include "Player.hpp"

Player::Player():Ship{}, mvState{STATIONNARY}, shootCooldown{200}, startShootCooldown{0}, launchMissile{false}{}

Player::Player(const Player& p): Ship{}, mvState{STATIONNARY}, shootCooldown{p.shootCooldown}, startShootCooldown{0}, launchMissile{false}{
}

Uint32 Player::getShootCooldown() const {return this->shootCooldown;}
Uint32 Player::getStartShootCooldown() const {return this->startShootCooldown;}
bool Player::isShooting() const{
	return launchMissile;
}
movestate Player::getMvState() const{
	return this->mvState;
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
	this->setAtk(10);
	this->setStrength(1);
	
	this->invincible = 0;
}

/**
 * Shoots the first available ammo
 */
void Player::shoot(vector<Ship*> &v){
	if(SDL_GetTicks() - this->startShootCooldown >= this->shootCooldown){
		v.push_back(new Missile());
		v.back()->setStrength(this->atk);
		v.back()->launch(this->getX() + this->getW()/2 - v.back()->getW()/2, this->getY(), "player");
		this->startShootCooldown = SDL_GetTicks();
	}
}

void Player::move(){
	switch(this->mvState){
		case RIGHT:
			if(this->coo.x+this->coo.w < WIN_WIDTH){
				this->setXSpeed(this->speed);
				if(this->coo.y + this->coo.h < WIN_HEIGHT)
					this->setYSpeed(DRAW);
				else
					this->setYSpeed(0);
				} else {
					this->setXSpeed(0);
			}
			break;
		case LEFT:
			if(this->coo.x > 0){
				this->setXSpeed(-this->speed);
				if(this->coo.y + this->coo.h < WIN_HEIGHT)
					this->setYSpeed(DRAW);
				else
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
			if(this->coo.y + this->coo.h < WIN_HEIGHT)
				this->setYSpeed(DRAW);
			else
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
void Player::doActions(const InputState &is, vector<Ship*> &v){
	this->setMoveState(is);
	this->move();
	this->updateHitbox();
	if(is.getspacebar()){
		this->shoot(v);
	}
}

bool Player::takeDamage(int d){
	if(this->invincible == 0){
		this->health-= d;
		this->scintillate(60);
	}
	if(this->health <= 0) {
		health = 0;
	}
		return true;
	return false;
}

/**
 * This function decides what to do when the player gathers an item (returns true if the item is touched, false otherwise)
 */
bool Player::gatherItem(Item& i){
	string t = i.getType();
	if(this->hitShip(i.getCoo())){
		if(t == "itemAtkUp"){
			this->atk+=10;
			i.setHealth(0);
		} else if(t == "itemHeal"){
			this->heal(15);
			i.setHealth(0);
		}
		return true;
	}
	
	return false;
}

Player::~Player(){
// 	cout << "player deleted" << endl;
}

ostream& operator<<(ostream& out, Player &p){
	out << "health = " << p.getHealth() << ", maxHealth = " << p.getMaxHealth() << endl ;
	return out;
}
