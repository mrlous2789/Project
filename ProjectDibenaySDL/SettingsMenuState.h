#pragma once
#include "State.h"
#include "Game.h"
#include "UIController.h"

namespace Mer
{
	class SettingsMenuState : public State
	{
	public:
		SettingsMenuState(GameDataReF data);

		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
		void CleanUp();
	private:
		GameDataReF _data;

		AssetManager am;
		
		UIController ui;

		std::string assetsFile = SETTINGS_MENU_ASSETS;
		std::string uiFile = SETTINGS_MENU_UI;

		std::string lmbPressed = "";
		std::string rmbPressed = "";

	};
}


