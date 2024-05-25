#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

class SDLMenu {
public:
	std::string optionHovered() const;
	void addOption(const std::string newOption);
	void setCoordinates(const SDL_Rect coordinates);
	void setPadding(const int p);
	void setFont(TTF_Font* f);
	void renderMenu(SDL_Renderer *renderer) const;

	/// \brief adds or substracts to optionHovered_
	void changeSelection(int delta);

	void deinit();
protected:
private:
	std::vector<std::string> options_{};
	int optionHovered_{};
	int padding_{};
	SDL_Rect coordinates_{};
	TTF_Font* font_{nullptr};
};
