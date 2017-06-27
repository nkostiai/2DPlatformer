#pragma once
#include "sprite.h"


class AnimatedSprite : public Sprite {
public:
	AnimatedSprite(Graphics& graphics, const std::string& filePath, int srcX, int srcY, int width, int height, int animation_fps, int numberOfFrames);

	void update(int elapsedTime);

private:

	const int frameTime;
	const int numberOfFrames;
	int currentFrame;

	//Since the last frame change
	int elapsedTime;


};