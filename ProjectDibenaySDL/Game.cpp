#include "Game.h"
#include "TestState.h"

namespace Mer
{
	Game::Game()
	{
		if (InitSDL())//if sdl and other componets were initalised correctly start program
		{
			_data->sAM.ProcessSettingsFile(settingsFile);//load settings from file
			//sets music volume to ('music_volume' * 'master_volume') / 100 using the settings
			Mix_VolumeMusic((_data->sAM.getAudioSetting("music_volume") * _data->sAM.getAudioSetting("master_volume")) / 100);
			//sets effect volume to ('effect_volume'*'master_volume') / 100 using the settings
			Mix_Volume(-1, (_data->sAM.getAudioSetting("effect_volume") * _data->sAM.getAudioSetting("master_volume")) / 100);
			//create centered window titled 'Dibenay' with height and width from settings file
			_data->window = SDL_CreateWindow("Dibenay", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _data->sAM.getDisplaySetting("screen_width"), _data->sAM.getDisplaySetting("screen_height"), NULL);
			//add first state to state machine
			_data->machine.AddState(StateRef(new TestState(this->_data)));
			//sets running to be true in game data
			_data->running = true;
			//run program
			this->Run();
		}
		else//else output to console an error
		{
			std::cout << "Probelem initialising SDL" << std::endl;
		}

	}


	void Game::Run()
	{

		Uint32 newTime, frameTime, interpolation;//used for timing 'Update' and 'HandleInput' function calls
		
		Uint32 currentTime = SDL_GetTicks();//get ticks since sdl was initilised (time in ms)

		Uint32 accumaltor = 0;//accumaltion of time 

		while (_data->running)//running is true run program
		{
			this->_data->machine.ProcesssStateChanges();//process any changes to program state

			newTime = SDL_GetTicks();//get ticks since sdl was inititalised (time in ms)
			frameTime = newTime - currentTime;//work out time in ms since last frame

			if (frameTime > 250)//is its been more than 250ms since last frame frameTime = 250ms
			{
				frameTime = 250;
			}

			currentTime = newTime;//change current time to new time
			accumaltor += frameTime;

			while(accumaltor >= dt)//while the accumator is greater than desierd frame time call functions
			{
				this->_data->machine.GetActiveState()->HandleInput();
				this->_data->machine.GetActiveState()->Update(dt);

				accumaltor -= dt;//use minus to allow program to catch up 
			}

			interpolation = accumaltor / dt;

			this->_data->machine.GetActiveState()->Draw(interpolation);
		}

		CleanUp();//when program is no longer running call clean up function

	}


	bool Game::InitSDL()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)//if initialsing SDL failed return false
		{
			return false;
		}
		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) < 0)//if opening audio device failed return false
		{
			return false;
		}

		return true;//return true if nothing failed
	}


	void Game::CleanUp()
	{
		_data->sAM.CleanUp();//clean up assets
		Mix_CloseAudio();//close audio device

		SDL_Quit();//quit sdl
	}
}