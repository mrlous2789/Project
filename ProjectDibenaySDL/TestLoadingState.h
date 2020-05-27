#pragma once

#include "State.h"
#include "Game.h"
#include "AssetManager.h"

namespace Mer
{
	class TestLoadingState : public State
	{
	public:
		TestLoadingState(GameDataReF data);
		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
		void CleanUp();
	private:
		GameDataReF _data;
		AssetManager am;
		AssetManager tmpAM;

		std::string loadingAssetsFile = LOADING_SCREEN_ASSETS;

		std::string assetsFile = GAME_ASSETS;
	};
}

