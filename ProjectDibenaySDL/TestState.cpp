#include "TestState.h"
#include <iostream>

namespace Mer
{
	TestState::TestState(GameDataReF data) : _data(data)
	{

	}
	void TestState::Init()
	{
		this->renderer = SDL_CreateRenderer(this->_data->window, -1, 0);


		this->map = IMG_LoadTexture(renderer,"./Assets/Terrain_Base_Layer.png");

		std::cout << "Init" << std::endl;
	}
	void TestState::HandleInput()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_WINDOWEVENT)
			{
				switch (event.window.event)
				{
				case SDL_WINDOWEVENT_CLOSE:
					this->_data->running = false;
				}
			}
		}

	}
	void TestState::Update(float dt)
	{

	}
	void TestState::Draw(float dt)
	{
		SDL_RenderClear(renderer);
		std::cout << SDL_GetError() << std::endl;
		SDL_RenderCopy(renderer, this->map, NULL, NULL);
		std::cout << SDL_GetError() << std::endl;
		SDL_RenderPresent(renderer);
	}
}