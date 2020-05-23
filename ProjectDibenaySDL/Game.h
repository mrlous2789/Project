#pragma once

#include <memory>
//include header files
#include <string>
#include <SDL.h>
#include "StateMachine.h"
#include "AssetManager.h"

namespace Mer
{
	struct GameData //struct containing data for game data is passed to every state
	{
		StateMachine machine; // state machine 
		SDL_Window* window; // window
		bool running; //boolean for whether game is running
		AssetManager sAM; //program settings asset manager
	};

	typedef std::shared_ptr<GameData> GameDataReF;

	class Game
	{
	public:
		Game();
	private:
		Uint32 dt = 1000 / 60; //time in ms between update and handle input can be called
		//denominator is desired frame rate
		
		GameDataReF _data = std::make_shared<GameData>();

		std::string settingsFile = "./Assets/settings.txt"; //settings file location

		void Run();
		bool InitSDL();
		void CleanUp();
	};
}


