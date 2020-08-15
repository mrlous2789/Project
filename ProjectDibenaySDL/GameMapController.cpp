#include "GameMapController.h"
namespace Mer
{
	GameMapController::GameMapController()
	{

	}
	void GameMapController::Init(AssetManager *am, int screenWidth, int screenHeight, SDL_Renderer* &renderer)
	{
		this->am = am;
		this->renderer = renderer;
		//SDL_QueryTexture(this->am->getTexture("map_coloured_layer"), NULL, NULL, &mapW, &mapH);
		UpdateScreenResolution(screenWidth, screenHeight);
		//CalculateNations(NATIONS_DATA_FILE);
		CalculateProvinces(PROVINCES_DATA_FILE);
		UpdateMapRect();
		sRect.x = 0; sRect.y = 0; sRect.w = screenWidth; sRect.h = screenHeight;
		dRect.x = 0; dRect.y = 0; dRect.w = screenWidth; dRect.h = screenHeight;
	}
	void GameMapController::UpdateMap()
	{
		if (zoomin || zoomInFalloff)
		{
			ProcessZoomIn();
		}
		if (zoomout || zoomOutFalloff)
		{
			ProcessZoomOut();
		}
	}
	void GameMapController::ProcessZoomIn()
	{

	}
	void GameMapController::ProcessZoomOut()
	{
		
	}
	void GameMapController::UpdateMapRect()
	{
		float scaleX, scaleY;
		

		mapDRect.x = 0; mapDRect.y = 0; mapDRect.w = screenWidth; mapDRect.h = screenHeight;

		mapSRect.x = 0; mapSRect.y = 0; mapSRect.w = screenWidth * zoomLevel; mapSRect.h = screenHeight * zoomLevel;
		
	}

	void GameMapController::RenderMap()
	{
		//SDL_RenderCopy(renderer, am->getTexture("map_coloured_layer"),&mapSRect, &mapDRect);
		//SDL_RenderCopy(renderer, am->getTexture("map_base_layer"), &sRect, &dRect);
		RenderProvinces();
	}
	void GameMapController::setZoomIn(bool set)
	{
		zoomin = set; zoomInFalloff = set; currentFalloff = 0.0f;
	}
	void GameMapController::setZoomOut(bool set)
	{
		zoomout = set; zoomOutFalloff = set; currentFalloff = 0.0f;
	}

	void GameMapController::UpdateScreenResolution(int screenWidth, int screenHeight)
	{
		this->screenWidth = screenWidth;
		this->screenHeight = screenHeight;
		
		int tmp =  mapW / screenWidth;
		int tmp2 = mapH / screenHeight;

		if (tmp2 < tmp)
		{
			maxZoom = tmp2;
		}
		else
		{
			maxZoom = tmp;
		}

		zoomLevel = minZoom;
		zoomSpeed = minZoom / 10.0f;

		UpdateMapRect();
	}

	void GameMapController::setSpeed(float speed)
	{
		wheelSpeed = speed;
	}

	void GameMapController::CalculateNations(std::string filename)
	{
		std::ifstream file;
		file.open(filename);
		
		std::string line;
		while (std::getline(file,line))
		{
			std::string name, capital;
			int red, green, blue;
			int nameBr = 0, capitalBr = 0, redBr = 0, greenBr = 0;
			for (int i = 0; i < line.size(); i++)// find break points between data
			{
				if (line[i] == ':')
				{
					if (nameBr == 0)
					{
						nameBr = i;
					}
					else if(capitalBr == 0)
					{
						capitalBr = i;
					}
					else if (redBr == 0)
					{
						redBr = i;
					}
					else if (greenBr == 0)
					{
						greenBr = i;
					}
				}
			} 
			name = line.substr(0, nameBr);
			capital = line.substr(nameBr + 1, (capitalBr - nameBr) - 1);
			red = std::stoi(line.substr(capitalBr + 1, (redBr - capitalBr) - 1));
			green = std::stoi(line.substr(redBr + 1, (greenBr - redBr) - 1));
			blue = std::stoi(line.substr(greenBr + 1, (line.size() -greenBr) - 1));

			_nations.push_back(Nation(name, capital, red, green, blue));
			std::cout << "GMC: " << name << " " << capital << " " <<" R: "<< red << " " << " G: " << green << " " << " B: " << blue << std::endl;
			
		}

		file.close();

		CalculateBorders("map_provinces_layer");

	}
	void GameMapController::CalculateProvinces(std::string filename)
	{
		std::ifstream file;
		file.open(filename);

		std::string line;
		while (std::getline(file, line))
		{
			std::string id;
			int red, green, blue;
			int nameBr = 0, redBr = 0, greenBr = 0;
			for (int i = 0; i < line.size(); i++)// find break points between data
			{
				if (line[i] == ':')
				{
					if (nameBr == 0)
					{
						nameBr = i;
					}
					else if (redBr == 0)
					{
						redBr = i;
					}
					else if (greenBr == 0)
					{
						greenBr = i;
					}
				}
			}
			id = line.substr(0, nameBr);
			red = std::stoi(line.substr(nameBr + 1, (redBr - nameBr) - 1));
			green = std::stoi(line.substr(redBr + 1, (greenBr - redBr) - 1));
			blue = std::stoi(line.substr(greenBr + 1, (line.size() - greenBr) - 1));

			
			_provinces.push_back(Province(id, red, green, blue, screenWidth, screenHeight));
			std::cout << "GMC: " << id << " " << " R: " << red << " " << " G: " << green << " " << " B: " << blue << std::endl;

		}

		file.close();

		CalculateBorders("map_provinces_layer");
	}

	void GameMapController::CalculateBorders(std::string mapFile)
	{
		SDL_PixelFormat* fmt;
		Uint8 index;
		Uint32 temp, pixel;
		Uint32* pixels = (Uint32*)am->getSurface(mapFile)->pixels;

		Uint8 tempR, tempG, tempB, tempA;

		fmt = am->getSurface(mapFile)->format;
		SDL_LockSurface(am->getSurface(mapFile));
		


		for (Uint32 x = 1; x < am->getSurface(mapFile)->w; x++)
		{
			for (Uint32 y = 1; y < am->getSurface(mapFile)->h; y++)
			{
				//pixel = pixels[(y * _mapFiles.getSurface("map_nations_layer")->w) + x];
				SDL_GetRGBA(pixels[(y * am->getSurface(mapFile)->w) + x], fmt, &tempR, &tempG, &tempB, &tempA);
				int pixelRed = tempR; int pixelGreen = tempG; int pixelBlue = tempB;
				for (int i = 0; i < _provinces.size(); i++)
				{
					if (_provinces[i].getRed() == tempR && _provinces[i].getGreen() == tempG && _provinces[i].getBlue() == tempB)
					{
						_provinces[i].MapPixelColour(x, y, pixelRed, pixelGreen, pixelBlue, 180);
					}
					else
					{
						_provinces[i].MapPixelColour(x, y, 0, 0, 0, 0);
					}
				}
			}
		}

		std::cout << "Border Done" << std::endl;


		SDL_UnlockSurface(am->getSurface("map_nations_layer"));
		FinaliseLoading();
	}

	void GameMapController::FinaliseLoading()
	{
		for (int i = 0; i < _provinces.size(); i++)
		{
			am->LoadTexture(_provinces[i].getID(), renderer, _provinces[i].getSurface());
			if (SDL_SetTextureBlendMode(am->getTexture(_provinces[i].getID()), SDL_BLENDMODE_ADD) < 0)
			{
				std::cout << "Error " << std::endl;
			}
			
		}
	}

	void GameMapController::RenderProvinces()
	{
		for (int i = 0; i < _provinces.size(); i++)
		{
			SDL_RenderCopy(renderer, am->getTexture(_provinces[i].getID()), _provinces[i].getSRect(), _provinces[i].getDRect());
		}
	}
}
