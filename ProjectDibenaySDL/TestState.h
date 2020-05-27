#pragma once
//include header files
#include <SDL.h>
#include "State.h"
#include "Game.h"
#include <time.h>
#include <fstream>
#include<SDL_image.h>
#include "AssetManager.h"
#include "UIController.h"
#include "GameMapController.h"

namespace Mer
{
	class TestState : public State
	{
	public:
		TestState(GameDataReF data, AssetManager &am);

		//deafult functions for states
		void Init(); 
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
		void CleanUp();
	private:
		GameDataReF _data;

		AssetManager _am;
		GameMapController gmc;
		SDL_Texture* map;

		std::string uiFile = GAME_UI;

		UIController ui;

		std::string lmbPressed = "";
		std::string rmbPressed = "";

	};
}


