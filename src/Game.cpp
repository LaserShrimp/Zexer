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
	SDL_Rect rectB = {.x = 0, .y = 0, .w = WIN_WIDTH, .h = WIN_HEIGHT};
	
	int a = 0; //To count frames and make the scroll TODO: delete when scrolling tests are finished
	SDL_Surface *sBackground1 = IMG_Load("assets/testScroll1.png");
	SDL_Texture *tBackground1 = SDL_CreateTextureFromSurface(renderer, sBackground1); 
	SDL_Rect rectB1 = {.x = 0, .y = -WIN_HEIGHT, .w = WIN_WIDTH, .h = WIN_HEIGHT};
	
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
	while (player->getHealth() > 0  && !inputs.getquit() && !inputs.getescape()) {
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
			e->doActions(vEnemy, vItems, vParticle, *player);
			if(player->hitShip(e->getHitbox())){
				player->takeDamage(e->getStrength());
			}
			for(Ship* p: vPlayer){
				//an enemy takes damages only if the Ship it collides with has another Id (prevents from missile to missile collisions)
				if(p->hitShip(e->getHitbox()) && p->getId() != e->getId()){
					if(e->takeDamage(p->getStrength())){
						gameInterface->increaseScore();
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
		if(a%3 == 0){
			rectB.y++;
			rectB1.y++;
		}
		a++;
		if(rectB.y == 0)
			rectB1.y = -WIN_HEIGHT;
		if(rectB1.y == 0)
			rectB.y = -WIN_HEIGHT;
		SDL_RenderCopy(renderer, tBackground, NULL, &rectB);
		SDL_RenderCopy(renderer, tBackground1, NULL, &rectB1);
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
			if((vEnemy[i]->getReadyToDelete())){
				//Generate an item with chance 5/10 4/10 1/10
				if(vEnemy[i]->getId() != "missile"){
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
	SDL_FreeSurface(sBackground1);
	SDL_DestroyTexture(tBackground1);
	
	Mix_FreeMusic(musicTest);
}

void Game::pause(){
	
}

Game::~Game(){
	
}
