#include "InputState.hpp"

InputState::InputState():z{false}, q{false}, s{false}, d{false}, right{false}, left{false}, up{false}, down{false}, spacebar{false}, escape{false}, quit(false){
}

void InputState::setState(const SDL_Event event){
	if(event.type == SDL_QUIT){
		this->quit = true;
	}
	else if(event.type == SDL_KEYDOWN){
		switch(event.key.keysym.sym){
			case SDLK_LEFT:
				this->left = true;
				break;
			case SDLK_RIGHT:
				this->right = true;
				break;
			case SDLK_UP:
				this->up = true;
				break;
			case SDLK_DOWN:
				this->down = true;
				break;
			case SDLK_z:
				this->z = true;
				break;
			case SDLK_q:
				this->q = true;
				break;
			case SDLK_s:
				this->s = true;
				break;
			case SDLK_d:
				this->d = true;
				break;
			case SDLK_SPACE:
				this->spacebar = true;
				break;
			case SDLK_ESCAPE:
				this->escape = true;
				break;
			default:
				break;
		}
	}
	else if(event.type == SDL_KEYUP){
		switch(event.key.keysym.sym){
			case SDLK_LEFT:
				this->left = false;
				break;
			case SDLK_RIGHT:
				this->right = false;
				break;
			case SDLK_UP:
				this->up = false;
				break;
			case SDLK_DOWN:
				this->down = false;
				break;
			case SDLK_z:
				this->z = false;
				break;
			case SDLK_q:
				this->q = false;
				break;
			case SDLK_s:
				this->s = false;
				break;
			case SDLK_d:
				this->d = false;
				break;
			case SDLK_SPACE:
				this->spacebar = false;
				break;
			case SDLK_ESCAPE:
				this->escape = false;
				break;
			default:
				break;
		}
	}
}


bool InputState::getz() const{
	return this->z;
}
bool InputState::getq() const{
	return this->q;
}
bool InputState::gets() const{
	return this->s;
}
bool InputState::getd() const{
	return this->d;
}
bool InputState::getright() const{
	return this->right;
}
bool InputState::getleft() const{
	return this->left;
}
bool InputState::getup() const{
	return this->up;
}
bool InputState::getdown() const{
	return this->down;
}
bool InputState::getspacebar() const{
	return this->spacebar;
}
bool InputState::getescape() const{
	return this->escape;
}
bool InputState::getquit() const{
	return this->quit;
}


InputState::~InputState(){}
