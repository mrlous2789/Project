#pragma once
#include <string>
#include <SDL.h>
#include <iostream>

namespace Mer
{
	class UIElement
	{
	public:
		UIElement();
		UIElement(std::string name, int textureWidth, int textureHeight, float xPosScale, float yPosScale ,std::string type, bool visible, std::string parentName,SDL_Texture* uiTexture, std::string category, int screenWidth, int screenHeight);

		void CalculateRects(int screenWidth, int screenHeight);


		std::string getName();
		std::string getParentName();
		std::string  getType();
		std::string getCategory();

		SDL_Rect* getSRect();
		SDL_Rect* getDRect();

		SDL_Texture* getTexture();

		bool getVisible();
		void changeVisiblity();
		
	private:
		std::string name = "";
		int textureWidth = 0;
		int textureHeight = 0;
		float xPosScale = 0.0f;
		float yPosScale = 0.0f;
		std::string type = "";
		bool visible;
		std::string parentName = "";
		std::string category = "";



		SDL_Rect sRect;//source rect, size of texture
		SDL_Rect dRect;//destination rect where texture is on screen

		SDL_Texture* uiTexture;
	};
}


