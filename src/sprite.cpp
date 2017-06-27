#include "sprite.h"
#include "graphics.h"

Sprite::Sprite(Graphics& graphics, const std::string & fileName, const int srcX, const int srcY, const int width, const int height):
	texture{graphics.loadImage(fileName.c_str())},
	sourceRect{srcX, srcY, width, height}
{

}

void Sprite::draw(Graphics & g, const int x, const int y, globals::verticalFacing facing, int degrees) const
{
	g.renderTexture(this->texture, x, y, &sourceRect, facing, degrees);
}

