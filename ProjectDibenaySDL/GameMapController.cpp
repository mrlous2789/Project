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
		LoadProvinces(PROVINCES_DATA_FILE);
		LoadNations(NATIONS_DATA_FILE);

		//SDL_SetTextureBlendMode(am->getTexture("map_base_layer"), SDL_BLENDMODE_MOD);

		UpdateMapRect();
		sRect.x = 0; sRect.y = 0; sRect.w = MAP_WIDTH; sRect.h = MAP_HEIGHT;
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
		SDL_RenderCopy(renderer, am->getTexture("map_base_layer"), &sRect, &dRect);
		//RenderProvinces();
		RenderNations();
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

	void GameMapController::LoadNations(std::string filename)
	{
		std::ifstream file;
		file.open(filename);
		
		std::string line;
		int provinceCounter = 0;

		std::vector<Province*> natProvinces;
		std::vector<std::string> lineVector;
		
		while (std::getline(file,line)) 
		{
			std::stringstream linestream(line);

			std::string segment;

			natProvinces.clear();
			lineVector.clear();

			std::cout << line << std::endl;

			std::string name = "";

			Uint8 red = 0, green = 0, blue = 0;

			while (std::getline(linestream,segment, ':'))
			{
				lineVector.push_back(segment);
				std::cout << lineVector.size() << std::endl;

				//_nations.push_back(Nation(name, capital, red, green, blue));
				//std::cout << "GMC: " << name << " " << capital << " " <<" R: "<< red << " " << " G: " << green << " " << " B: " << blue << std::endl;

			}

			for (int i = 0; i < lineVector.size(); i++)
			{
				if (i == 0)
				{
					name = lineVector[i];
				}
				else if (i == 1)
				{
					red = std::stoi(lineVector[i]);
				}
				else if (i == 2)
				{
					green = std::stoi(lineVector[i]);
				}
				else if (i == 3)
				{
					blue = std::stoi(lineVector[i]);
				}
				else if (i >= 4)
				{
					for (int j = 0; j < _provinces.size(); j++)
					{
						if (lineVector[i] == _provinces[j].getID())
						{
							natProvinces.push_back(&_provinces[j]);
						}
					}
				}
			}
			for (int i = 0; i < natProvinces.size(); i++)
			{
				std::cout << natProvinces[i]->getID() << std::endl;
			}



			_nations.push_back(Nation(name, natProvinces, red, green, blue));
		}


		file.close();

		//CalculateNationBorders();
		FinaliseLoading();
	}

	void GameMapController::CalculateNationBorders()
	{

	}

	void GameMapController::LoadProvinces(std::string filename)
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

		CalculateProvinceBorders("map_provinces_layer");
	}

	void GameMapController::CalculateProvinceBorders(std::string mapFile)
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
						_provinces[i].MapPixelColour(x, y, _provinces[i].getRed(), _provinces[i].getGreen(), _provinces[i].getBlue(), 150);
					}
					else
					{
						_provinces[i].MapPixelColour(x, y, 0x00, 0x00, 0x00, 0x00);
					}
				}
			}
		}

		std::cout << "Border Done" << std::endl;


		//SDL_UnlockSurface(am->getSurface("map_nations_layer"));
		
	}

	void GameMapController::FinaliseLoading()
	{
		for (int i = 0; i < _provinces.size(); i++)
		{
			SDL_SetSurfaceBlendMode(_provinces[i].getSurface(), SDL_BLENDMODE_BLEND);
			am->LoadTexture(_provinces[i].getID(), renderer, _provinces[i].getSurface());
			if (SDL_SetTextureBlendMode(am->getTexture(_provinces[i].getID()), SDL_BLENDMODE_BLEND) < 0)
			{
				std::cout << "GMC: Provinces texture blend mode error " << std::endl;
			}			
		}

		for (int i = 0; i < _nations.size(); i++)
		{		
			_nations[i].processMap(renderer);
			am->LoadTexture(_nations[i].getName(), renderer, _nations[i].getSurface());
			if (SDL_SetTextureBlendMode(am->getTexture(_nations[i].getName()), SDL_BLENDMODE_BLEND) < 0)
			{
				std::cout << "GMC: Nations texture blend mode error" << std::endl;
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

	void GameMapController::RenderNations()
	{
		for (int i = 0; i < _nations.size(); i++)
		{
			//SDL_Texture* map = SDL_CreateTextureFromSurface(renderer, _nations[i].getMap());
			SDL_RenderCopy(renderer, am->getTexture(_nations[i].getName()), &sRect, &dRect);			
		}
	}
}
