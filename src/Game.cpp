#include "Game.hpp"

Game::Game(): score{0}{}

void Game::setScore(int s){
	this->score = s;
}

int Game::getScore(){return this->score;}

void Game::start(SDL_Renderer *renderer, SDL_Window *window){
	SDL_Event event;
	Wave w;
	Player *player = new Player();
	
	player->init();
    vector<Ship*> vEnemy;
	vector<Ship*> vPlayer;
	vector<Item*> vItems;
	vector<Particle*> vParticle;
// 	w.loadLevel(vEnemy, 1);
// 	w.randomizeShipCoo(vEnemy);
	
	SDL_Surface *sBackground = IMG_Load("assets/background.png");
	SDL_Texture *tBackground = SDL_CreateTextureFromSurface(renderer, sBackground);
	
	GameInterface *gameInterface = new GameInterface;
	AnimationHandler *aHandler = new AnimationHandler(renderer);
	gameInterface->initBackground(renderer);
	
	InputState inputs;
	int fps = FPS;
	Uint32 frameTime = 1000/fps; //1000 milliseconds/FPS
	Uint32 tick1 = 0;
	Uint32 tick2 = 0;
	
	Mix_AllocateChannels(10);
	Mix_Music *musicTest = Mix_LoadMUS("./assets/paProto.mp3");
	if(musicTest == nullptr){
		cout << Mix_GetError() << endl;
	}
	Mix_Chunk *c = Mix_LoadWAV("assets/plucked.wav");
	Mix_PlayMusic(musicTest, -1);
// 	Mix_VolumeMusic(MIX_MAX_VOLUME);
	while (player->getHealth() > 0  && !inputs.getquit() && !inputs.getescape()/* && w.getLevel() <= 5*/) {
		if(vEnemy.size() == 0){
			w.increaseLevel();
			w.loadRandomizedLevel(vEnemy, w.getLevel());
			w.randomizeShipCoo(vEnemy);
		}
		tick1 = SDL_GetTicks();
		SDL_PollEvent(&event);
		inputs.setState(event);
		player->doActions(inputs, vPlayer);
		
		for(unsigned long int k = 0; k < vEnemy.size(); k++){
			Ship *e = vEnemy[k];
			e->doActions(vEnemy, *player);
			if(player->hitShip(e->getHitbox())){
				player->takeDamage(e->getStrength());
// 				e->takeDamage(player->getStrength());
// 				e->scintillate(10);
			}
			for(Ship* p: vPlayer){
				//an enemy takes damages only if the Ship it collides with has another Id (prevents from missile to missile collisions)
				if(p->hitShip(e->getHitbox()) && p->getId() != e->getId()){
					if(e->takeDamage(p->getStrength())){
						gameInterface->increaseScore();
					} else {
						e->scintillate(10);
					}
					vParticle.push_back(new Particle("smoke", e->getCoo().x, e->getCoo().y, e->getCoo().w, e->getCoo().h));
					p->takeDamage(e->getStrength());
				}
			}
		}
		for(Ship* m: vPlayer){
			m->move();
		}
		for(Item* i: vItems){
			if(player->gatherItem(*i)){
				if(i->getType() == "itemAtkUp")
					vParticle.push_back(new Particle("atkUp", player->getCoo().x, player->getCoo().y, player->getCoo().w, player->getCoo().h));
				else if(i->getType() == "itemHeal")
					vParticle.push_back(new Particle("healing", player->getCoo().x, player->getCoo().y, player->getCoo().w, player->getCoo().h));
			}
			i->increaseAlive();
		}
		
		//RENDERING
		SDL_RenderCopy(renderer, tBackground, NULL, NULL);
		for(Item* i: vItems){
			aHandler->renderOnScreen(*i);
		}
		for(Ship* e: vEnemy){
			aHandler->renderOnScreen(*e);
		}
		for(Ship* e: vPlayer){
			aHandler->renderOnScreen(*e);
		}
		aHandler->renderOnScreen(*player);
		for(Particle* p: vParticle){
			aHandler->renderOnScreen(*p);
		}
		for(long unsigned int i = 0; i < vPlayer.size(); i++){
			//if the ship is out of the screen or has no health
			if(vPlayer[i]->getCoo().y + vPlayer[i]->getCoo().h < 0 || vPlayer[i]->getHealth() <= 0){
				delete vPlayer[i];
				vPlayer.erase(vPlayer.begin()+i);
			}
		}
		for(long unsigned int i = 0; i < vEnemy.size(); i++){
			//if the ship is out of the screen or has no health
			if((!vEnemy[i]->isOnGameArea() || vEnemy[i]->getHealth() <= 0)){
				vParticle.push_back(new Particle("explosion1", vEnemy[i]->getCoo().x, vEnemy[i]->getCoo().y, vEnemy[i]->getCoo().w, vEnemy[i]->getCoo().h));
				//Generate an item with chance 5/10 4/10 1/10
				if(vEnemy[i]->getId() != "missile"){
					int chance(rand()%10);
					if(chance <= 2)
						vItems.push_back(new Item("itemHeal", vEnemy[i]->getCoo().x, vEnemy[i]->getCoo().y, vEnemy[i]->getCoo().w, vEnemy[i]->getCoo().h));
					else if(chance == 3)
						vItems.push_back(new Item("itemAtkUp", vEnemy[i]->getCoo().x, vEnemy[i]->getCoo().y, vEnemy[i]->getCoo().w, vEnemy[i]->getCoo().h));
					
					Mix_PlayChannel(-1, c, 0);
				}
				delete vEnemy[i];
				vEnemy.erase(vEnemy.begin()+i);
			}
		}
		for(long unsigned int i = 0; i < vParticle.size(); i++){
			//If the animation is finished
			if(vParticle[i]->getCurrentFrame() >= vParticle[i]->getNbFrames()){
				delete vParticle[i];
				vParticle.erase(vParticle.begin()+i);
			}
		}
		for(long unsigned int i = 0; i < vItems.size(); i++){
			//If the animation is finished
			if(vItems[i]->isTimeFinished() || vItems[i]->getHealth() <= 0){
				delete vItems[i];
				vItems.erase(vItems.begin()+i);
			}
		}
		
		gameInterface->loadStatsFromPlayer(*player);
		gameInterface->render(renderer);
		SDL_RenderPresent(renderer);
		//SDL_RenderClear(renderer);
		tick2 = SDL_GetTicks();
		if(tick2 - tick1 < frameTime)
			SDL_Delay(frameTime - (tick2 - tick1));
	}
	this->score = gameInterface->getScore();
	cout << "Final score : " << gameInterface->getScore() << endl;
	delete gameInterface;
	delete player;
	for(long unsigned int i = 0; i < vEnemy.size(); i++){
		delete vEnemy[i];
	}
	for(long unsigned int i = 0; i < vParticle.size(); i++){
		delete vParticle[i];
	}
	for(long unsigned int i = 0; i < vPlayer.size(); i++){
		delete vPlayer[i];
	}
	for(long unsigned int i = 0; i < vItems.size(); i++){
		delete vItems[i];
	}
	vEnemy.clear();
	vPlayer.clear();
	vParticle.clear();
	vItems.clear();
	delete aHandler;
	
	SDL_FreeSurface(sBackground);
	SDL_DestroyTexture(tBackground);
	
	Mix_FreeMusic(musicTest);
}

void Game::pause(){
	
}

Game::~Game(){
	
}
