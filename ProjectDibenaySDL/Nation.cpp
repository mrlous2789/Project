#include "Nation.h"
namespace Mer
{
	Nation::Nation()
	{

	}
	Nation::Nation(std::string name, std::vector<Province*> provinces, int red, int green, int blue)
	{
		this->name = name; 
		this->capitalProvince = capitalProvince;
		this->red = red;
		this->green = green; 
		this->blue = blue;
		this->provinces = provinces;

		Uint32 rmask, gmask, bmask, amask;
		rmask = 0x00; gmask = 0x00; bmask = 0x00; amask = 0x00;

		nationBorders = SDL_CreateRGBSurface(0, 3840, 2160, 32, rmask, gmask, bmask, amask);
		nationBorders = SDL_ConvertSurfaceFormat(nationBorders, SDL_PIXELFORMAT_RGBA8888, 0);
		SDL_FillRect(nationBorders, NULL, SDL_MapRGBA(nationBorders->format, 0, 0, 0, 0));
		
	}

	int Nation::getRed()
	{
		return red;
	}
	int Nation::getGreen()
	{
		return green;
	}
	int Nation::getBlue()
	{
		return blue;
	}
	std::string Nation::getName()
	{
		return name;
	}

	SDL_Texture* Nation::getMap()
	{
		return map;
	}

	SDL_Surface* Nation::getSurface()
	{
		return nationBorders;
	}

	void Nation::processMap(SDL_Renderer* &renderer)
	{
		WipeMap();




		//MIGHT NEED THIS LATER 
		for (int i = 0; i < provinces.size(); i++)
		{
			SDL_BlitSurface(provinces[i]->getSurface(), NULL, nationBorders, NULL);
		}

		//map = SDL_CreateTextureFromSurface(renderer, nationBorders);
	}

	void Nation::WipeMap()
	{
		SDL_LockSurface(nationBorders);
		SDL_memset(nationBorders->pixels, 0, nationBorders->h * nationBorders->pitch);
		SDL_UnlockSurface(nationBorders);
	}
}