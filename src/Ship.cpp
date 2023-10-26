#include "Ship.hpp"

Ship::Ship():id{"ship"}, cooVect{Vect(0, 0)}, speedVect{Vect(0, 0)}, coo({.x = 0, .y = 0, .w = WIDTH, .h = HEIGHT}), hitbox({.x = 0, .y = 0, .w = WIDTH, .h = HEIGHT}), speed{SPEED}, health{1}, maxHealth{1}, atk{1}, hitboxRatio{1.0}, frame{1}, invincible{0}, nbFramesInvincible{0}, stayInScreen{false}{
}

Ship::Ship(int x, int y, string id){
	this->id = id;
	this->coo.x = x;
	this->coo.y = y;
	this->coo.w = WIDTH;
	this->coo.h = HEIGHT;
	this->hitbox = this->coo;
	this->hitboxRatio = 1.0;
	this->speed = SPEED;
}
Ship::Ship(SDL_Rect coo, float speed):coo{coo}, hitbox{coo}, speed{speed}, hitboxRatio{100}{
}

string Ship::getId(){
	return this->id;
}
SDL_Rect Ship::getCoo(){
	return this->coo;
}
Vect& Ship::getCooVect() const{
	Vect *v = new Vect();
	v->setX(this->cooVect.getX());
	v->setY(this->cooVect.getY());
	return *v;
}
Vect& Ship::getSpeedVect() const{
	Vect *v = new Vect();
	v->setX(this->speedVect.getX());
	v->setY(this->speedVect.getY());
	return *v;
}
SDL_Rect Ship::getHitbox(){
	return this->hitbox;
}
int Ship::getX(){
	return this->coo.x;
}
int Ship::getY(){
	return this->coo.y;
}
int Ship::getW(){
	return this->coo.w;
}
int Ship::getH(){
	return this->coo.h;
}
float Ship::getSpeed(){
	return this->speed;
}
int Ship::getHealth(){
	return this->health;
}
int Ship::getMaxHealth(){
	return this->maxHealth;
}
int Ship::getAtk(){
	return this->atk;
}
int Ship::getStrength(){
	return this->strength;
}
float Ship::getXSpeed(){
	return this->speedVect.getX();
}
float Ship::getYSpeed(){
	return this->speedVect.getY();
}
int Ship::getInvincible(){
	return this->invincible;
}

int Ship::getCurrentFrame(){
	return this->frame;
}
int Ship::getCurrentFrameAndIncrease(){
	this->frame++;
	if(this->frame >= 10000)//Frame must stay between 1 and 9999
		this->frame = 1;
	return this->frame - 1;
}

void Ship::setCoo(SDL_Rect n){
	this->coo = n;
}
void Ship::setCooVect(float x, float y){
	this->cooVect.setX(x);
	this->cooVect.setY(y);
}
void Ship::setSpeedVect(float x, float y){
	this->speedVect.setX(x);
	this->speedVect.setY(y);
}
void Ship::setHitbox(SDL_Rect b){
	this->hitbox = b;
}
void Ship::setX(int x){
	this->coo.x = x;
}
void Ship::setY(int y){
	this->coo.y = y;
}
void Ship::setW(int w){
	this->coo.w = w;
}
void Ship::setH(int h){
	this->coo.h = h;
}
void Ship::setSpeed(float s){
	this->speed = s;
}
void Ship::setXSpeed(const float x){
	this->speedVect.setX(x);
}
void Ship::setYSpeed(const float y){
	this->speedVect.setY(y);
}
void Ship::setHealth(int h){
	this->health = h;
}
void Ship::setMaxHealth(int m){
	this->maxHealth = m;
}
void Ship::setHitboxRatio(float hr){
	this->hitboxRatio = hr;
}
void Ship::setAtk(int a){
	this->atk = a;
}
void Ship::setStrength(int s){
	this->strength = s;
}
void Ship::setInvincible(int i){
	this->invincible = i;
}
void Ship::setStayInScreen(bool b){
	this->stayInScreen = b;
}

void Ship::init(){}

void Ship::goLeft(){
	this->coo.x-= this->speed;
}

void Ship::goRight(){
	this->coo.x+= this->speed;
}
void Ship::goUp(){
	this->coo.y-= this->speed;
}
void Ship::goDown(){
	this->coo.y+= this->speed;
}
void Ship::move(){}
void Ship::translationMovement(){
	this->cooVect = this->cooVect+this->speedVect;
	this->synchronizeCooFromVect();
	//We control if the ship must stay inside the screen or not
	if(this->stayInScreen){
		if(this->coo.x + coo.w > WIN_WIDTH){
			this->coo.x = WIN_WIDTH - this->coo.w;
			this->cooVect.setX(this->coo.x);
		}
		else if(this->coo.x < 0){
			this->coo.x = 0;
			this->cooVect.setX(this->coo.x);
		}
	}
}
void Ship::synchronizeCooFromVect(){
	this->coo.x = static_cast<int>(this->cooVect.getX());
	this->coo.y = static_cast<int>(this->cooVect.getY());
}
void Ship::synchronizeVectFromCoo(){
	this->cooVect.setX(this->coo.x);
	this->cooVect.setY(this->coo.y);
}

bool Ship::hitShip(SDL_Rect s){
	SDL_Rect r;
	return SDL_IntersectRect(&(this->hitbox), &s, &r) == SDL_TRUE;
}

void Ship::heal(){
	if(this->health < this->maxHealth){
		this->health++;
	}
}
void Ship::heal(int a){
	if(this->health + a > this->maxHealth){
		this->healCompletely();
	} else {
		this->health+= a;
	}
}
void Ship::healCompletely(){
	this->health = this->maxHealth;
}
bool Ship::takeDamage(){
	this->health--;
	if(this->health <= 0)
		return true;
	return false;
}
bool Ship::takeDamage(int d){
	this->health-= d;
	if(this->health <= 0)
		return true;
	return false;
}

/**
 * This function moves the hitbox to the right place
 */
void Ship::updateHitbox(){
	this->hitbox.w = (int) (this->hitboxRatio * this->coo.w);
	this->hitbox.h = (int) (this->hitboxRatio * this->coo.h);
	this->hitbox.x = this->coo.x + this->coo.w/2 - this->hitbox.w/2;
	this->hitbox.y = this->coo.y + this->coo.h/2 - this->hitbox.h/2;
}

void Ship::doActions(vector<Ship*>& v){
	this->move();
}

void Ship::rerack(){
	this->healCompletely();
	this->setY(-this->coo.h);
	this->synchronizeVectFromCoo();
}
void Ship::launch(int startX, int startY){
}
void Ship::launch(int startX, int startY, Vect dir){
}
void Ship::launch(int startX, int startY, string launcherId){
}
void Ship::launch(int startX, int startY, string launcherId, int atk){
}

/**
 * starts the counter of the ship to make it scintillate in the renderer
 */
void Ship::scintillate(int nbFrames){
	if(this->invincible == 0)
		this->invincible = 1;
	
	this->nbFramesInvincible = nbFrames;
}
void Ship::scintillate(){
	this->scintillate(120); //during two seconds
}

Ship::~Ship(){
}

ostream& operator<<(ostream& out, Ship &s){
	out << "coo.x = " << s.getCoo().x << ", coo.y = " << s.getCoo().y << ", coo.w = " << s.getCoo().w << ", coo.h = " << s.getCoo().h << ", speed = " << s.getSpeed() << "health = " << s.getHealth() << "/" << s.getMaxHealth();
	return out;
}
