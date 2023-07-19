#include "Ship.hpp"

Ship::Ship(): texture{NULL}, coo({.x = 0, .y = 0, .w = WIDTH, .h = HEIGHT}), speed{SPEED}, health{1}, maxHealth{1}{
}

Ship::Ship(SDL_Texture *t): texture{t}, coo({0, 0, WIDTH, HEIGHT}), speed{SPEED}, health{1}, maxHealth{1}{
}
Ship::Ship(SDL_Texture *t, int x, int y){
	this->texture = t;
	this->coo.x = x;
	this->coo.y = y;
	this->coo.w = WIDTH;
	this->coo.h = HEIGHT;
	this->speed = SPEED;
}
Ship::Ship(SDL_Texture *t, SDL_Rect coo, int speed):texture{t}, coo{coo}, speed{speed}{
}

SDL_Texture *Ship::getTexture(){
	return this->texture;
}
SDL_Rect Ship::getCoo(){
	return this->coo;
}
int Ship::getX(){
	return this->coo.x;
}
int Ship::getY(){
	return this->coo.y;
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
void Ship::setX(int x){
	this->coo.x = x;
}
void Ship::setY(int y){
	this->coo.y = y;
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
	return SDL_IntersectRect(&(this->coo), &s, &r) == SDL_TRUE;
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
