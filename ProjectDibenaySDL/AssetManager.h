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
		void InitAssetManager(SDL_Renderer* renderer, std::string locationsFile);
		~AssetManager() {}

		void LoadTexture(std::string name, std::string filename, SDL_Renderer* renderer);
		SDL_Texture* getTexture(std::string name);

		void LoadMusic(std::string name, std::string filename);
		Mix_Music* getMusic(std::string name);

		void LoadEffect(std::string name, std::string filename);
		Mix_Chunk* getEffect(std::string name);

	private:
		std::map <std::string, SDL_Texture*> _textures;
		std::map <std::string, Mix_Music*> _music;
		std::map <std::string, Mix_Chunk*> _soundEffects;
		void ProccessLocationsFile(SDL_Renderer* renderer, std::string locationsFile);
		char typeLimiter = ':';
		char nameLimiter = '=';


	};
}


