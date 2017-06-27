#include "levelstate.h"
#include "player.h"
#include "input.h"

LevelState::LevelState(Graphics& g)
{
	initializeObjects(g);
}

void LevelState::initializeObjects(Graphics& g) {
	this->player = std::make_shared<Player>(Player(g, 120, 120));
	gameObjects.push_back(this->player);

}

void LevelState::handleInput(Input & input)
{
	if (input.isKeyPressed(SDL_SCANCODE_LEFT)) {
		player->move(globals::direction::LEFT);
	}
	else if (input.isKeyPressed(SDL_SCANCODE_RIGHT)) {
		player->move(globals::direction::RIGHT);
	}
	else {
		player->move(globals::direction::STOP);
	}
}

void LevelState::draw(Graphics& g) {
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->draw(g);
	}
}

void LevelState::update(units::MS elapsedTime)
{
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->update(elapsedTime);
	}
}
