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
		UIElement(std::string name, std::string textureName, int textureWidth, int textureHeight, int xPos, int yPos ,std::string type, bool visible, std::string parentName, std::string category, int screenWidth, int screenHeight);

		void CalculateRects(int screenWidth, int screenHeight);


		std::string getName();
		std::string getParentName();
		std::string  getType();
		std::string getCategory();
		std::string getTextureName();

		SDL_Rect* getSRect();
		SDL_Rect* getDRect();

		bool getVisible();
		void changeVisiblity();
		
	private:
		std::string name = "";
		std::string textureName = "";
		int textureWidth = 0;
		int textureHeight = 0;
		int xPos = 0;
		int yPos = 0;
		std::string type = "";
		bool visible;
		std::string parentName = "";
		std::string category = "";
		SDL_Rect sRect;//source rect, size of texture
		SDL_Rect dRect;//destination rect where texture is on screen


		float defaultScreenWidth = 1920.0f;
		float defaultScreenHeight = 1080.0f;

		float widthScale, heightScale;

	};
}


