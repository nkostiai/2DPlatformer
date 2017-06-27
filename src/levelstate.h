#pragma once
#include "gamestate.h"
#include <memory>
#include <vector>

class GameObject;
class Player;

class LevelState : public GameState {
public:
	LevelState(Graphics & g);

	void initializeObjects(Graphics & g);

	void handleInput(Input& input);
	void draw(Graphics & g);
	void update(units::MS elapsedTime);
	

private:
	std::vector<std::shared_ptr<GameObject>> gameObjects;
	std::shared_ptr<Player> player;

};