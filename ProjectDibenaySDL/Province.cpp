#include "Province.h"
namespace Mer
{
	Province::Province()
	{
		provinceBorders = SDL_CreateRGBSurface(0, 1920, 1080, 32, 0, 0, 0, 0);
		pixels = (Uint32*)provinceBorders->pixels;
		format = provinceBorders->format;
	}
	Province::Province(std::string id, int red, int green, int blue, int screenWidth, int screenHeight)
	{
		this->id = id;
		this->red = red;
		this->green = green;
		this->blue = blue;
		provinceBorders = SDL_CreateRGBSurface(0, 1920, 1080, 32, 0, 0, 0, 0);
		pixels = (Uint32*)provinceBorders->pixels;
		format = provinceBorders->format;
		sRect.x = 0; sRect.y = 0; sRect.w = screenWidth; sRect.h = screenHeight;
		dRect.x = 0; dRect.y = 0; dRect.w = screenWidth; dRect.h = screenHeight;
	}

	int Province::getRed()
	{
		return red;
	}
	int Province::getGreen()
	{
		return green;
	}
	int Province::getBlue()
	{
		return blue;
	}
	std::string Province::getID()
	{
		return id;
	}

	void Province::MapPixelColour(int x, int y, int red, int green, int blue, int alpha)
	{
		Uint32 color = SDL_MapRGBA(format, red, green, blue, alpha);
		pixels[(y * provinceBorders->w) + x] = color;
		
	}

	SDL_Texture* Province::getTexture()
	{
		return provinceTexture;
	}
	SDL_Surface* Province::getSurface()
	{
		return provinceBorders;
	}

	void Province::ConvertToTexture(SDL_Renderer* renderer)
	{
		provinceTexture = SDL_CreateTextureFromSurface(renderer, provinceBorders);
	}
	SDL_Rect* Province::getSRect()
	{
		return &sRect;
	}
	SDL_Rect* Province::getDRect()
	{
		return &dRect;
	}
}
