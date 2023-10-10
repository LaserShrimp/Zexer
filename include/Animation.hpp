#ifndef __ANIMATION_HPP__
#define __ANIMATION_HPP__

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "defines.h"
#include "Animation.hpp"

using namespace std;

class Animation{
private:
	string name;
	SDL_Texture *texture;
	int currentFrame;//number of the current frame (for animation)
	int numberOfFrames;
	SDL_Rect framePos;
	bool alphaChanged;
protected:
public:
	Animation();
	Animation(SDL_Texture *t, string name);
	Animation(const Animation& a);
	
	void setName(string name);
	void setNumberOfFrames(int n);
	void setFrameSize(int w, int h);
	void setTexture(SDL_Texture *t);
	void setTexture(SDL_Renderer *r, char *texturePath);
	void nextFrame();
	void changeAlpha(int alpha);
	void resetAlpha();
	void renderImage(SDL_Renderer *r, SDL_Rect dest);
	SDL_Texture* getTexture();
	
	virtual ~Animation();
};


#endif
