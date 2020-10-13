#include "Province.h"
namespace Mer
{
	Province::Province()
	{
		provinceBorders = SDL_CreateRGBSurface(0, 1920, 1080, 32, 0, 0, 0, 0);
		pixels = (Uint32*)provinceBorders->pixels;
		format = provinceBorders->format;
	}
	Province::Province(std::string id, Uint8 red, Uint8 green, Uint8 blue, int screenWidth, int screenHeight)
	{
		this->id = id;
		this->red = red;
		this->green = green;
		this->blue = blue;
		Uint32 rmask, gmask, bmask, amask;
		rmask = 0x00;gmask = 0x00;bmask = 0x00;amask = 0x00;

		provinceBorders = SDL_CreateRGBSurface(0, 3840, 2160, 32, rmask, gmask, bmask, amask);
		provinceBorders = SDL_ConvertSurfaceFormat(provinceBorders, SDL_PIXELFORMAT_RGBA8888, 0);
		SDL_FillRect(provinceBorders, NULL, SDL_MapRGBA(provinceBorders->format, 0, 0, 0, 0));
		pixels = (Uint32*)provinceBorders->pixels;
		format = provinceBorders->format;
		sRect.x = 0; sRect.y = 0; sRect.w = 3840; sRect.h = 2160;
		dRect.x = 0; dRect.y = 0; dRect.w = screenWidth; dRect.h = screenHeight;
	}

	Uint8 Province::getRed()
	{
		return red;
	}
	Uint8 Province::getGreen()
	{
		return green;
	}
	Uint8 Province::getBlue()
	{
		return blue;
	}
	std::string Province::getID()
	{
		return id;
	}

	void Province::MapPixelColour(int x, int y, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
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
