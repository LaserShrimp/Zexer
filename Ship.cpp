#include "Ship.hpp"

Ship::Ship(): texture{NULL}, coo({.x = 0, .y = 0, .w = WIDTH, .h = HEIGHT}), hitbox({.x = 0, .y = 0, .w = WIDTH, .h = HEIGHT}), speed{SPEED}, health{1}, maxHealth{1}, hitboxRatio{1.0}, frameNb{0}, framePos({.x = 0, .y = 0, .w = WIDTH, .h = HEIGHT}){
}

Ship::Ship(SDL_Texture *t): texture{t}, coo({0, 0, WIDTH, HEIGHT}), speed{SPEED}, health{1}, maxHealth{1}, hitboxRatio{1.0}, frameNb{0}, framePos({.x = 0, .y = 0, .w = WIDTH, .h = HEIGHT}){
}
Ship::Ship(SDL_Texture *t, int x, int y){
	this->texture = t;
	this->coo.x = x;
	this->coo.y = y;
	this->coo.w = WIDTH;
	this->coo.h = HEIGHT;
	this->hitbox = this->coo;
	this->hitboxRatio = 1.0;
	this->speed = SPEED;
	this->framePos.x = 0;
	this->framePos.y = 0;
	this->framePos.w = WIDTH;
	this->framePos.h = HEIGHT;
}
Ship::Ship(SDL_Texture *t, SDL_Rect coo, int speed):texture{t}, coo{coo}, hitbox{coo}, speed{speed}, hitboxRatio{100}{
}

SDL_Texture *Ship::getTexture(){
	return this->texture;
}
SDL_Rect Ship::getCoo(){
	return this->coo;
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
int Ship::getSpeed(){
	return this->speed;
}
int Ship::getHealth(){
	return this->health;
}
int Ship::getMaxHealth(){
	return this->maxHealth;
}

void Ship::setTexture(SDL_Texture *t){
	this->texture = t;
}
void Ship::setCoo(SDL_Rect n){
	this->coo = n;
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
void Ship::setSpeed(int s){
	this->speed = s;
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

void Ship::renderShip(SDL_Renderer *r){
	if(this->texture == NULL){cout << "NULL texture..." << endl;}
	
	SDL_RenderCopy(r, this->texture, NULL, &(this->coo));
}

bool Ship::hitShip(SDL_Rect s){
	SDL_Rect r;
	return SDL_IntersectRect(&(this->hitbox), &s, &r) == SDL_TRUE;
}

void Ship::heal(){
	this->health++;
}
void Ship::heal(int a){
	this->health+= a;
}
void Ship::healCompletely(){
	this->health = this->maxHealth;
}
void Ship::takeDamage(){
	this->health--;
}
void Ship::takeDamage(int d){
	this->health-= d;
	cout << "Ship takes damage " << endl;
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

void Ship::rerack(){
	this->healCompletely();
}

Ship::~Ship(){
	if(this->texture != NULL){
		SDL_DestroyTexture(this->texture);
	}
}

ostream& operator<<(ostream& out, Ship &s){
	out << "coo.x = " << s.getCoo().x << ", coo.y = " << s.getCoo().y << ", coo.w = " << s.getCoo().w << ", coo.h = " << s.getCoo().h << ", speed = " << s.getSpeed();
	return out;
}
