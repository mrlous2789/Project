#include "UIElement.h"

namespace Mer
{
	UIElement::UIElement()
	{

	}
	UIElement::UIElement(std::string name, int textureWidth, int textureHeight, float xPosScale, float yPosScale, std::string type, bool visible, std::string parentName, SDL_Texture* uiTexture, std::string category,int screenWidth, int screenHeight)
	{
		this->name = name;
		this->type = type;
		this->textureWidth = textureWidth;
		this->textureHeight = textureHeight;
		this->xPosScale = xPosScale;
		this->yPosScale = yPosScale;
		this->uiTexture = uiTexture;
		this->category = category;
		this->parentName = parentName;
		this->visible = visible;
	}

	void UIElement::CalculateRects(int screenWidth, int screenHeight)
	{
		sRect.x = 0;
		sRect.y = 0;
		sRect.w = textureWidth;
		sRect.h = textureHeight;

		std::cout << "Width: " << screenWidth << " Height: " << screenHeight << std::endl;

		dRect.x = (screenWidth * xPosScale) - (textureWidth / 2);
		dRect.y = (screenHeight * yPosScale) - (textureHeight / 2);
		dRect.w = textureWidth;
		dRect.h = textureHeight;

		std::cout << dRect.x << " " << dRect.y << std::endl;
	}

	std::string UIElement::getName()
	{
		return name;
	}
	std::string UIElement::getParentName()
	{
		return parentName;
	}
	std::string UIElement::getType()
	{
		return type;
	}

	SDL_Rect* UIElement::getSRect()
	{
		return &sRect;
	}
	SDL_Rect* UIElement::getDRect()
	{
		return &dRect;
	}

	SDL_Texture* UIElement::getTexture()
	{
		return this->uiTexture;
	}

	bool UIElement::getVisible()
	{
		return visible;
	}

	void UIElement::changeVisiblity()
	{
		if (visible)
		{
			visible = false;
			std::cout << name <<" hidden" << std::endl;
		}
		else
		{
			visible = true;
			std::cout << name << " visible" << std::endl;
		}
	}
}