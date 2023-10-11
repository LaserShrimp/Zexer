#include "Player.hpp"

Player::Player():Ship{}, nbAmmo{0}, stackSize{0}, ammo{vector<Missile*>{}}, mvState{STATIONNARY}, shootCooldown{225}, startShootCooldown{0}{}

Player::Player(const Player& p): Ship{}, nbAmmo{p.getNbAmmo()}, stackSize{p.getStackSize()}, ammo{vector<Missile*>{}}, mvState{STATIONNARY}, shootCooldown{p.shootCooldown}, startShootCooldown{0}{
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
movestate Player::getMvState() const{
	return this->mvState;
}
void Player::setNbAmmo(int n){
	this->nbAmmo = n;
}
void Player::setStackSize(int stackSize){
	this->stackSize = stackSize;
}
// void Player::setMissileTexture(int missileId, const Animation& a){
// 	this->ammo[missileId]->Ship::setAnimationNeutral(a);
// }
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
// void Player::setAnimationNeutral(SDL_Renderer *r){
// 	this->animNeutral.setFrameSize(WIDTH, HEIGHT);
// 	this->animNeutral.setNumberOfFrames(10);
// 	this->animNeutral.setTexture(r, (char*)"assets/playerShipTest.png");
// }
// void Player::setAnimationUp(SDL_Renderer *r){
// 	this->animUp.setFrameSize(WIDTH, HEIGHT);
// 	this->animUp.setNumberOfFrames(10);
// 	this->animUp.setTexture(r, (char*)"assets/playerUpTest.png");
// }
// void Player::setAnimationDown(SDL_Renderer *r){
// 	this->animDown.setFrameSize(WIDTH, HEIGHT);
// 	this->animDown.setNumberOfFrames(10);
// 	this->animDown.setTexture(r, (char*)"assets/playerDownTest.png");
// }
// void Player::setAnimationRight(SDL_Renderer *r){
// 	this->animRight.setFrameSize(WIDTH, HEIGHT);
// 	this->animRight.setNumberOfFrames(10);
// 	this->animRight.setTexture(r, (char*)"assets/playerRightTest.png");
// }
// void Player::setAnimationLeft(SDL_Renderer *r){
// 	this->animLeft.setFrameSize(WIDTH, HEIGHT);
// 	this->animLeft.setNumberOfFrames(10);
// 	this->animLeft.setTexture(r, (char*)"assets/playerLeftTest.png");
// }
void Player::init(int x, int y, int speed, int ammo, int stackSize){
	this->coo.x = x;
	this->coo.y = y;
	this->synchronizeVectFromCoo();
	this->speed = speed;
	this->nbAmmo = ammo;
	this->stackSize = stackSize;
}
// void Player::init(){
// 	this->init(WIN_WIDTH/2 - WIDTH/2, WIN_HEIGHT - 1.5*HEIGHT, SPEED, 1, 1); //1, 1 are random
// }
// void Player::init(SDL_Texture *missileTexture){
// 	this->init(WIN_WIDTH/2 - WIDTH/2, WIN_HEIGHT - 1.5*HEIGHT, SPEED, 3, 3);//3, 3 are random
// }
void Player::init(/*SDL_Renderer *r*/){
	this->init(WIN_WIDTH/2 - WIDTH/2, WIN_HEIGHT - 1.5*HEIGHT, SPEED, 1, 1); //1, 1 are random
	this->id = "player";
// 	this->setAnimationUp(r);
// 	this->setAnimationDown(r);
// 	this->setAnimationRight(r);
// 	this->setAnimationLeft(r);
// 	this->setAnimationNeutral(r);
	
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
		for(Missile* i : this->ammo){
			if(i->isReady()){
				//We set the next ammo in front of the ship and let it go
				i->launch(this->coo.x + this->coo.w/2 - 2, this->coo.y);
				break;
			}
		}
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

// void Player::renderShip(SDL_Renderer *r){
// 	//	changing the alpha if it took damages
// 	if(this->invincible > 0){
// 		this->changeAlpha(rand()%255);
// 		this->invincible++;
// 		if(this->invincible == this->nbFramesInvincible)
// 			this->invincible = 0;
// 	} else {
// 		this->resetAlpha();
// 	}
// 	switch(this->mvState){
// 		case STATIONNARY:
// 			this->animNeutral.renderImage(r, this->coo);
// 			this->animNeutral.nextFrame();
// 			break;
// 			
// 		case UP:
// 		case UPRIGHT:
// 		case UPLEFT:
// 			this->animUp.renderImage(r, this->coo);
// 			this->animUp.nextFrame();
// 			break;
// 		case DOWN:
// 			this->animDown.renderImage(r, this->coo);
// 			this->animDown.nextFrame();
// 			break;
// 		case LEFT:
// 		case DOWNLEFT:
// 			this->animLeft.renderImage(r, this->coo);
// 			this->animLeft.nextFrame();
// 			break;
// 		case RIGHT:
// 		case DOWNRIGHT:
// 			this->animRight.renderImage(r, this->coo);
// 			this->animRight.nextFrame();
// 			break;
// 		default:
// 			this->animNeutral.renderImage(r, this->coo);
// 			this->animNeutral.nextFrame();
// 			break;
// 	}
// // 	for(Missile* i : this->ammo){
// // 		if(!i->isReady()){
// // 			i->renderShip(r);
// // 		}
// // 	}
// }

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

// void Player::changeAlpha(int alpha){
// 	this->animUp.changeAlpha(rand()%255);
// 	this->animDown.changeAlpha(rand()%255);
// 	this->animRight.changeAlpha(rand()%255);
// 	this->animLeft.changeAlpha(rand()%255);
// 	this->animNeutral.changeAlpha(rand()%255);
// }
// 
// void Player::resetAlpha(){
// 	this->animUp.resetAlpha();
// 	this->animDown.resetAlpha();
// 	this->animRight.resetAlpha();
// 	this->animNeutral.resetAlpha();
// 	this->animLeft.resetAlpha();
// }

ostream& operator<<(ostream& out, Player &p){
	out << "health = " << p.getHealth() << ", maxHealth = " << p.getMaxHealth() << endl << ", nbAmmos = " << p.getNbAmmo() << ", stackSize = " << p.getStackSize() << endl ;
	return out;
}
