#pragma once

#include <memory>
#include <string>
#include <SDL.h>
#include "StateMachine.h"
#include "AssetManager.h"

namespace Mer
{
	struct GameData
	{
		StateMachine machine;
		SDL_Window* window;
		bool running;
		AssetManager sAM;
	};

	typedef std::shared_ptr<GameData> GameDataReF;

	class Game
	{
	public:
		Game();
	private:
		Uint32 dt = 1000 / 60;
		
		GameDataReF _data = std::make_shared<GameData>();

		std::string settingsFile = "./Assets/settings.txt";

		void Run();
		bool InitSDL();
		void CleanUp();
	};
}


