#pragma once
#include "AssetManager.h"
#include <SDL.h>
namespace Mer
{
	class GameMapController
	{
	public:
		GameMapController();
		void Init(AssetManager* am, int screenWidth, int screenHeight, SDL_Renderer* renderer);
		void UpdateScreenResolution(int screenWidth, int screenHeight);
		void UpdateMap();
		void RenderMap();

		void setZoomIn(bool set);
		void setZoomOut(bool set);
	private:
		AssetManager _mapFiles;
		bool zoomin;
		bool zoomout;
		float zoomSpeed = 0.1f;
		float zoomLevel = 1.0f;

		void ProcessZoomIn();
		void ProcessZoomOut();
		void UpdateMapRect();

		SDL_Rect mapSRect;
		SDL_Rect mapDRect;

		SDL_Renderer* renderer;

		int screenWidth;
		int screenHeight;

		int mapW;
		int mapH;

		float maxZoom = 2.0f;
		float minZoom = 1.0f;
	};
}


