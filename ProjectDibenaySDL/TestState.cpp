#include "TestState.h"
#include <iostream>

namespace Mer
{
	TestState::TestState(GameDataReF data, AssetManager &am) : _data(data)
	{
		_am = am;
		std::cout << "new test state" << std::endl;
	}


	void TestState::Init()
	{		
		std::cout << "Test State Started " << std::endl;
		SDL_SetRenderDrawBlendMode(this->_data->renderer, SDL_BLENDMODE_BLEND);
		ui.initUI(this->_data->renderer , &_am);
		ui.ProccessUIFile(uiFile, this->_data->settings.getDisplaySetting("screen_width"), this->_data->settings.getDisplaySetting("screen_height"));

		gmc.Init(&_am,this->_data->settings.getDisplaySetting("screen_width"), this->_data->settings.getDisplaySetting("screen_height"), this->_data->renderer);
		
		Mix_PlayMusic(_am.getMusic("test_music"), -1);
		//Mix_PlayChannel(-1, _am.getEffect("test_effect"), 1);

		std::cout << "TestState: Init" << std::endl;
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
					int size = ui.getButtonElementsSize();
					for (int i = 0; i < size; i++)
					{
						if (this->_data->input.IsTexturePressed(ui.getButtonElementDRect(i)))
						{
							lmbPressed = ui.getButtonElementName(i);
							std::cout << lmbPressed << std::endl;
							break;
						}						
					}
				}
				break;
			case SDL_MOUSEWHEEL:
				if (event.wheel.y > 0)
				{
					std::cout << "Zooming in " << std::endl;
					gmc.setZoomIn(true);
					gmc.setZoomOut(false);
					gmc.setSpeed(event.wheel.y);
				}
				else if (event.wheel.y < 0)
				{
					std::cout << "Zooming out" << std::endl;
					gmc.setZoomOut(true); 
					gmc.setZoomIn(false);
					gmc.setSpeed(event.wheel.y);
				}
				break;
			}			
		}
	}


	void TestState::Update(float dt)
	{
		if (!this->_data->running)
		{
			SDL_DestroyRenderer(this->_data->renderer);
			CleanUp();
		}
		if (lmbPressed != "")
		{
			if (lmbPressed == "test_button_top")
			{
				ui.changeParentVisibility("test_button_background_right");
				lmbPressed = "";
			}
			else if (lmbPressed == "test_button_med")
			{
				this->_data->settings.ChangeSetting("display", "screen_width", 1366);
				this->_data->settings.ChangeSetting("display", "screen_height", 768);
				this->_data->settings.SaveSettings();
			
				SDL_SetWindowSize(this->_data->window, this->_data->settings.getDisplaySetting("screen_width"), this->_data->settings.getDisplaySetting("screen_height"));
				ui.signalResolutionChange(this->_data->settings.getDisplaySetting("screen_width"), this->_data->settings.getDisplaySetting("screen_height"));
				gmc.UpdateScreenResolution(this->_data->settings.getDisplaySetting("screen_width"), this->_data->settings.getDisplaySetting("screen_height"));
				lmbPressed = "";
			}
			else if (lmbPressed == "test_button_low")
			{				
				lmbPressed = "";
				this->_data->running = false;
				CleanUp();
			}
			else if (lmbPressed == "test_button_top_right")
			{
				lmbPressed = "";
				ui.changeParentVisibility("test_button_background");
			}
			else if (lmbPressed == "test_button_med_right")
			{
				this->_data->settings.ChangeSetting("display", "screen_width", 1280);
				this->_data->settings.ChangeSetting("display", "screen_height", 720);
				this->_data->settings.SaveSettings();

				SDL_SetWindowSize(this->_data->window, this->_data->settings.getDisplaySetting("screen_width"), this->_data->settings.getDisplaySetting("screen_height"));
				ui.signalResolutionChange(this->_data->settings.getDisplaySetting("screen_width"), this->_data->settings.getDisplaySetting("screen_height"));
				gmc.UpdateScreenResolution(this->_data->settings.getDisplaySetting("screen_width"), this->_data->settings.getDisplaySetting("screen_height"));
				lmbPressed = "";
			}
			else
			{
				std::cout << "TestState: " << lmbPressed << " unhandled button " << std::endl;
				lmbPressed = "";
			}
		}
		gmc.UpdateMap();
		ui.ProcessUIChanges();
	}


	void TestState::Draw(float dt)
	{
		if (this->_data->running)
		{
			SDL_RenderClear(this->_data->renderer);

			gmc.RenderMap();
			ui.RenderUI();

			SDL_RenderPresent(this->_data->renderer);
		}
	}

	
	void TestState::CleanUp()
	{
		_am.CleanUp();
	}
}