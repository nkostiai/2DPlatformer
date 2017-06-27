#include <SDL.h>
#include <algorithm>
#include <memory>
#include "Game.h"
#include "input.h"
#include "Globals.h"
#include "graphics.h"
#include "sprite.h"
#include "units.h"
#include "levelstate.h"

Game::Game()
{
	gameLoop();
}

Game::~Game()
{
}

void Game::gameLoop()
{
	//Initialization
	running = true;

	SDL_Event event;
	Graphics g;
	Input input;

	gameStates.push_back(std::make_unique<LevelState>(LevelState(g)));


	auto last_update = std::chrono::high_resolution_clock::now();

	//Main game loop
	while (running) {
		//Init loop properties
		using std::chrono::high_resolution_clock;
		using std::chrono::milliseconds;
		using std::chrono::duration_cast;
		const auto frame_start = high_resolution_clock::now();

		//-----INPUT-----
		//Update input status
		input.startNewFrame();
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				input.pressKey(event.key.keysym.scancode);
				break;
			case SDL_KEYUP:
				input.releaseKey(event.key.keysym.scancode);
				break;
			case SDL_QUIT:
				running = false;
				break;
			}
		}
		handleInput(input);
		//----/INPUT-----

		//----UPDATE-----
		const auto current_time = high_resolution_clock::now();
		const auto upd_elapsed_time = current_time - last_update;
		const auto elapsedTime = duration_cast<milliseconds>(upd_elapsed_time).count();

		update((units::MS)elapsedTime);

		last_update = high_resolution_clock::now();
		//----/UPDATE-----

		//----DRAW-----
		draw(g);
		//----DRAW----

		//----WAIT----
		const auto frame_end = high_resolution_clock::now();
		const auto frame_elapsed = duration_cast<milliseconds>(frame_end - frame_start);
		const auto delay_duration = (globals::MAX_FRAME_TIME - frame_elapsed);
		SDL_Delay(std::max(delay_duration.count(), long long(0)));
		//----/WAIT----

		//Print FPS
		//LOG(1 / ((duration_cast<std::chrono::nanoseconds>(high_resolution_clock::now() - frame_start).count() * (1.0)) / 1000000000));

	}


}

void Game::handleInput(Input& input)
{
	//QUIT
	if (input.isKeyPressed(SDL_SCANCODE_ESCAPE)) {
		this->running = false;
	}

	gameStates[currentState]->handleInput(input);

}

void Game::update(units::MS elapsedTime)
{
	gameStates[currentState]->update(elapsedTime);
}

void Game::draw(Graphics& g)
{
	g.clear();
	gameStates[currentState]->draw(g);
	g.flip();
}
