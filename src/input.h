#pragma once
#include <SDL.h>
#include <map>
#include <memory>

class Input {

public:

	Input();

	void pressKey(SDL_Scancode);
	void releaseKey(SDL_Scancode code);
	bool isKeyPressed(SDL_Scancode code);
	bool wasKeyReleased(SDL_Scancode code);
	bool isKeyHeld(SDL_Scancode code);
	void startNewFrame();
	
	Input(const Input&) = delete;
	Input& operator=(const Input&) = delete;

private:
	std::unique_ptr<std::map<SDL_Scancode, bool>> currentFrame;
	std::unique_ptr<std::map<SDL_Scancode, bool>> previousFrame;


};