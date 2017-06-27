#include "input.h"
Input::Input()
{
	currentFrame = std::make_unique<std::map<SDL_Scancode, bool>>(std::map<SDL_Scancode, bool>());
	previousFrame = std::make_unique<std::map<SDL_Scancode, bool>>(std::map<SDL_Scancode, bool>());
}


void Input::pressKey(SDL_Scancode code) {
	(*currentFrame)[code] = true;
}

void Input::releaseKey(SDL_Scancode code) {
	(*currentFrame)[code] = false;
}



bool Input::isKeyPressed(SDL_Scancode code) {
	return (*currentFrame)[code];
}

bool Input::wasKeyReleased(SDL_Scancode code) {
	return ((*previousFrame)[code] && (!(*currentFrame)[code]));
}

bool Input::isKeyHeld(SDL_Scancode code) {
	return (*previousFrame)[code] && (*currentFrame)[code];
}


//Swaps the input maps and clears the current map
void Input::startNewFrame()
{
	(*previousFrame) = (*currentFrame);

}
