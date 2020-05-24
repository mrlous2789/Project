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
		this->_data->ui.setRenderer(renderer);
		this->_data->ui.ProccessUIFile(uiFile, this->_data->settings.getDisplaySetting("screen_width"), this->_data->settings.getDisplaySetting("screen_height"));
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
					int size = this->_data->ui.getButtonElementsSize();
					for (int i = 0; i < size; i++)
					{
						if (this->_data->input.IsTexturePressed(this->_data->ui.getButtonElementDRect(i)))
						{
							lmbPressed = this->_data->ui.getButtonElementName(i);
							std::cout << lmbPressed << std::endl;
							break;
						}
						
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
		if (lmbPressed != "")
		{
			if (lmbPressed == "test_button_top")
			{
				this->_data->ui.changeParentVisibility("test_button_background");
				lmbPressed = "";
			}
			if (lmbPressed == "test_button_med")
			{
				this->_data->settings.ChangeSetting("display", "screen_width", 1366);
				this->_data->settings.ChangeSetting("display", "screen_height", 768);
				this->_data->settings.SaveSettings();
			
				SDL_SetWindowSize(this->_data->window, this->_data->settings.getDisplaySetting("screen_width"), this->_data->settings.getDisplaySetting("screen_height"));
				this->_data->ui.signalResolutionChange(this->_data->settings.getDisplaySetting("screen_width"), this->_data->settings.getDisplaySetting("screen_height"));
				lmbPressed = "";
			}
			if (lmbPressed == "test_button_low")
			{
				
				lmbPressed = "";
				this->_data->running = false;
				CleanUp();
			}
		}
		this->_data->ui.ProcessUIChanges();
	}


	void TestState::Draw(float dt)
	{
		if (this->_data->running)
		{
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, am.getTexture("map_base_layer"), &srect1, &drect1);
			SDL_RenderCopy(renderer, am.getTexture("map_nations_layer"), &srect1, &drect2);
			this->_data->ui.RenderUI();
			SDL_RenderPresent(renderer);
		}
	}

	
	void TestState::CleanUp()
	{
		am.CleanUp();
	}
}