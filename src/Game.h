#pragma once
#include <chrono>
#include <memory>
#include <vector>
#include "gamestate.h"

class Graphics;
class Input;
class Sprite;
union SDL_Event;

class Game {

public:

	Game();
	~Game();

private:
	void gameLoop();
	void handleInput(Input& input);
	void update(int elapsedTime_ms);
	void draw(Graphics & g);
	Game(const Game&) = delete;
	Game & operator=(const Game&) = delete;
	bool running = true;

	std::vector<std::unique_ptr<GameState>> gameStates;
	int currentState = 0;

	


};