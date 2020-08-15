#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
namespace Mer
{
	class Nation
	{
	public:
		Nation();
		Nation(std::string name, std::string capitalProvince, int red, int green, int blue);

		int getRed();
		int getGreen();
		int getBlue();		
		std::string getName();
	private:
		SDL_Surface* nationBorders;
		std::string name;
		std::string capitalProvince;
		int red;
		int green;
		int blue;
	};
}


