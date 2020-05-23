#pragma once
#include<fstream>
#include<SDL.h>
#include<iostream>
#include<map>
#include<SDL_image.h>
#include<string>
#include<SDL_mixer.h>

namespace Mer
{
	class AssetManager
	{
	public:
		AssetManager();
		~AssetManager() {}

		void LoadTexture(std::string name, std::string filename, SDL_Renderer* renderer);
		SDL_Texture* getTexture(std::string name);

		void LoadMusic(std::string name, std::string filename);
		Mix_Music* getMusic(std::string name);

		void LoadEffect(std::string name, std::string filename);
		Mix_Chunk* getEffect(std::string name);

		void LoadDisplaySetting(std::string name, std::string setting);
		Uint16 getDisplaySetting(std::string name);
		void LoadAudioSetting(std::string name, std::string setting);
		Uint16 getAudioSetting(std::string name);

		void ProccessLocationFile(SDL_Renderer* renderer, std::string locationsFile);
		void ProcessSettingsFile(std::string settingsFile);

		void CleanUp();
	private:
		std::map <std::string, SDL_Texture*> _textures;
		std::map <std::string, Mix_Music*> _music;
		std::map <std::string, Mix_Chunk*> _soundEffects;
		std::map <std::string, Uint16> _displaySettings;
		std::map <std::string, Uint16> _audioSettings;
		
		void cleanTextures();
		void cleanMusic();
		void cleanSoundEffects();
		void cleanDisplaySettings();
		void cleanAudioSettings();

		char typeLimiter = ':';
		char nameLimiter = '=';

	};
}


