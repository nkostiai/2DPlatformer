#pragma once
#include "units.h"
class Graphics;
class Input;

class GameObject {
public:	 
	virtual void draw(Graphics& g) = 0;
	virtual void update(units::MS elapsedTime) = 0;
	GameObject();

private:

};