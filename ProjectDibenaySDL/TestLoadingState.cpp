#include "TestLoadingState.h"
#include "TestState.h"
namespace Mer
{
	TestLoadingState::TestLoadingState(GameDataReF data) : _data(data)
	{

	}
	void TestLoadingState::Init()
	{
		AssetManager tmpAM;
		tmpAM.ProccessLocationFile(this->_data->renderer,loadingAssetsFile);
		am.ProccessLocationFileWithLoadingBar(this->_data->renderer, assetsFile, tmpAM.getTextureMap(),this->_data->settings.getDisplaySetting("screen_width"), this->_data->settings.getDisplaySetting("screen_height"));
		this->_data->machine.AddState(StateRef(new TestState(_data, am)),true);		
		std::cout << "TestLoadingState: Init" << std::endl;
	}
	void TestLoadingState::HandleInput()
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
			}
		}
	}
	void TestLoadingState::Update(float dt)
	{
		this->_data->machine.AddState(StateRef(new TestState(_data, am)), true);
	}
	void TestLoadingState::Draw(float dt)
	{

	}
	void TestLoadingState::CleanUp()
	{
		tmpAM.CleanUp();
	}
}
