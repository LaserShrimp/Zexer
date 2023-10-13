#ifndef __SHIP_HPP__
#define __SHIP_HPP__

#include <iostream>
#include <vector>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "defines.h"
#include "gameAddOns.h"
#include "Animation.hpp"
#include "Vect.hpp"

using namespace std;

class Ship{
	protected:
		string id; 
		Vect cooVect;
		Vect speedVect;
		SDL_Rect coo;
		SDL_Rect hitbox;
		float speed;
		int health;
		int maxHealth;
		int atk;
		float hitboxRatio; //to set the size of the hitbox (a a percentage of the whole sprite centered in the middle of the ship)
		
		int frame;//number of the current frame (for animation)
		
		int invincible;
		int nbFramesInvincible;
		
		bool stayInScreen;
		void setId(string id);
	private :
		
	public:
		Ship();
		Ship(int x, int y, string id);
		Ship(SDL_Rect coo, float speed);
		
		string getId();
		SDL_Rect getCoo();
		Vect& getCooVect() const;
		Vect& getSpeedVect() const;
		SDL_Rect getHitbox();
		int getX();
		int getY();
		int getW();
		int getH();
		float getSpeed();
		int getHealth();
		int getMaxHealth();
		int getAtk();
		float getXSpeed();
		float getYSpeed();
		int getInvincible();
		int getCurrentFrame();
		int getCurrentFrameAndIncrease();
		
		void setCooVect(float x, float y);
		void setSpeedVect(float x, float y);
		void setCoo(SDL_Rect n);
		void setHitbox(SDL_Rect b);
		void setX(int x);
		void setY(int y);
		void setW(int w);
		void setH(int h);
		void setSpeed(float s);
		void setHealth(int h);
		void setMaxHealth(int m);
		void setAtk(int a);
		void setXSpeed(float x);
		void setYSpeed(float y);
		void setHitboxRatio(float hr);
		void setInvincible(int i);
		void setStayInScreen(bool b);
		
		virtual void init();
		
		void goLeft();
		void goRight();
		void goUp();
		void goDown();
		virtual void move();
		void translationMovement();
		void synchronizeVectFromCoo();
		void synchronizeCooFromVect();
		void heal();
		void heal(int a);
		void healCompletely();
		virtual bool takeDamage();
		virtual bool takeDamage(int d);
		void updateHitbox();
		virtual void doActions(vector<Ship*>& v);
		
		void rerack();
		
		bool hitShip(SDL_Rect s);
		virtual void launch(int startX, int startY);
		virtual void launch(int startX, int startY, Vect dir);
		virtual void launch(int startX, int startY, string launcherId);
		virtual void launch(int startX, int startY, string launcherId, int atk);
		
		void scintillate(int nbFrames);
		void scintillate();
		
		virtual ~Ship();
		friend class AnimationHandler;
};

ostream& operator<<(ostream& out, Ship &s);

#endif
