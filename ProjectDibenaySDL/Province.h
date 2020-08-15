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
		Province(std::string id, int red, int green, int  blue, int screenWidth, int ScreenHeight);

		int getRed();
		int getGreen();
		int getBlue();
		std::string getID();

		void MapPixelColour(int x, int y, int red, int green, int blue, int alpha);

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
		int red = 0;
		int green = 0;
		int blue = 0;

		SDL_Rect sRect;
		SDL_Rect dRect;
	};
}


