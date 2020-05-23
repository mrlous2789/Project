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

		am.ProccessLocationFile(this->renderer, assetsFile);
		std::cout << "Init" << std::endl;

		
		Mix_PlayMusic(am.getMusic("test_music"), -1);
		//Mix_PlayChannel(-1, am.getEffect("test_effect"), 1);

		srect1.x = 0;
		srect1.y = 0;
		srect1.w = 640;
		srect1.h = 360;

		drect1.x = 0;
		drect1.y = 0;
		drect1.w = 640;
		drect1.h = 360;

		drect2.x = 640;
		drect2.y = 0;
		drect2.w = 640;
		drect2.h = 360;

		int w, h;
		SDL_QueryTexture(am.getTexture("test_button"), NULL, NULL, &w, &h);
		buttonPosRect.x = (this->_data->settings.getDisplaySetting("screen_width") / 2) - (w / 2);
		buttonPosRect.y = (this->_data->settings.getDisplaySetting("screen_height") / 2) - (h / 2);
		buttonPosRect.w = w;
		buttonPosRect.h = h;
	}


	void TestState::HandleInput()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_WINDOWEVENT:
				switch (event.window.event)
				{
				case SDL_WINDOWEVENT_CLOSE:
					this->_data->running = false;
					break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					if (this->_data->input.IsTexturePressed(&buttonPosRect))
					{
						std::cout << "button pressed" << std::endl;
					}
				}
			}
		}


	}


	void TestState::Update(float dt)
	{
		if (!this->_data->running)
		{
			SDL_DestroyRenderer(renderer);
			CleanUp();
		}
	}


	void TestState::Draw(float dt)
	{
		if (this->_data->running)
		{
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, am.getTexture("map_base_layer"), &srect1, &drect1);
			SDL_RenderCopy(renderer, am.getTexture("map_nations_layer"), &srect1, &drect2);
			SDL_RenderCopy(renderer, am.getTexture("test_button"), NULL, &buttonPosRect);
			SDL_RenderPresent(renderer);
		}
	}

	
	void TestState::CleanUp()
	{
		am.CleanUp();
	}
}