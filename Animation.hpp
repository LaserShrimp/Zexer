#ifndef __ANIMATION_HPP__
#define __ANIMATION_HPP__

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "defines.h"
#include "Animation.hpp"

class Animation{
private:
	SDL_Texture *texture;
	int currentFrame;//number of the current frame (for animation)
	int numberOfFrames;
	SDL_Rect framePos;
protected:
public:
	Animation();
	Animation(SDL_Texture *t);
	Animation(const Animation& a);
	
	void setNumberOfFrames(int n);
	void setFrameSize(int w, int h);
	void setTexture(SDL_Texture *t);
	void setTexture(SDL_Renderer *r, char *texturePath);
	void nextFrame();
	void renderImage(SDL_Renderer *r, SDL_Rect dest);
	
	virtual ~Animation();
};


#endif
