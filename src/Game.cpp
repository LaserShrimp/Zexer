#include "Game.hpp"

// Game::Game(): score_{0}{}

Game* Game::getInstance() {
	if(game_ == nullptr) {
		game_ = new Game();
		return game_;
	}

	return game_;
}

void Game::setScore(int s){
	score_ = s;
}

int Game::getScore(){return score_;}

void Game::start(SDL_Renderer *renderer){
	SDL_Event event;
	Wave w;
	Player *player = new Player();
	
	player->init();
    vector<Ship*> vEnemy;
	vector<Ship*> vPlayer;
	vector<Item*> vItems;
	vector<Particle*> vParticle;
	
	SDL_Surface *sBackground = IMG_Load("assets/background.png");
	SDL_Texture *tBackground = SDL_CreateTextureFromSurface(renderer, sBackground);
	SDL_Rect rectB = {.x = 0, .y = 0, .w = WIN_WIDTH, .h = WIN_HEIGHT};
	
	int a = 0; //To count frames and make the scroll TODO: delete when scrolling tests are finished
	SDL_Surface *sBackground1 = IMG_Load("assets/testScroll1.png");
	SDL_Texture *tBackground1 = SDL_CreateTextureFromSurface(renderer, sBackground1); 
	SDL_Rect rectB1 = {.x = 0, .y = -WIN_HEIGHT, .w = WIN_WIDTH, .h = WIN_HEIGHT};
	
	SDL_Surface *splanet1 = IMG_Load("assets/background/planet1.png");
	SDL_Surface *splanet2 = IMG_Load("assets/background/planet2.png");
	SDL_Texture *tplanet1 = SDL_CreateTextureFromSurface(renderer, splanet1);
	SDL_Texture *tplanet2 = SDL_CreateTextureFromSurface(renderer, splanet2);
	SDL_Rect rectplanet1 = {.x = rand()%(WIN_WIDTH + 500) - 250, .y = -510, .w = 500, .h = 500};
	SDL_Rect rectplanet2 = {.x = rand()%(WIN_WIDTH + 500) - 250, .y = 0, .w = 500, .h = 500};
// 	SDL_SetTextureAlphaMod(tplanet1, 124);
// 	SDL_SetTextureAlphaMod(tplanet2, 124);
	
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
	Mix_Chunk *cMetalBoom = Mix_LoadWAV("assets/metalBoom.wav");
	Mix_Chunk *winChunk = Mix_LoadWAV("assets/winScreen.wav");
	Mix_Chunk *loseChunk = Mix_LoadWAV("assets/loseScreen.wav");
	Mix_PlayMusic(musicTest, -1);
// 	Mix_VolumeMusic(MIX_MAX_VOLUME);
	bool gameLoopActive{true};
	bool levelContinues{true};
	while (gameLoopActive) {
		gameLoopActive = !inputs.getquit() && !inputs.getescape();
		if(player->getHealth() <= 0 && levelContinues){
			levelContinues = false;
			Mix_PlayChannel(-1, loseChunk, 0);
		}
		if(vEnemy.size() == 0 && levelContinues){
			w.increaseLevel();
// 			w.loadRandomizedLevel(vEnemy, w.getLevel());
			levelContinues = w.loadLevelFromFile(vEnemy, "level.lvl");
			if(!levelContinues) {
				Mix_PlayChannel(-1, winChunk, 0);
			}
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
				if(player->getInvincible() == 0){
					vParticle.push_back(new Particle("cross", player->getCoo().x, player->getCoo().y, player->getCoo().w, player->getCoo().h));
					Mix_PlayChannel(-1, cMetalBoom, 0);
				}
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
		if(a%10 == 0){
// 			rectB.y++;
// 			rectB1.y++;
			rectplanet1.y++;
			rectplanet2.y++;
		}
		a++;
		if(rectB.y == 0)
			rectB1.y = -WIN_HEIGHT;
		if(rectB1.y == 0)
			rectB.y = -WIN_HEIGHT;
		if(rectplanet1.y == 0){
			rectplanet2.y = -(rand()%500) - 500;
			rectplanet2.x = rand()%(WIN_WIDTH + 500) - 250;
		}
			
		if(rectplanet2.y == 0){
			rectplanet1.y = -(rand()%500) - 500;
			rectplanet1.x = rand()%(WIN_WIDTH + 500) - 250;
		}
			
		SDL_RenderCopy(renderer, tBackground, NULL, &rectB);
		SDL_RenderCopy(renderer, tBackground1, NULL, &rectB1);
		
		SDL_RenderCopy(renderer, tplanet1, NULL, &rectplanet1);
		SDL_RenderCopy(renderer, tplanet2, NULL, &rectplanet2);
		
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
		if(player->getHealth() <= 0){
			player->setX(-100);
			player->synchronizeVectFromCoo();
		}
		
		gameInterface->loadStatsFromPlayer(*player);
		gameInterface->render(renderer);
		if(!levelContinues){
			endScreen(renderer, player->getHealth() > 0);
		}
		SDL_RenderPresent(renderer);
		tick2 = SDL_GetTicks();
		if(tick2 - tick1 < frameTime)
			SDL_Delay(frameTime - (tick2 - tick1));
	}

	score_ = gameInterface->getScore();
	delete gameInterface;
	if(player != nullptr){
		delete player;
	}
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
	SDL_FreeSurface(splanet1);
	SDL_DestroyTexture(tplanet1);
	SDL_FreeSurface(splanet2);
	SDL_DestroyTexture(tplanet2);
	
	Mix_FreeChunk(c);
	Mix_FreeChunk(cMetalBoom);
	Mix_FreeChunk(winChunk);
	Mix_FreeChunk(loseChunk);
	Mix_FreeMusic(musicTest);
}

void Game::pause(){
	
}

void Game::endScreen(SDL_Renderer *r, bool win){
	TTF_Font *f = TTF_OpenFont("Hybrid_b.ttf", 30);

	SDL_Surface *s = NULL;
	if(win){
		s = TTF_RenderText_Blended(f, "FINISHED !", {255, 255, 255, 255});
	} else {
		s = TTF_RenderText_Blended(f, "EXPLODED !", {255, 255, 255, 255});
	}
	SDL_Texture *t = SDL_CreateTextureFromSurface(r, s);
	SDL_RenderCopy(r, t, NULL, NULL);

	SDL_FreeSurface(s);
	SDL_DestroyTexture(t);
	TTF_CloseFont(f);
}

Game::~Game(){
	
}
