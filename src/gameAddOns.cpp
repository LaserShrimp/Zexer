#include "gameAddOns.hpp"

/**
 * This function takes the coordinates rect and returns 1 if it is on the camera's sight, 0 otherwise
 */
int isOnCamera(const SDL_Rect rect){
	return  rect.x < WIN_WIDTH && rect.x + rect.w > 0
		&& rect.y < WIN_HEIGHT && rect.y + rect.h > 0;
}
