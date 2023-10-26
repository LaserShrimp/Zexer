#include "Wave.hpp"

Wave::Wave(): level{0}{
	
}

int Wave::getLevel(){
	return this->level;
}

void Wave::increaseLevel(){
	this->level++;
}

void Wave::loadLevel(vector<Ship*>& v, int l){
	if(l == 1){
		for(long unsigned int i = 0; i < 5; i++){
			if(i < 3){
				v.push_back(new Enemy());
				v.back()->init();
			}
			else if(i == 3){
				v.push_back(new Unit1());
				v.back()->init();
			}
			else if(i == 4){
				v.push_back(new UnitOmni());
				v.back()->init();
			}
// 			cout << "i : " << v[i]->getId() << endl;
		}
	} else if (l == 2){
		for(long unsigned int i = 0; i < 7; i++){
			if(i < 5){
				v.push_back(new Enemy());
				v.back()->init();
			}
			else {
				v.push_back(new Unit1());
				v.back()->init();
			}
		}
	} else if (l == 3){
		for(long unsigned int i = 0; i < 6; i++){
			v.push_back(new Unit1());
			v.back()->init();
		}
	} else if (l == 4){
		for(long unsigned int i = 0; i < 60; i++){
			if(i < 20){
				v.push_back(new Unit1());
				v.back()->init();
			}
			else {
				v.push_back(new Enemy());
				v.back()->init();
			}
		}
	} else if (l == 5){
		for(long unsigned int i = 0; i < 50; i++){
			v.push_back(new UnitOmni());
			v.back()->init();
		}
	} else {
		cout << "impossible to load requested level..." << endl;
	}
}

/**
 * this function set random coordinates for all the ships in v.
 * these coo must be between : 0 <= x <= WIN_WIDTH - v[i].w and  -Y_EXTENSION <= y <= 0 - v[i].h
 */
void Wave::randomizeShipCoo(vector<Ship*>& v){
	for(long unsigned int i = 0; i < v.size(); i++){
		int x = rand()%(WIN_WIDTH - v[i]->getW()) /*+ v[i]->getW()*/;
		int y = rand()%(Y_EXTENSION - v[i]->getH()) - (Y_EXTENSION);
		v[i]->setCooVect(x, y);
		v[i]->synchronizeCooFromVect();
	}
}

// Ship* Wave::get(long unsigned int i){
// 	return this->vEnemy[i];
// }
// void Wave::erase(long unsigned int i){
// 	this->vEnemy.erase(this->vEnemy)
// }
// 
// void Wave::add(string n){
// 	if(n == "enemy")
// 		this->vEnemy.push_back(new Enemy());
// 	else if(n == "unit1")
// 		this->vEnemy.push_back(new Unit1());
// 	
// 	this->vEnemy.end()->init();
// }

Wave::~Wave(){
	for(long unsigned int i = 0; i < this->vEnemy.size(); i++){
		delete this->vEnemy[i];
	}
	this->vEnemy.clear();
}

// Ship* operator[](int i){
// 	return ;
// }
