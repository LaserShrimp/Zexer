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
	this->readyToDelete = false;
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
	if(this->shCurr == this->shootCooldown - 1 && this->coo.y >= 0){ //shoot if the cooldown is finished AND the ship is on screen
		this->shoot(v);
	}
	this->shCurr++;
	this->shCurr = this->shCurr%this->shootCooldown;
}
void Unit1::doActions(vector<Ship*>& v, Ship& p){
	this->doActions(v);
}
void Unit1::doActions(vector<Ship*>& v, vector<Item*>& vi, vector<Particle*>& vp, Ship& p){
	this->doActions(v);
	if(!this->isOnGameArea() || this->health <= 0){
		vp.push_back(new Particle("explosion1", this->getCoo().x, this->getCoo().y, this->getCoo().w, this->getCoo().h));
 		vi.push_back(new Item("itemHeal", this-> getCoo().x + this->getCoo().w/2 - 10, this->getCoo().y + this->getCoo().h/2 - 10));
		this->readyToDelete = true;
	}
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
	this->atk = 30;
	this->strength = 15;
	this->invincible = 0;
	this->readyToDelete = false;
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
void UnitOmni::doActions(vector<Ship*>& v, Ship& p){
	this->doActions(v);
}
void UnitOmni::doActions(vector<Ship*>& v, vector<Item*>& vi, vector<Particle*>& vp, Ship& p){
	this->doActions(v);
	if(!this->isOnGameArea() || this->health <= 0){
		vp.push_back(new Particle("explosion1", this->getCoo().x, this->getCoo().y, this->getCoo().w, this->getCoo().h));
		this->readyToDelete = true;
	}
}

void UnitOmni::shoot(vector<Ship*>& v){
// 	this->move();
	for(float i = 0.0; i < 12.0; i+= 1.0){
		Missile *n = new Missile();
		n->setStrength(this->atk);
		Vect mDir(double((cos((i/12.0)*2*std::numbers::pi) * MISSILE_SPEED/4.0)), double((sin((i/12.0)*2*std::numbers::pi)* MISSILE_SPEED/4.0)));
		n->launch(this->getX() + this->getW()/2 - n->getW()/2, this->getY() + this->getH()/2 - n->getH()/2, mDir);
		v.push_back(n);
// 		cout << "missile loaded by omni" << endl;
	}
}

void UnitOmni::move(){
	this->translationMovement();
	this->updateHitbox();
}

UnitOmni::~UnitOmni(){
// 	cout << "UnitOmni destroyed" << endl;
}

//UNITTRACKER

UnitTracker::UnitTracker(){
	
}

void UnitTracker::init(){
	this->id = "unitTracker";
	this->speed = 2.75;
	this->speedVect.setY(0.6);
	this->speedVect.setX(0);
	this->coo.x = rand()%WIN_WIDTH;
	this->coo.y = -50;
	this->coo.w = 30;
	this->coo.h = 30;
	this->setHitboxRatio(1.0);
	this->synchronizeVectFromCoo();
	this->setStayInScreen(true);
	
	this->setMaxHealth(40);
	this->healCompletely();
	this->atk = 0;
	this->strength = 45;
	this->invincible = 0;
	this->readyToDelete = false;
}

void UnitTracker::doActions(vector<Ship*>& v, Ship& p){
	this->move(p.getCooVect());
}
void UnitTracker::doActions(vector<Ship*>& v, vector<Item*>& vi, vector<Particle*>& vp, Ship& p){
	this->doActions(v, p);
	if(!this->isOnGameArea() || this->health <= 0){
		vp.push_back(new Particle("explosion1", this->getCoo().x, this->getCoo().y, this->getCoo().w, this->getCoo().h));
		if(rand()%10 == 0){
			vi.push_back(new Item("itemHeal", this-> getCoo().x, this->getCoo().y));
		}
		this->readyToDelete = true;
	}
}

void UnitTracker::move(Vect& target){
	this->setXSpeed(target.getX() - this->cooVect.getX());
	this->setYSpeed(target.getY() - this->cooVect.getY());
	this->speedVect.divideBy(this->speedVect.norm());
	this->speedVect.multiplyBy(this->speed);
	
	this->translationMovement();
	this->updateHitbox();
}

UnitTracker::~UnitTracker(){
// 	cout << "UnitOmni destroyed" << endl;
}

//UNITDESTROYER

UnitDestroyer::UnitDestroyer(){
	
}

void UnitDestroyer::init(){
	this->id = "unitDestroyer";
	this->speed = 2.75;
	this->speedVect.setY(0.6);
	this->speedVect.setX(0);
	this->coo.x = rand()%WIN_WIDTH;
	this->coo.y = -50;
	this->coo.w = 100;
	this->coo.h = 150;
	this->setHitboxRatio(1.0);
	this->synchronizeVectFromCoo();
	this->setStayInScreen(true);
	
	this->setMaxHealth(500);
	this->healCompletely();
	this->atk = 0;
	this->strength = 60;
	this->invincible = 0;
	
	this->landmark = rand()%200;
	this->shootCooldown = FPS * 5;
	this->shCurr = 0;
	this->readyToDelete = false;
}

void UnitDestroyer::doActions(vector<Ship*>& v, Ship& p){
	this->move(p.getCooVect());
	if(this->shCurr == 1 && this->coo.y >= 0){ //shoot if the cooldown is finished AND the ship is on screen
		this->shoot(v);
	}
	this->shCurr++;
	this->shCurr = this->shCurr%this->shootCooldown;
}
void UnitDestroyer::doActions(vector<Ship*>& v, vector<Item*>& vi, vector<Particle*>& vp, Ship& p){
	this->move(p.getCooVect());
	if(this->shCurr == 1 && this->coo.y >= 0){ //shoot if the cooldown is finished AND the ship is on screen
		this->shoot(v);
		vp.push_back(new Particle("smoke2", this->getX() - 30, this->getY(), 20, 20));
		vp.push_back(new Particle("smoke2", this->getX() + this->getW(), this->getY(), 20, 20));
		vp.push_back(new Particle("smoke2", this->getX() - 30, this->getY() + 120, 20, 20));
		vp.push_back(new Particle("smoke2", this->getX() + this->getW(), this->getY() + 120, 20, 20));
		vp.push_back(new Particle("smoke2", this->getX() + this->getW()/2 - 25, this->getY() + this->getH(), 50, 50));
	}
	this->shCurr++;
	this->shCurr = this->shCurr%this->shootCooldown;
	
	if(!this->isOnGameArea() || this->health <= 0){
		vi.push_back(new Item("itemHeal", this->getCoo().x, this->getCoo().y + 75));
		vi.push_back(new Item("itemHeal", this->getCoo().x, this->getCoo().y + 40));
		vi.push_back(new Item("itemAtkUp", this->getCoo().x + this->getCoo().w - 20, this->getCoo().y + 75));
		vp.push_back(new Particle("smoke2", this->getCoo().x, this->getCoo().y + 25, this->getCoo().w, this->getCoo().w));
		this->readyToDelete = true;
	}
}

void UnitDestroyer::move(Vect& target){
	if(this->coo.y < landmark)
		this->speedVect.setY(2.5);
	else
		this->speedVect.setY(0);
	
	this->translationMovement();
	this->updateHitbox();
}

void UnitDestroyer::shoot(vector<Ship*>& v){
	UnitTracker *n1 = new UnitTracker();
	UnitTracker *n2 = new UnitTracker();
	UnitTracker *n3 = new UnitTracker();
	UnitTracker *n4 = new UnitTracker();
	n1->init();
	n1->launch(this->getX() - 30, this->getY());
	v.push_back(n1);
	n2->init();
	n2->launch(this->getX() + this->getW(), this->getY());
	v.push_back(n2);
	n3->init();
	n3->launch(this->getX() - 30, this->getY() + 120);
	v.push_back(n3);
	n4->init();
	n4->launch(this->getX() + this->getW(), this->getY() + 120);
	v.push_back(n4);
	Unit1 *u = new Unit1();
	u->init();
	u->launch(this->getX() + this->getW()/2 - u->getW()/2, this->getY() + this->getH());
	v.push_back(u);
}

UnitDestroyer::~UnitDestroyer(){
// 	cout << "UnitOmni destroyed" << endl;
}
