#pragma once

#include <memory>
//include header files
#include <string>
#include <SDL.h>
#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"
#include "DEFINITIONS.h"

namespace Mer
{
	struct GameData //struct containing data for game data is passed to every state
	{
		StateMachine machine; // state machine 
		SDL_Window* window; // window
		SDL_Renderer* renderer;
		bool running; //boolean for whether game is running
		AssetManager settings; //program settings asset manager
		InputManager input; //input manager
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

		std::string settingsFile = SETTINGS; //settings file location

		void Run();
		bool InitSDL();
		void CleanUp();
	};
}


