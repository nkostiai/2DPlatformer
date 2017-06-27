#include "player.h"
#include "sprite.h"
#include "globals.h"
#include <algorithm>

Player::Player(Graphics& g, units::position startX, units::position startY) :
	x(startX), y(startY), sprite(std::make_shared<Sprite>(Sprite(g, "player.png", 0, 0, 16, 32))){

	isGrounded = false;
	xVelocity = 0.0f;
	yVelocity = 0.0f;
	xAccelModifier = 0.0f;

}

void Player::draw(Graphics & g)
{
	sprite->draw(g, units::positionToPixel(x), units::positionToPixel(y));
}

void Player::update(units::MS elapsedTime)
{
	verticalMovement(elapsedTime);
	horizontalMovement(elapsedTime);
}

void Player::verticalMovement(units::MS elapsedTime) {
	units::position delta = 0.0f;
	//Update velocity
	//if not on ground apply gravity
	if (!isGrounded) {
		yVelocity += GRAVITY * elapsedTime;
		yVelocity = std::min(yVelocity, MAX_VERTICAL_SPEED);
	}
	delta = yVelocity * elapsedTime;

	verticalCollisions(delta);

}

void Player::verticalCollisions(units::position delta) {
	if (y + delta > 250) {
		y = 250;
		yVelocity = 0;
		isGrounded = true;
	}
	else {
		y += delta;
		isGrounded = false;
	}
}

void Player::horizontalMovement(units::MS elapsedTime) {
	//Update velocity
	xVelocity += ((HORIZONTAL_ACCELERATION * xAccelModifier) * elapsedTime);
	if (xAccelModifier < 0) {
		xVelocity = std::max(-MAX_HORIZONTAL_SPEED, xVelocity);
	}
	else if (xAccelModifier > 0) {
		xVelocity = std::min(MAX_HORIZONTAL_SPEED, xVelocity);
	}
	else {
		if (xVelocity < 0) {
			xVelocity += FRICTION * elapsedTime;
			xVelocity = std::min(xVelocity, 0.0f);
		}
		else if (xVelocity > 0) {
			xVelocity -= FRICTION * elapsedTime;
			xVelocity = std::max(xVelocity, 0.0f);
		}
	}

	//Calculate delta
	units::position delta = xVelocity * elapsedTime; //amount of movement
	//Handle collisions
	horizontalCollisions(delta);
	
}

void Player::horizontalCollisions(units::position delta) {
	x += delta;
}

void Player::move(globals::direction direction) {
	if (direction == globals::direction::LEFT) {
		xAccelModifier = -1;
	}
	else if (direction == globals::direction::RIGHT) {
		xAccelModifier = 1;
	}
	else {
		xAccelModifier = 0;
	}
}

void Player::jump() {
	if (isGrounded) {
		yVelocity = INITIAL_JUMP_VELOCITY;
		isGrounded = false;
	}
}
