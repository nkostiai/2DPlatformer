#pragma once
#include "units.h"
class Graphics;
class Input;

class GameState {

public:
	virtual void handleInput(Input& input) = 0;
	virtual void update(units::MS elapsedTime) = 0;
	virtual void draw(Graphics& g) = 0;

private:

};