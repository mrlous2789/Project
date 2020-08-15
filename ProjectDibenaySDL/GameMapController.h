#pragma once
#include "AssetManager.h"
#include <SDL.h>
#include <fstream>
#include "DEFINITIONS.h"
#include <vector>
#include "Nation.h"
#include "Province.h"

namespace Mer
{
	class GameMapController
	{
	public:
		GameMapController();
		void Init(AssetManager* am, int screenWidth, int screenHeight, SDL_Renderer* &renderer);
		void UpdateScreenResolution(int screenWidth, int screenHeight);
		void UpdateMap();
		void RenderMap();

		void setZoomIn(bool set);
		void setZoomOut(bool set);

		void setSpeed(float speed);
	private:
		AssetManager* am;
		bool zoomin;
		bool zoomout;
		bool zoomInFalloff = false;
		bool zoomOutFalloff = false;
		float falloff = 1.5f;
		float falloffSpeed;
		float zoomSpeed = 0.1f;
		float zoomLevel = 1.0f;
		float currentFalloff = 0.0f;

		float wheelSpeed;

		void ProcessZoomIn();
		void ProcessZoomOut();
		void UpdateMapRect();
		void CalculateNations(std::string filename);
		void CalculateProvinces(std::string filename);
		void FinaliseLoading();
		void RenderProvinces();

		SDL_Rect mapSRect;
		SDL_Rect mapDRect;

		SDL_Renderer* renderer;

		int screenWidth;
		int screenHeight;

		int mapW = 1920;
		int mapH = 1080;

		float maxZoom = 2.0f;
		float minZoom = 1.0f;

		void CalculateBorders(std::string mapFile);

		std::vector<Nation> _nations;
		std::vector<Province> _provinces;

		SDL_Rect sRect;
		SDL_Rect dRect;


	};
}


