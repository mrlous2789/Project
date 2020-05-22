#include "Game.h"
#include "TestState.h"

namespace Mer
{
	Game::Game(int width, int height, std::string title)
	{
		_data->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,NULL);
		_data->machine.AddState(StateRef(new TestState(this->_data)));
		_data->running = true;

		this->Run();
	}

	void Game::Run()
	{
		Uint32 newTime, frameTime, interpolation;
		
		Uint32 currentTime = SDL_GetTicks();

		Uint32 accumaltor = 0;

		while (_data->running)
		{
			this->_data->machine.ProcesssStateChanges();

			newTime = SDL_GetTicks();
			frameTime = newTime - currentTime;

			if (frameTime > 250)
			{
				frameTime = 250;
			}

			currentTime = newTime;
			accumaltor += frameTime;

			while(accumaltor >= dt)
			{
				this->_data->machine.GetActiveState()->HandleInput();
				this->_data->machine.GetActiveState()->Update(dt);

				accumaltor -= dt;
			}

			interpolation = accumaltor / dt;

			this->_data->machine.GetActiveState()->Draw(interpolation);
		}
	}
}