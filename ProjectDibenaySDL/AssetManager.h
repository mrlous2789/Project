#pragma once
//include header files
#include<fstream>
#include<SDL.h>
#include<iostream>
#include<map>
#include<SDL_image.h>
#include<string>
#include<SDL_mixer.h>
#include<tuple>

namespace Mer
{
	class AssetManager
	{
	public:
		AssetManager();    // contructor
		~AssetManager() {} // destructor

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
		//maps for assets
		std::map <std::string, SDL_Texture*> _textures; 
		std::map <std::string, Mix_Music*> _music;
		std::map <std::string, Mix_Chunk*> _soundEffects;
		std::map <std::string, Uint16> _displaySettings;
		std::map <std::string, Uint16> _audioSettings;
		
		//clean assets functions
		void cleanTextures();
		void cleanMusic();
		void cleanSoundEffects();
		void cleanDisplaySettings();
		void cleanAudioSettings();

		//progress through file functions
		float calcFileSize(std::string filename);

		//processing files functions
		std::tuple<int, int> calcLimiterPositions(std::string line);
		std::tuple<std::string, std::string, std::string> seperateLine(std::string line,int tlPos,int nlPos);

		//breakpoints between types, names and locations/setting value
		char typeLimiter = ':';
		char nameLimiter = '=';

		float loadingPercentage = 0.0f;

	};
}


