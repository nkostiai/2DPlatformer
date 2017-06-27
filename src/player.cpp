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

	float delta = xVelocity * elapsedTime; //amount of movement

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
