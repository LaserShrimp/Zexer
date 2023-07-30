#include "Animation.hpp"

Animation::Animation(): texture{NULL}, currentFrame{0}, numberOfFrames{0}, framePos({.x = 0, .y = 0, .w = 0, .h = 0}){
	
}

Animation::Animation(SDL_Texture *t): texture{t}, currentFrame{0}, numberOfFrames{0}, framePos{}{
	
}

Animation::Animation(const Animation& a): texture{a.texture}, currentFrame{a.currentFrame}, numberOfFrames{a.numberOfFrames}, framePos{a.framePos}{
}

void Animation::setNumberOfFrames(int n){
	this->numberOfFrames = n;
}

void Animation::setFrameSize(int w, int h){
	this->framePos.w = w;
	this->framePos.h = h;
}
void Animation::setTexture(SDL_Texture *t){
	this->texture = t;
}
void Animation::setTexture(SDL_Renderer *r, char* texturePath){
	this->texture = SDL_CreateTextureFromSurface(r, IMG_Load(texturePath));
}

/**
 * Sets the animation to the next frame
 */
void Animation::nextFrame(){
	this->currentFrame = (currentFrame+1)%numberOfFrames;
	std::cout << "current frame : " << currentFrame << std::endl;
	this->framePos.x = (this->currentFrame * this->framePos.w);
}

void Animation::renderImage(SDL_Renderer *r, SDL_Rect dest){
	SDL_RenderCopy(r, this->texture, &(this->framePos), &dest);
}

Animation::~Animation(){
	SDL_DestroyTexture(this->texture);
}
