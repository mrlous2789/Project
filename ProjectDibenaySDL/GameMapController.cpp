#include "GameMapController.h"
namespace Mer
{
	GameMapController::GameMapController()
	{

	}
	void GameMapController::Init(AssetManager *am, int screenWidth, int screenHeight, SDL_Renderer* renderer)
	{
		_mapFiles = *am;
		this->renderer = renderer;
		SDL_QueryTexture(_mapFiles.getTexture("map_coloured_layer"), NULL, NULL, &mapW, &mapH);
		UpdateScreenResolution(screenWidth, screenHeight);
		UpdateMapRect();
	}
	void GameMapController::UpdateMap()
	{
		if (zoomin)
		{
			ProcessZoomIn();
		}
		if (zoomout)
		{
			ProcessZoomOut();
		}
	}
	void GameMapController::ProcessZoomIn()
	{
		zoomLevel -= zoomSpeed;
		if (zoomLevel < minZoom)
		{
			zoomLevel = minZoom;
		}
		UpdateMapRect();
		zoomin = false;
	}
	void GameMapController::ProcessZoomOut()
	{
		zoomLevel += zoomSpeed;

		if (zoomLevel > maxZoom )
		{
			zoomLevel = maxZoom;
		}
		std::cout << "GMC: zoomlevel = " << zoomLevel << std::endl;
		UpdateMapRect();
		zoomout = false;
	}
	void GameMapController::UpdateMapRect()
	{
		float scaleX, scaleY;
		

		mapDRect.x = 0; mapDRect.y = 0; mapDRect.w = screenWidth; mapDRect.h = screenHeight;

		mapSRect.x = 0; mapSRect.y = 0; mapSRect.w = screenWidth * zoomLevel; mapSRect.h = screenHeight * zoomLevel;

		std::cout << "map width = " << mapSRect.w << "map height = " << mapSRect.h << std::endl;
		
	}

	void GameMapController::RenderMap()
	{
		SDL_RenderCopy(renderer, _mapFiles.getTexture("map_coloured_layer"),&mapSRect, &mapDRect);
	}
	void GameMapController::setZoomIn(bool set)
	{
		zoomin = set;
	}
	void GameMapController::setZoomOut(bool set)
	{
		zoomout = set;
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

		std::cout << "GMC: mapw / screenwidth = " << tmp << ", maph / screenheight = " << tmp2 <<std::endl;
		std::cout << "GMC: minZoom = " << minZoom << std::endl;
	}
}