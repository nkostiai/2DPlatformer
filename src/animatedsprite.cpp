#include "animatedsprite.h"
#include "Globals.h"

AnimatedSprite::AnimatedSprite(Graphics& graphics, const std::string & filePath, int srcX, int srcY, int width, int height, int animation_fps, int numberOfFrames) :
	Sprite(graphics, filePath, srcX, srcY, width, height), frameTime(1000 / animation_fps), numberOfFrames(numberOfFrames), currentFrame(0), elapsedTime(0)
{

}

void AnimatedSprite::update(int elapsedTime) {
	this->elapsedTime += elapsedTime;
	if (this->elapsedTime > frameTime) {

		currentFrame++;

		elapsedTime = 0;
		if (currentFrame < numberOfFrames) {
			sourceRect.x += this->sourceRect.w;
		}
		else {
			sourceRect.x -= (numberOfFrames - 1) * this->sourceRect.w;
			currentFrame = 0;
		}
		this->elapsedTime = 0;
	}
}
