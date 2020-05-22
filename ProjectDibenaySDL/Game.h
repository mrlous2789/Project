#pragma once

#include <memory>
#include <string>
#include <SDL.h>
#include "StateMachine.h"

namespace Mer
{
	struct GameData
	{
		StateMachine machine;
		SDL_Window* window;
		bool running;
	};

	typedef std::shared_ptr<GameData> GameDataReF;

	class Game
	{
	public:
		Game(int width, int height, std::string title);
	private:
		Uint32 dt = 1000 / 60;
		
		GameDataReF _data = std::make_shared<GameData>();

		void Run();
	};
}


