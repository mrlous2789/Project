#include "SettingsMenuState.h"

namespace Mer
{
	SettingsMenuState::SettingsMenuState(GameDataReF data) : _data(data)
	{

	}

	void SettingsMenuState::Init()
	{
		am.ProccessLocationFile(this->_data->renderer, assetsFile);
	}

	void SettingsMenuState::HandleInput()
	{

	}

	void SettingsMenuState::Update(float dt)
	{

	}

	void SettingsMenuState::Draw(float dt)
	{

	}

	void SettingsMenuState::CleanUp()
	{

	}
}
