#include "Animation.hpp"

Animation::Animation(): name{""}, texture{NULL}, currentFrame{0}, numberOfFrames{0}, framePos({.x = 0, .y = 0, .w = 0, .h = 0}), alphaChanged(false){
	
}

Animation::Animation(SDL_Texture *t ,string name): name{name}, texture{t}, currentFrame{0}, numberOfFrames{0}, framePos{}, alphaChanged{false}{
	
}

Animation::Animation(const Animation& a): name{a.name}, texture{a.texture}, currentFrame{a.currentFrame}, numberOfFrames{a.numberOfFrames}, framePos{a.framePos}, alphaChanged{false}{
}

void Animation::setName(string name){
	this->name = name;
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
	SDL_SetTextureBlendMode(this->texture, SDL_BLENDMODE_BLEND);
}

/**
 * Sets the animation to the next frame
 */
void Animation::nextFrame(){
	this->currentFrame = (currentFrame+1)%numberOfFrames;
	this->framePos.x = (this->currentFrame * this->framePos.w);
}

void Animation::setToFrame(int frame){
	int currentFrame = frame%numberOfFrames;
	this->framePos.x = currentFrame * this->framePos.w;
}

void Animation::changeAlpha(int alpha){
	SDL_SetTextureAlphaMod(this->texture, alpha);
	this->alphaChanged = true;
}
void Animation::resetAlpha(){
	if(this->alphaChanged){
		SDL_SetTextureAlphaMod(this->texture, 0xFF);
	}
}

void Animation::renderImage(SDL_Renderer *r, SDL_Rect dest){
	SDL_RenderCopy(r, this->texture, &(this->framePos), &dest);
}

SDL_Texture* Animation::getTexture(){
	return this->texture;
}

Animation::~Animation(){
	SDL_DestroyTexture(this->texture);
}
