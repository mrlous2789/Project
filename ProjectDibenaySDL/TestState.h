#pragma once
//include header files
#include <SDL.h>
#include "State.h"
#include "Game.h"
#include <time.h>
#include <fstream>
#include<SDL_image.h>
#include "AssetManager.h"

namespace Mer
{
	class TestState : public State
	{
	public:
		TestState(GameDataReF data);

		//deafult functions for states
		void Init(); 
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
		void CleanUp();
	private:
		GameDataReF _data;

		AssetManager am;
		SDL_Renderer* renderer;
		SDL_Texture* map;
		SDL_Rect srect1;
		SDL_Rect drect1;
		SDL_Rect drect2;
		std::string assetsFile = "./Assets/game_assets_locations.txt";

	};
}


