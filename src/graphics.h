#pragma once
#include <map>
#include "globals.h"
struct SDL_Texture;
struct SDL_Rect;
struct SDL_Surface;
struct SDL_Renderer;
struct SDL_Point;


class Graphics {

public:
	Graphics();
	~Graphics();

	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;

	SDL_Texture* loadImage(const std::string& fileName);

	void renderTexture(SDL_Texture * tex, const SDL_Rect destination, const SDL_Rect * clip, globals::verticalFacing facing, int degrees) const;

	void renderTexture(SDL_Texture * tex, const int destX, const int destY, const SDL_Rect * clip, globals::verticalFacing facing, int degrees) const;

	void flip() const;
	void clear() const;
	

private:
	//The window
	struct SDL_Window* gWindow;

	//Renderer
	struct SDL_Renderer* gRenderer;

	SDL_Point* getCenterFromTexture(SDL_Texture* tex);

	//Map of sprite sheets
	std::map<std::string, SDL_Texture*> spriteSheets;
};