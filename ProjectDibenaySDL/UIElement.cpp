#include "UIElement.h"

namespace Mer
{
	UIElement::UIElement()
	{

	}
	UIElement::UIElement(std::string name,std::string textureName ,int textureWidth, int textureHeight, int xPos, int yPos, std::string type, bool visible, std::string parentName, std::string category,int screenWidth, int screenHeight)
	{
		this->name = name;
		this->textureName = textureName;
		this->type = type;
		this->textureWidth = textureWidth;
		this->textureHeight = textureHeight;
		this->xPos = xPos;
		this->yPos = yPos;
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

		widthScale = screenWidth / defaultScreenWidth; heightScale = screenHeight / defaultScreenHeight;

		dRect.x = xPos * widthScale - (textureWidth / 2);
		dRect.y = yPos * heightScale - (textureHeight / 2);
		dRect.w = textureWidth;
		dRect.h = textureHeight;

		if (dRect.x < 0)
		{
			dRect.x = 0;
		}
		if (dRect.y < 0)
		{
			dRect.y = 0;
		}
		if (dRect.x  + textureWidth > screenWidth)
		{
			dRect.x = screenWidth - textureWidth;
		}
		if (dRect.y + textureHeight > screenHeight)
		{
			dRect.y = screenHeight - textureHeight;
		}
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
	std::string UIElement::getCategory()
	{
		return category;
	}
	std::string UIElement::getTextureName()
	{
		return textureName;
	}

	SDL_Rect* UIElement::getSRect()
	{
		return &sRect;
	}
	SDL_Rect* UIElement::getDRect()
	{
		return &dRect;
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
		}
		else
		{
			visible = true;
		}
	}
}