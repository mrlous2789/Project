#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include "Province.h"
#include "DEFINITIONS.h"

namespace Mer
{
	class Nation
	{
	public:
		Nation();
		Nation(std::string name, std::vector<Province*> provinces,int red, int green, int blue);

		int getRed();
		int getGreen();
		int getBlue();		
		std::string getName();

		void processMap(SDL_Renderer* &renderer);
		
		SDL_Texture* getMap();
		SDL_Surface* getSurface();

	private:
		SDL_Surface* nationBorders;
		SDL_Texture* map;
		std::string name;
		std::string capitalProvince;
		int red;
		int green;
		int blue;

		SDL_Rect sRect;
		SDL_Rect dRect;

		void WipeMap();
		
		std::vector<Province*> provinces;
		
	};
}


