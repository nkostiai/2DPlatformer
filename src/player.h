#pragma once
#include "GameObject.h"
#include "units.h"
#include "globals.h"

#include <memory>

class Sprite;

namespace {
	//Player constants
	units::acceleration GRAVITY = 0.00450f;

	units::acceleration FRICTION = 0.001434f;

	units::acceleration HORIZONTAL_ACCELERATION = 0.00325f;

	units::velocity MAX_HORIZONTAL_SPEED = 0.325f;
	units::velocity MAX_VERTICAL_SPEED = 0.325f;
	units::velocity INITIAL_JUMP_VELOCITY = 0.500f;
}

class Player : public GameObject {



public:
	Player(Graphics& g, units::position startX, units::position startY);
	void draw(Graphics& g);
	void update(units::MS elapsedTime);
	void move(globals::direction direction);

private:
	void verticalMovement(units::MS elapsedTime);
	void horizontalMovement(units::MS elapsedTime);
	units::position x, y;
	units::velocity xVelocity, yVelocity;
	bool isGrounded;
	units::acceleration xAccelModifier;
	std::shared_ptr<Sprite> sprite;

};