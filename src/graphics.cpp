#include "graphics.h"
#include <SDL.h>
#include <SDL_image.h> 
#include <iostream>
#include "Globals.h"
#define LOG(x) (std::cout << x << std::endl);


Graphics::Graphics()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("Platformer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, globals::RES_WIDTH, globals::RES_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	if (!success)
	{
		LOG("Creating graphics failed");
	}
}

Graphics::~Graphics()
{
	for (std::map<std::string, SDL_Texture*>::iterator it = spriteSheets.begin(); it != spriteSheets.end(); ++it)
	{
		SDL_DestroyTexture(it->second);
	}
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
}

//Loads and stores a texture to the sprite sheets map
SDL_Texture * Graphics::loadImage(const std::string & fileName)
{
	const std::string filePath = "resources/spritesheets/"+fileName;

	if (spriteSheets.count(fileName) == 0) {
		SDL_Texture* texture;
		texture = IMG_LoadTexture(gRenderer, filePath.c_str());
		if (!texture) {
			LOG("Error loading texture " << filePath.c_str());
		}
		spriteSheets[filePath] = texture;
	}
	return spriteSheets[filePath];
}

void Graphics::renderTexture(SDL_Texture * tex, const SDL_Rect destination, const SDL_Rect * clip, globals::verticalFacing facing, int degrees) const
{
	if (facing != globals::verticalFacing::RIGHT || degrees != 0) {
		LOG("facing other way");
		int width, height;
		SDL_QueryTexture(tex, NULL, NULL, &width, &height);
		SDL_Point center = { width, height };
		SDL_RenderCopyEx(gRenderer, tex, clip, &destination, degrees, &center, SDL_FLIP_HORIZONTAL);
	}
	else {
		SDL_RenderCopy(gRenderer, tex, clip, &destination);
	}
}

void Graphics::renderTexture(SDL_Texture * tex, const int destX, const int destY, const SDL_Rect * clip, globals::verticalFacing facing, int degrees) const
{
	//Destination rectangle
	SDL_Rect destination;

	//Coordinates where drawn on the screen
	destination.x = destX;
	destination.y = destY;

	//Take the width and height of the clip if given
	if (clip != nullptr) {
		destination.w = clip->w;
		destination.h = clip->h;
	} else {
		//If not clipped, query the dimensions from the texture
		SDL_QueryTexture(tex, nullptr, nullptr, &destination.w, &destination.h);
	}
	
	renderTexture(tex, destination, clip, facing, degrees);
}

void Graphics::flip() const
{
	SDL_RenderPresent(gRenderer);
}

void Graphics::clear() const
{
	SDL_RenderClear(gRenderer);
}

