#include "Unit1.hpp"

//UNIT1
Unit1::Unit1():shootCooldown{200}, shCurr{0}, moveCooldown{30}, staticCooldown{120}{
	
}

void Unit1::init(){
	this->id = "unit1";
	shCurr = 0;
	mCurr = 0;
	stCurr = 0;
	this->speed = 10.5;
	this->speedVect.setY(U1_YSPEED);
	this->speedVect.setX(U1_XSPEED);
	this->coo.x = rand()%WIN_WIDTH;
	this->coo.y = -50;
	this->coo.w = 50;
	this->coo.h = 50;
	this->setHitboxRatio(1.0);
	this->synchronizeVectFromCoo();
	this->setStayInScreen(true);
	
	this->setMaxHealth(75);
	this->healCompletely();
	this->atk = 10;
	this->strength = 10;
	this->invincible = 0;
	this->areaLimit = rand()%U1_LIMIT_MAX;
	this->hasLanded = false;
}

void Unit1::move(){
	if(this->coo.y >= this->areaLimit && !this->hasLanded){
		this->speedVect.setY(0);
		this->hasLanded = true;
	} else {
		if(this->stCurr == this->staticCooldown){
			this->randomDir();
			this->stCurr = -1;
			this->mCurr = 0;
		}
		else if(this->mCurr >= 0){
			this->mCurr++;
			if(this->moveCooldown == this->mCurr){
				this->mCurr = -1;
				this->stCurr = 0;
				this->speedVect.setX(0);
			}
		} else if(this->stCurr >= 0){
			this->stCurr++;
		}
	}
	
	this->translationMovement();
	this->updateHitbox();
}

void Unit1::doActions(vector<Ship*>& v){
	this->move();
	//shoot
	if(this->shCurr == 1 && this->coo.y >= 0){ //shoot if the cooldown is finished AND the ship is on screen
		this->shoot(v);
	}
	this->shCurr++;
	this->shCurr = this->shCurr%this->shootCooldown;
}

void Unit1::shoot(vector<Ship*>& v){
	v.push_back(new Missile());
	v.back()->setStrength(this->atk);
	v.back()->launch(this->getX() + this->getW()/2 - v.back()->getW()/2, this->getY(), "unit1");
}

/**
 * set a random direction on x axis
 */
void Unit1::randomDir(){
	if(rand()%3 < 2)// 2/3 chances to change the direction
		this->speed = this->speed * (-1);
	this->speedVect.setX(speed);
}

Unit1::~Unit1(){
// 	cout << "unit1 deleted" << endl;
}


//UNITOMNI

UnitOmni::UnitOmni():shootCooldown{120}, shCurr{0}{
	
}

void UnitOmni::init(){
	this->id = "unitOmni";
	shCurr = 0;
	this->speed = 10.5;
	this->speedVect.setY(0.6);
	this->speedVect.setX(0);
	this->coo.x = rand()%WIN_WIDTH;
	this->coo.y = -50;
	this->coo.w = 50;
	this->coo.h = 50;
	this->setHitboxRatio(1.0);
	this->synchronizeVectFromCoo();
	this->setStayInScreen(true);
	
	this->setMaxHealth(100);
	this->healCompletely();
	this->atk = 10;
	this->strength = 15;
	this->invincible = 0;
}

void UnitOmni::doActions(vector<Ship*>& v){
	this->move();
	//shoot
	if(this->shCurr == 1 && this->coo.y >= 0){ //shoot if the cooldown is finished AND the ship is on screen
		this->shoot(v);
	}
	this->shCurr++;
	this->shCurr = this->shCurr%this->shootCooldown;
}

void UnitOmni::shoot(vector<Ship*>& v){
	this->move();
	for(float i = 0.0; i < 12.0; i+= 1.0){
		v.push_back(new Missile());
		v.back()->setStrength(this->atk);
		Vect mDir(double((cos((i/12.0)*2*std::numbers::pi) * MISSILE_SPEED)), double((sin((i/12.0)*2*std::numbers::pi)* MISSILE_SPEED)));
		v.back()->launch(this->getX() + this->getW()/2 - v.back()->getW()/2, this->getY(), mDir);
	}
}

void UnitOmni::move(){
	this->translationMovement();
	this->updateHitbox();
}

UnitOmni::~UnitOmni(){
	
}
