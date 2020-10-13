#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>

namespace Mer
{
	class Province
	{
	public:
		Province();
		Province(std::string id, Uint8 red, Uint8 green, Uint8  blue, int screenWidth, int ScreenHeight);

		Uint8 getRed();
		Uint8 getGreen();
		Uint8 getBlue();
		std::string getID();

		void MapPixelColour(int x, int y, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);

		SDL_Texture* getTexture();
		SDL_Surface* getSurface();

		SDL_Rect* getSRect();
		SDL_Rect* getDRect();

		void ConvertToTexture(SDL_Renderer* renderer);
	private:
		SDL_Surface* provinceBorders;
		SDL_PixelFormat* format;
		Uint32* pixels;
		SDL_Texture* provinceTexture;
		std::string id = "";
		Uint8 red = 0;
		Uint8 green = 0;
		Uint8 blue = 0;

		SDL_Rect sRect;
		SDL_Rect dRect;
	};
}


