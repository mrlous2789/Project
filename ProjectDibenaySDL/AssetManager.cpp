#include "AssetManager.h"
namespace Mer
{
	AssetManager::AssetManager()
	{

	}
	void AssetManager::InitAssetManager(SDL_Renderer* renderer, std::string locationsFile)
	{
		ProccessLocationsFile(renderer, locationsFile);
	}
	void AssetManager::LoadTexture(std::string name, std::string filename, SDL_Renderer* renderer)
	{
		SDL_ClearError();
		SDL_Texture* tex = IMG_LoadTexture(renderer, filename.c_str());
		const char* error = SDL_GetError();
		printf(error);
		if (!*error)
		{
			this->_textures[name] = tex;
		}
		else 
		{
			std::cout << "Failed to load: " << name << " at: " << filename << std::endl << SDL_GetError() << std::endl;
		}
	}
	SDL_Texture* AssetManager::getTexture(std::string name)
	{
		return this->_textures.at(name);
	}
	void AssetManager::LoadMusic(std::string name, std::string filename)
	{
		Mix_ClearError();
		Mix_Music* mus = Mix_LoadMUS(filename.c_str());
		const char* error = Mix_GetError();
		printf(error);
		if (!*error)
		{
			this->_music[name] = mus;
		}
		else
		{
			std::cout << "Failed to load: " << name << " at: " << filename << std::endl << Mix_GetError() << std::endl;
		}
	}
	Mix_Music* AssetManager::getMusic(std::string name)
	{
		return this->_music.at(name);
	}
	void AssetManager::LoadEffect(std::string name, std::string filename)
	{
		Mix_ClearError();
		Mix_Chunk* eff = Mix_LoadWAV(filename.c_str());
		const char* error = Mix_GetError();
		printf(error);
		if (!*error)
		{
			this->_soundEffects[name] = eff;
		}
		else
		{
			std::cout << "Failed to load: " << name << " at: " << filename << std::endl << Mix_GetError() << std::endl;
		}
	}
	Mix_Chunk* AssetManager::getEffect(std::string name)
	{
		return this->_soundEffects.at(name);
	}
	void AssetManager::ProccessLocationsFile(SDL_Renderer* renderer, std::string locationsFile)
	{
		std::ifstream file;
		file.open(locationsFile);

		std::string line;

		while (std::getline(file, line))
		{
			std::string type, name, location;
			int typeLimiterPos = 0, nameLimiterPos = 0;
			for (int i = 0; i < line.size() - 1; i++)
			{
				if (line[i] == typeLimiter)
				{
					typeLimiterPos = i;
				}
				if (line[i] == nameLimiter)
				{
					nameLimiterPos = i;
				}
			}
			if (typeLimiterPos == nameLimiterPos)
			{
				std::cout << line << " is a bad line" << std::endl;
			}
			else
			{
				std::cout << line << std::endl;
				type = line;
				type = type.substr(0, typeLimiterPos);
				std::cout << type << std::endl;
				name = line;
				name = name.substr(typeLimiterPos + 1, (nameLimiterPos - typeLimiterPos) - 1);
				std::cout << name << std::endl;
				location = line;
				location = location.substr(nameLimiterPos + 1, (line.size() - nameLimiterPos) - 1);
				std::cout << location << std::endl;

				if (type == "texture")
				{
					LoadTexture(name, location, renderer);
				}
				else if (type == "music")
				{
					LoadMusic(name, location);
				}
				else if (type == "effect")
				{
					LoadEffect(name, location);
				}
				else
				{
					std::cout << "Bad Type" << std::endl;
				}
			}
		}
		file.close();
	}
}