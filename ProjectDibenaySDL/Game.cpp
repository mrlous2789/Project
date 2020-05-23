#include "Game.h"
#include "TestState.h"

namespace Mer
{
	Game::Game()
	{
		if (InitSDL())
		{
			_data->sAM.ProcessSettingsFile(settingsFile);
			Mix_VolumeMusic((_data->sAM.getAudioSetting("music_volume") * _data->sAM.getAudioSetting("master_volume")) / 100);
			Mix_Volume(-1, (_data->sAM.getAudioSetting("effect_volume") * _data->sAM.getAudioSetting("master_volume")) / 100);
			_data->window = SDL_CreateWindow("Dibenay", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _data->sAM.getDisplaySetting("screen_width"), _data->sAM.getDisplaySetting("screen_height"), NULL);
			_data->machine.AddState(StateRef(new TestState(this->_data)));
			_data->running = true;
			this->Run();
		}
		else
		{
			std::cout << "Probelem initialising SDL" << std::endl;
		}

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

		CleanUp();

	}


	bool Game::InitSDL()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			return false;
		}
		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
		{
			return false;
		}

		return true;
	}


	void Game::CleanUp()
	{
		_data->sAM.CleanUp();
		Mix_CloseAudio();
		SDL_Quit();
	}
}