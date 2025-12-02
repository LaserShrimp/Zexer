#include "SDLMenu.hpp"
#include "gameAddOns.hpp"

std::string SDLMenu::optionHovered() const {
	return options_.at(optionHovered_);
}

void SDLMenu::addOption(const std::string newOption){
	options_.push_back(newOption);
}

void SDLMenu::setCoordinates(const SDL_Rect newCoordinates) {
	coordinates_ = newCoordinates;
}

void SDLMenu::setPadding(const int p){
	padding_ = p;
}

void SDLMenu::setFont(TTF_Font* f) {
	font_ = f;
}

void SDLMenu::renderMenu(SDL_Renderer *renderer) const {
	SDL_Texture *t = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, coordinates_.w, coordinates_.h);
	SDL_SetTextureBlendMode(t, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(renderer, t);

	int H{(coordinates_.h - ((static_cast<int>(options_.size()) - 1) * padding_))/static_cast<int>(options_.size())};
	int cpt{0};
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	for(auto s: options_){
		SDL_Surface *textSurface = TTF_RenderText_Blended(font_, s.c_str(), {255, 255, 255, 255});
		SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		SDL_Rect textDst = {0, cpt*(H + padding_), coordinates_.w, H};
		SDL_RenderCopy(renderer, textTexture, NULL, &textDst);

		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(textTexture);
		cpt++;
	}
	SDL_Rect hoverRect = {0, optionHovered_ * H, coordinates_.w, H};
	SDL_SetRenderDrawColor(renderer, 125, 50, 78, 255);
	SDL_RenderDrawRect(renderer, &hoverRect);
	SDL_SetRenderTarget(renderer, NULL);
	SDL_RenderCopy(renderer, t, NULL, &coordinates_);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);


	SDL_DestroyTexture(t);
}

void SDLMenu::changeSelection(int delta) {
	int newSelection{optionHovered_ + delta};
	if(newSelection < 0){
		newSelection = options_.size() - 1;
	} else if (newSelection >= options_.size()){
		newSelection = 0;
	}
	optionHovered_ = newSelection;
}

void SDLMenu::deinit(){
	TTF_CloseFont(font_);
}
