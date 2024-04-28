#include "Wave.hpp"

Wave::Wave(): level{0}{
	
}

void Wave::setLevel(int level){
	this->level = level;
}

int Wave::getLevel(){
	return this->level;
}

void Wave::increaseLevel(){
	this->level++;
}

void Wave::insertShip(vector<Ship*>& v, string name){
	if(name == "unit1"){
		Unit1 *s = new Unit1();
		s->init();
		v.push_back(s);
	} else if(name == "unitOmni"){
		UnitOmni *s = new UnitOmni();
		s->init();
		v.push_back(s);
	} else if(name == "enemy"){
		Enemy *s = new Enemy();
		s->init();
		v.push_back(s);
	} else if(name == "unitTracker"){
		UnitTracker *s = new UnitTracker();
		s->init();
		v.push_back(s);
	}
	else if(name == "unitDestroyer"){
		UnitDestroyer *s = new UnitDestroyer();
		s->init();
		v.push_back(s);
	}
}

void Wave::loadLevel(vector<Ship*>& v, int l){
	this->level = l;
	if(l == 1){
		for(long unsigned int i = 0; i < 5; i++){
			if(i < 3){
				this->insertShip(v, "enemy");
			}
			else if(i == 3){
				this->insertShip(v, "unit1");
			}
			else if(i == 4){
				this->insertShip(v, "unitOmni");
			}
// 			cout << "i : " << v[i]->getId() << endl;
		}
	} else if (l == 2){
		for(long unsigned int i = 0; i < 7; i++){
			if(i < 5){
				this->insertShip(v, "enemy");
			}
			else {
				this->insertShip(v, "unit1");
			}
		}
	} else if (l == 3){
		for(long unsigned int i = 0; i < 6; i++){
			this->insertShip(v, "unit1");
		}
	} else if (l == 4){
		for(long unsigned int i = 0; i < 60; i++){
			if(i < 20){
				this->insertShip(v, "unit1");
			}
			else {
				this->insertShip(v, "enemy");
			}
		}
	} else if (l == 5){
		for(long unsigned int i = 0; i < 50; i++){
			this->insertShip(v, "unitOmni");
		}
	} else {
		cout << "impossible to load requested level..." << endl;
	}
}

void Wave::loadRandomizedLevel(vector<Ship*>& v, int l){
	this->level = l;
	for(int i = 0; i <= l; i++){
		int o = rand()%5;
		if(o == 0)
			this->insertShip(v, "unit1");
		else if(o == 1)
			this->insertShip(v, "unitOmni");
		else if(o == 2)
			this->insertShip(v, "enemy");
		else if(o == 3)
			this->insertShip(v, "unitTracker");
		else if(o == 4)
			this->insertShip(v, "unitDestroyer");
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

bool Wave::loadLevelFromFile(vector<Ship*>& v, string fileName){
	ifstream f(fileName);
	string currentLine("");
	int cpt(0);
	//Go to the current level
	while(cpt != this->level && getline(f, currentLine)){
		if(currentLine == "*")
			cpt++;
	}
	//load the level
	while(getline(f, currentLine)){
		if(currentLine == "*")
			break;
		this->insertShip(v, currentLine);
	}
	f.close();

	return currentLine != "";
}

Wave::~Wave(){
}
