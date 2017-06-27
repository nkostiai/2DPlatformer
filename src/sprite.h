#pragma once
#include <string>
#include <vector>
#include <SDL.h>


class Graphics;

class Sprite {

public:
	Sprite(Graphics& graphics, const std::string& fileName, const int srcX, const int srcY, const int width, const int height);
	virtual ~Sprite() = default;

	Sprite& operator=(const Sprite&) = delete;

	virtual void update(int elapsedTime) {};

	void draw(Graphics &g, const int x, const int y) const;

private:
	SDL_Texture *texture;

protected:
	SDL_Rect sourceRect;
};