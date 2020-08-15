#include "UIController.h"
namespace Mer
{
	//some sort of process that deals with ui that cant be on screen at the same time, making all neccesary ui is on screen at correct time etc
	UIController::UIController()
	{

	}
	void UIController::ProccessUIFile(std::string uiFileLocation, int screenWidth, int screenHeight)
	{
		std::ifstream file;
		file.open(uiFileLocation);
		std::string line;

		this->screenWidth = screenWidth;
		this->screenHeight = screenHeight;

		while (std::getline(file,line))
		{
			std::string name, textureName, textureWidthS, textureHeightS, xPosS, yPosS, type, visibleS, parentName, category;
			int nameBr = 0, textureNameBr = 0, textureWidthSBr = 0, textureHeightSBr = 0, xPosSBr = 0, yPosSBr = 0, typeBr = 0, visibleSBr= 0, categoryBr = 0;
			for (int i = 0; i < line.size() - 1; i++)
			{
				if (line[i] == ':')
				{
					if (nameBr == 0)
					{
						nameBr = i;
					}
					else if (textureNameBr == 0)
					{
						textureNameBr = i;
					}
					else if (textureWidthSBr == 0)
					{
						textureWidthSBr = i;
					}
					else if (textureHeightSBr == 0)
					{
						textureHeightSBr = i;
					}
					else if (xPosSBr == 0)
					{
						xPosSBr = i;
					}
					else if (yPosSBr == 0)
					{
						yPosSBr = i;
					}
					else if (typeBr == 0)
					{
						typeBr = i;
					}
					else if (visibleSBr == 0)
					{
						visibleSBr = i;
					}
					else if (categoryBr == 0)
					{
						categoryBr = i;
					}
				}
				
			}
			name = line.substr(0, nameBr);
			textureName = line.substr(nameBr + 1, (textureNameBr - nameBr) - 1);
			textureWidthS = line.substr(textureNameBr + 1, (textureWidthSBr - textureNameBr) - 1);
			textureHeightS = line.substr(textureWidthSBr + 1, (textureHeightSBr - textureWidthSBr) - 1);
			xPosS = line.substr(textureHeightSBr + 1, (xPosSBr - textureHeightSBr) - 1);
			yPosS = line.substr(xPosSBr + 1, (yPosSBr - xPosSBr) - 1);
			type = line.substr(yPosSBr + 1, (typeBr - yPosSBr) - 1);
			visibleS = line.substr(typeBr + 1, (visibleSBr - typeBr) - 1);
			category = line.substr(visibleSBr + 1, (categoryBr - visibleSBr) - 1);
			if (line.back() == ' ')
			{
				parentName = "";
			}
			else
			{
				parentName = line.substr(categoryBr + 1, (line.size() - categoryBr) - 1);
			}

			AddElement(name, textureName, CtI(textureWidthS), CtI(textureHeightS), CtI(xPosS), CtI(yPosS), type, CtB(visibleS), parentName, category,screenWidth, screenHeight);
		}

		UpdateChildrenVisiblity();
	}
	void UIController::ProcessUIChanges()
	{
		if (_visibilityChange)
		{
			UpdateChildrenVisiblity();
			_visibilityChange = false;
		}
		if (_resolutionChange)
		{
			for (int i = 0; i < uiElementsB.size(); i++)
			{
				uiElementsB[i].CalculateRects(screenWidth, screenHeight);
			}
			for (int i = 0; i < uiElementsI.size(); i++)
			{
				uiElementsI[i].CalculateRects(screenWidth, screenHeight);
			}
			_resolutionChange = false;
		}

	}

	void UIController::AddElement(std::string name, std::string textureName, int textureWidth, int textureHeight, int xPos, int yPos, std::string type, bool visible, std::string parentName, std::string category,int screenWidth, int screenHeight)
	{
		if (category == "action_button")
		{
			uiElementsB.push_back(UIElement(name, textureName ,textureWidth, textureHeight, xPos, yPos, type, visible, parentName, category, screenWidth, screenHeight));
			uiElementsB.back().CalculateRects(screenWidth, screenHeight);
		}
		else if (category == "ui_image")
		{
			uiElementsI.push_back(UIElement(name, textureName,textureWidth, textureHeight, xPos, yPos, type, visible, parentName, category, screenWidth, screenHeight));
			uiElementsI.back().CalculateRects(screenWidth, screenHeight);
		}
		else
		{
			std::cout << category << "UIC: Bad category" << std::endl;
		}

	}
	int UIController::CtI(std::string input)
	{
		return std::stoi(input);
	}
	bool UIController::CtB(std::string input)
	{
		if (input == "1")
		{
			return true;
		}
		else if(input == "0")
		{
			return false;
		}
		else
		{
			std::cout << "UIC: bad visiiblity input setting to false " << std::endl;
			return false;
		}
	}
	float UIController::CtF(std::string input)
	{
		return std::stof(input);
	}

	void UIController::initUI(SDL_Renderer* &renderer, AssetManager *_am)
	{
		currentRenderer = renderer;
		am = _am;
	}
	void UIController::RenderUI()
	{
		for (int i = 0; i < uiElementsI.size(); i++)
		{
			if (uiElementsI[i].getVisible())
			{
				SDL_RenderCopy(currentRenderer, am->getTexture(uiElementsI[i].getTextureName()), uiElementsI[i].getSRect(), uiElementsI[i].getDRect());
			}
		}
		for (int i = 0; i < uiElementsB.size(); i++)
		{
			if (uiElementsB[i].getVisible())
			{
				SDL_RenderCopy(currentRenderer, am->getTexture(uiElementsB[i].getTextureName()), uiElementsB[i].getSRect(), uiElementsB[i].getDRect());
			}
		}
	}

	void UIController::ClearUI()
	{
		uiElementsB.clear();
		uiElementsI.clear();
	}

	int UIController::getButtonElementsSize()
	{
		return uiElementsB.size();
	}
	SDL_Rect* UIController::getButtonElementDRect(int element)
	{
		if (uiElementsB[element].getVisible())
		{
			return uiElementsB[element].getDRect();
		}
		else
		{
			SDL_Rect hiddenRect;
			hiddenRect.x = -100;
			hiddenRect.y = -100;
			hiddenRect.w = 0;
			hiddenRect.y = 0;
			return &hiddenRect;
		}


	}
	std::string UIController::getButtonElementName(int element)
	{
		return uiElementsB[element].getName();
	}
	int UIController::getParentByName(std::string name)
	{
		for (int i = 0; i < uiElementsI.size(); i++)
		{
			if (uiElementsI[i].getName() == name)
			{
				return i;
			}
		}
		return -1;
	}

	void UIController::changeParentVisibility(std::string name)
	{
		uiElementsI[getParentByName(name)].changeVisiblity();
		_visibilityChange = true;
	}

	void UIController::signalResolutionChange(int screenWidth, int screenHeight)
	{
		_resolutionChange = true;
		this->screenWidth = screenWidth;
		this->screenHeight = screenHeight;
	}
	void UIController::UpdateChildrenVisiblity()
	{
		for (int i = 0; i < uiElementsB.size(); i++)
		{
			if (uiElementsI[getParentByName((uiElementsB[i].getParentName()))].getVisible() != uiElementsB[i].getVisible())
			{
				uiElementsB[i].changeVisiblity();
			}
		}
	}
}