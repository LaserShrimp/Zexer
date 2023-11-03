#include "AnimationHandler.hpp"

AnimationHandler::AnimationHandler(SDL_Renderer *r):r{r}{
	//SHIPS
	this->vAnim.push_back(new Animation());
	this->vAnim[0]->setName("asteroid");
	this->vAnim[0]->setFrameSize(WIDTH, HEIGHT);
	this->vAnim[0]->setNumberOfFrames(12);
	this->vAnim[0]->setTexture(r, (char*)"assets/asteroidAnimation.png");
	
	this->vAnim.push_back(new Animation());
	this->vAnim[1]->setName("unit1");
	this->vAnim[1]->setFrameSize(WIDTH/2, HEIGHT/2);
	this->vAnim[1]->setNumberOfFrames(27);
	this->vAnim[1]->setTexture(r, (char*)"assets/unit1.png");
	
	this->vAnim.push_back(new Animation());
	this->vAnim[2]->setName("missile");
	this->vAnim[2]->setFrameSize(10, 10);
	this->vAnim[2]->setNumberOfFrames(6);
	this->vAnim[2]->setTexture(r, (char*)"assets/missile.png");
	
	this->vAnim.push_back(new Animation());
	this->vAnim[3]->setName("unitOmni");
	this->vAnim[3]->setFrameSize(WIDTH, HEIGHT);
	this->vAnim[3]->setNumberOfFrames(10);
	this->vAnim[3]->setTexture(r, (char*)"assets/unitOmni.png");
	
	this->vAnim.push_back(new Animation());
	this->vAnim[4]->setName("unitTracker");
	this->vAnim[4]->setFrameSize(WIDTH, HEIGHT);
	this->vAnim[4]->setNumberOfFrames(18);
	this->vAnim[4]->setTexture(r, (char*)"assets/unitTracker.png");
	
	this->vAnim.push_back(new Animation());
	this->vAnim[5]->setName("unitDestroyer");
	this->vAnim[5]->setFrameSize(WIDTH, 150);
	this->vAnim[5]->setNumberOfFrames(24);
	this->vAnim[5]->setTexture(r, (char*)"assets/unitDestroyer.png");
	
	
	//PLAYER
	this->vAnimPlayer.push_back(new Animation());
	this->vAnimPlayer[0]->setName("up");
	this->vAnimPlayer[0]->setFrameSize(WIDTH, HEIGHT);
	this->vAnimPlayer[0]->setNumberOfFrames(10);
	this->vAnimPlayer[0]->setTexture(r, (char*)"assets/playerUpTest.png");
	
	this->vAnimPlayer.push_back(new Animation());
	this->vAnimPlayer[1]->setName("down");
	this->vAnimPlayer[1]->setFrameSize(WIDTH, HEIGHT);
	this->vAnimPlayer[1]->setNumberOfFrames(10);
	this->vAnimPlayer[1]->setTexture(r, (char*)"assets/playerDownTest.png");
	
	this->vAnimPlayer.push_back(new Animation());
	this->vAnimPlayer[2]->setName("right");
	this->vAnimPlayer[2]->setFrameSize(WIDTH, HEIGHT);
	this->vAnimPlayer[2]->setNumberOfFrames(10);
	this->vAnimPlayer[2]->setTexture(r, (char*)"assets/playerRightTest.png");
	this->vAnimPlayer.push_back(new Animation());
	
	this->vAnimPlayer[3]->setName("left");
	this->vAnimPlayer[3]->setFrameSize(WIDTH, HEIGHT);
	this->vAnimPlayer[3]->setNumberOfFrames(10);
	this->vAnimPlayer[3]->setTexture(r, (char*)"assets/playerLeftTest.png");
	this->vAnimPlayer.push_back(new Animation());
	
	this->vAnimPlayer[4]->setName("neutral");
	this->vAnimPlayer[4]->setFrameSize(WIDTH, HEIGHT);
	this->vAnimPlayer[4]->setNumberOfFrames(10);
	this->vAnimPlayer[4]->setTexture(r, (char*)"assets/playerShipTest.png");
	
	//PARTICLES
	this->vAnimParticles.push_back(new Animation());
	this->vAnimParticles[0]->setName("explosion1");
	this->vAnimParticles[0]->setFrameSize(WIDTH/2, HEIGHT);
	this->vAnimParticles[0]->setNumberOfFrames(16);
	this->vAnimParticles[0]->setTexture(r, (char*)"assets/explosion1.png");
	
	this->vAnimParticles.push_back(new Animation());
	this->vAnimParticles[1]->setName("atkUp");
	this->vAnimParticles[1]->setFrameSize(WIDTH/2, HEIGHT);
	this->vAnimParticles[1]->setNumberOfFrames(15);
	this->vAnimParticles[1]->setTexture(r, (char*)"assets/atkUp.png");
	
	this->vAnimParticles.push_back(new Animation());
	this->vAnimParticles[2]->setName("smoke");
	this->vAnimParticles[2]->setFrameSize(WIDTH, HEIGHT);
	this->vAnimParticles[2]->setNumberOfFrames(7);
	this->vAnimParticles[2]->setTexture(r, (char*)"assets/smoke.png");
	
	this->vAnimParticles.push_back(new Animation());
	this->vAnimParticles[3]->setName("healing");
	this->vAnimParticles[3]->setFrameSize(WIDTH, HEIGHT);
	this->vAnimParticles[3]->setNumberOfFrames(20);
	this->vAnimParticles[3]->setTexture(r, (char*)"assets/healing.png");
	
	this->vAnimParticles.push_back(new Animation());
	this->vAnimParticles[4]->setName("smoke2");
	this->vAnimParticles[4]->setFrameSize(WIDTH, HEIGHT);
	this->vAnimParticles[4]->setNumberOfFrames(18);
	this->vAnimParticles[4]->setTexture(r, (char*)"assets/smoke2.png");
	
	this->vAnimParticles.push_back(new Animation());
	this->vAnimParticles[5]->setName("cross");
	this->vAnimParticles[5]->setFrameSize(WIDTH, HEIGHT);
	this->vAnimParticles[5]->setNumberOfFrames(17);
	this->vAnimParticles[5]->setTexture(r, (char*)"assets/cross.png");
	
	//ITEMS
	this->vAnimItems.push_back(new Animation());
	this->vAnimItems[0]->setName("itemAtkUp");
	this->vAnimItems[0]->setFrameSize(32, 32);
	this->vAnimItems[0]->setNumberOfFrames(20);
	this->vAnimItems[0]->setTexture(r, (char*)"assets/itemAtkUp.png");
	
	this->vAnimItems.push_back(new Animation());
	this->vAnimItems[1]->setName("itemHeal");
	this->vAnimItems[1]->setFrameSize(32, 32);
	this->vAnimItems[1]->setNumberOfFrames(20);
	this->vAnimItems[1]->setTexture(r, (char*)"assets/itemHeal.png");
}

void AnimationHandler::renderOnScreen(Ship &s){
	int animIndex(0);
	string n = s.getId();
	
	if(n == "asteroid")
		animIndex = 0;
	else if(n == "unit1")
		animIndex = 1;
	else if(n == "missile")
		animIndex = 2;
	else if(n == "unitOmni")
		animIndex = 3;
	else if(n == "unitTracker")
		animIndex = 4;
	else if(n == "unitDestroyer")
		animIndex = 5;
	else
		cout << "Error on AnimationHandler with Ship : id " << s.getId() << " not recognized..." << endl;
	
	if(this->vAnim[animIndex]->getTexture() == NULL){
		cout << "animTexture NULL" << endl;
	}
	if(!isOnCamera(s.getCoo()))
		return;
	//	changing the alpha if it took damages
	if(s.getInvincible() > 0){
		this->vAnim[animIndex]->changeAlpha(rand()%255);
		s.invincible++;
		if(s.invincible == s.nbFramesInvincible)
			s.invincible = 0;
	} else {
		this->vAnim[animIndex]->resetAlpha();
	}
	//set animation to current frame
	this->vAnim[animIndex]->setToFrame(s.getCurrentFrameAndIncrease());
	if(animIndex == 4){ //if it's a unitTracker
		Vect unitaire(0, 1);
		float a = s.speedVect.angle(unitaire)*(180/std::numbers::pi);
		if(s.speedVect.getX() > 0)
			a = 360 - a;
		this->vAnim[animIndex]->renderImage(this->r, s.coo, a);
	}
	else
		this->vAnim[animIndex]->renderImage(this->r, s.coo);
	//Drawing health bar only if the ship is damaged
	SDL_Rect hmcoo = s.coo;
	hmcoo.y = s.coo.y - 4;
	hmcoo.h = 4;
	SDL_Rect hcoo = hmcoo;
	hcoo.h = 2;
	hcoo.y = hmcoo.y+1;
	hcoo.w = s.health*1.0/s.maxHealth*1.0 * hmcoo.w;
	if(s.health*1.0/s.maxHealth*1.0 > 20.0/100.0){
		SDL_SetRenderDrawColor(this->r, 255, 200, 50, 255);
	} else {
		SDL_SetRenderDrawColor(this->r, 255, 0, 0, 0);
	}
	if(s.health < s.maxHealth && s.health > 0){
		SDL_RenderFillRect(this->r, &hcoo);
		SDL_SetRenderDrawColor(this->r, 255, 255, 255, 255);
		SDL_RenderDrawRect(this->r, &hmcoo);
	}	
	SDL_SetRenderDrawColor(this->r, 0, 0, 0, 0);
}

void AnimationHandler::renderOnScreen(Particle &p){
	int animIndex(0);
	string n = p.getId();
	string type = p.getType();
	
	if(n == "particle"){
		if(type == "explosion1")
			animIndex = 0;
		else if(type == "atkUp")
			animIndex = 1;
		else if(type == "smoke")
			animIndex = 2;
		else if(type == "smoke2")
			animIndex = 4;
		else if(type == "healing")
			animIndex = 3;
		else if(type == "cross")
			animIndex = 5;
		
		if(this->vAnimParticles[animIndex]->getTexture() == NULL){
			cout << "animTexture NULL" << endl;
		}
		//set animation to current frame
		this->vAnimParticles[animIndex]->setToFrame(p.getCurrentFrameAndIncrease());
		this->vAnimParticles[animIndex]->renderImage(this->r, p.coo);
// 		cout << "current frame : " << this->vAnimParticles[animIndex]->getCurrentFrame() << " " << p.getCurrentFrame() << endl;
	}
	else
		cout << "Error on AnimationHandler : id " << p.getId() << " not recognized..." << endl;
}

void AnimationHandler::renderOnScreen(Item &i){
	int animIndex(0);
	string n = i.getId();
	string type = i.getType();
	if(type == "itemAtkUp")
		animIndex = 0;
	else if(type == "itemHeal")
		animIndex = 1;
	else{
		cout << "Error on AnimationHandler : id " << i.getId() << " not recognized..." << endl;
		return;
	}
		
	if(this->vAnimItems[animIndex]->getTexture() == NULL){
		cout << "animTexture NULL" << endl;
	}
	//set animation to current frame
	this->vAnimItems[animIndex]->setToFrame(i.getCurrentFrameAndIncrease());
	this->vAnimItems[animIndex]->renderImage(this->r, i.coo);
			
	//set animation to current frame
	this->vAnimItems[animIndex]->setToFrame(i.getCurrentFrameAndIncrease());
	this->vAnimItems[animIndex]->renderImage(this->r, i.coo);
}

void AnimationHandler::renderOnScreen(Player &p){
	//	changing the alpha if it took damages
	if(p.invincible > 0){
		this->changeAlphaPlayer(rand()%255);
		p.invincible++;
		if(p.invincible == p.nbFramesInvincible)
			p.invincible = 0;
	} else {
		this->resetAlphaPlayer();
	}
	int ind(0);
	switch(p.getMvState()){
		case STATIONNARY:
			ind = 4;
			break;
			
		case UP:
		case UPRIGHT:
		case UPLEFT:
			ind = 0;
			break;
		case DOWN:
			ind = 1;
			break;
		case LEFT:
		case DOWNLEFT:
			ind = 3;
			break;
		case RIGHT:
		case DOWNRIGHT:
			ind = 2;
			break;
		default:
			ind = 4;
			break;
	}
	this->vAnimPlayer[ind]->setToFrame(p.getCurrentFrameAndIncrease());
	this->vAnimPlayer[ind]->renderImage(this->r, p.coo);
}

void AnimationHandler::changeAlphaPlayer(int alpha){
	this->vAnimPlayer[0]->changeAlpha(rand()%255);
	this->vAnimPlayer[1]->changeAlpha(rand()%255);
	this->vAnimPlayer[2]->changeAlpha(rand()%255);
	this->vAnimPlayer[3]->changeAlpha(rand()%255);
	this->vAnimPlayer[4]->changeAlpha(rand()%255);
}

void AnimationHandler::resetAlphaPlayer(){
	this->vAnimPlayer[0]->resetAlpha();
	this->vAnimPlayer[1]->resetAlpha();
	this->vAnimPlayer[2]->resetAlpha();
	this->vAnimPlayer[3]->resetAlpha();
	this->vAnimPlayer[4]->resetAlpha();
}

void AnimationHandler::addAnim(const Animation *a){
	//this->vAnim.push_back(a);
}

AnimationHandler::~AnimationHandler(){
	for(int i = 0; i < 3; i++){
		delete vAnim[i];
	}
	for(int i = 0; i < 5; i++){
		delete vAnimPlayer[i];
	}
	for(int i = 0; i < 1; i++){
		delete vAnimParticles[i];
	}
	vAnim.clear();
	vAnimPlayer.clear();
	vAnimParticles.clear();
// 	cout << "animationHandler deleted" << endl;
}
