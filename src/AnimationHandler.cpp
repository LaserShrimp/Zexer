#include "AnimationHandler.hpp"

AnimationHandler::AnimationHandler(SDL_Renderer *r):r{r}{
// 	Animation *aNeutAst = new Animation();
// 	aNeutAst->setName("asteroid");
// 	aNeutAst->setFrameSize(WIDTH, HEIGHT);
// 	aNeutAst->setNumberOfFrames(12);
// 	aNeutAst->setTexture(r, (char*)"assets/asteroidAnimation.png");
// 	//addAnim(aNeutAst);
	this->vAnim.push_back(new Animation());
	this->vAnim[0]->setName("asteroid");
	this->vAnim[0]->setFrameSize(WIDTH, HEIGHT);
	this->vAnim[0]->setNumberOfFrames(12);
	this->vAnim[0]->setTexture(r, (char*)"assets/asteroidAnimation.png");
}

void AnimationHandler::renderOnScreen(Ship &s){
	int animIndex(0);
	string n = s.getId();
// 	for(int i = 0; i < this->vAnim.size(); i++){
// 		animIndex = i;
// 		if(this->vAnim[i].getId() == s.getName()){
// 			break;
// 		}
// 	}
// 	if(animIndex == this->vAnim.size()){
// 		cout << "Error on AnimationHandler : id " << s.getId() << " not recognized..." << endl;
// 		return;
// 	}
	
		if("asteroid" == n){
			animIndex = 0;
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
			this->vAnim[animIndex]->renderImage(this->r, s.coo);
			this->vAnim[animIndex]->nextFrame();
	
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
			if(s.health < s.maxHealth){
				SDL_RenderFillRect(this->r, &hcoo);
				SDL_SetRenderDrawColor(this->r, 255, 255, 255, 255);
				SDL_RenderDrawRect(this->r, &hmcoo);
			}	
			SDL_SetRenderDrawColor(this->r, 0, 0, 0, 0);
			
		}
		else
			cout << "Error on AnimationHandler : id " << s.getId() << " not recognized..." << endl;
			
}

void AnimationHandler::addAnim(const Animation *a){
	//this->vAnim.push_back(a);
}
