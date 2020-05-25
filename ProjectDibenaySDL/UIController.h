#pragma once
#include "UIElement.h"
#include <fstream>
#include <vector>
#include <map>
#include <SDL_image.h>
#include "AssetManager.h"

namespace Mer
{
	class UIController
	{
	public:
		UIController();
		
		void ProccessUIFile(std::string uiFileLocation, int screenWidth, int screenHeight);

		void ProcessUIChanges();
		
		void initUI(SDL_Renderer*& renderer, AssetManager *_am);

		void RenderUI();

		void ClearUI();

		int getButtonElementsSize();
		SDL_Rect* getButtonElementDRect(int element);
		std::string getButtonElementName(int element);

		void changeParentVisibility(std::string name);

		void signalResolutionChange(int screenWidth, int screenHeight);

	private:
		std::vector<UIElement> uiElementsB; //buttons
		std::vector<UIElement> uiElementsI; //images

		bool _visibilityChange;
		bool _resolutionChange;

		AssetManager *am;

		void AddElement(std::string name, std::string textureName, int textureWidth, int textureHeight, float xPosScale, float yPosScale, std::string type, bool visible, std::string parentName, std::string category,int screenWidth, int screenHeight);
		int CtI(std::string input);
		bool CtB(std::string input);
		float CtF(std::string input);

		int screenWidth;
		int screenHeight;

		void UpdateChildrenVisiblity();

		SDL_Renderer* currentRenderer;

		int getParentByName(std::string name);
	};
}


