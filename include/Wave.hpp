#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include "defines.h"
#include "gameAddOns.h"
#include "Ship.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include "Missile.hpp"
#include "Unit1.hpp"
#include "InputState.hpp"

class Wave{
private:
	int level;
// 	vector<Ship*> vEnemy;
protected:
public:
	Wave();
	
	void setLevel(int level);
	int getLevel();
	void increaseLevel();
	
	void insertShip(vector<Ship*>& v, string shipName);
	void loadLevel(vector<Ship*>& v, int l);
	void loadRandomizedLevel(vector<Ship*>& v, int l);
	void randomizeShipCoo(vector<Ship*>& v);
	
	virtual ~Wave();
};
