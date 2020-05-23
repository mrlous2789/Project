#pragma once
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

		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
	private:
		GameDataReF _data;

		AssetManager am;
		SDL_Renderer* renderer;
		SDL_Texture* map;

		std::string assetsFile = "./Assets/game_assets_locations.txt";

	};
}


