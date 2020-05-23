#include "AssetManager.h"
namespace Mer
{
	AssetManager::AssetManager()
	{

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


	void AssetManager::LoadDisplaySetting(std::string name, std::string setting)
	{
		this->_displaySettings[name] = std::stoi(setting);
	}

	Uint16 AssetManager::getDisplaySetting(std::string name)
	{
		return this->_displaySettings.at(name);
	}


	void AssetManager::LoadAudioSetting(std::string name, std::string setting)
	{
		this->_audioSettings[name] = std::stoi(setting);
	}

	Uint16 AssetManager::getAudioSetting(std::string name)
	{
		return this->_audioSettings.at(name);
	}


	void AssetManager::ProccessLocationFile(SDL_Renderer* renderer, std::string locationsFile)
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
					std::cout << type << " Bad Type" << std::endl;
				}
			}
		}
		file.close();
	}


	void AssetManager::ProcessSettingsFile(std::string settingsFile)
	{
		std::ifstream file;
		file.open(settingsFile);

		std::string line;

		while (std::getline(file, line))
		{
			std::string type, name, value;
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
				value = line;
				value = value.substr(nameLimiterPos + 1, (line.size() - nameLimiterPos) - 1);
				std::cout << value << std::endl;

				if (type == "display")
				{
					LoadDisplaySetting(name, value);
				}
				else if (type == "audio")
				{
					LoadAudioSetting(name, value);
				}
				else
				{
					std::cout << type << " Bad Type" << std::endl;
				}
			}
		}
	}


	void AssetManager::CleanUp()
	{
		if (!_textures.empty()) { cleanTextures(); }
		if (!_music.empty()) { cleanMusic(); }
		if (!_soundEffects.empty()) { cleanSoundEffects(); }
		if (!_displaySettings.empty()) { cleanDisplaySettings(); }
		if (!_audioSettings.empty()) { cleanAudioSettings(); }
	}

	void AssetManager::cleanDisplaySettings()
	{
		_displaySettings.clear();
		std::cout << "Display settings cleared" << std::endl;
	}
	
	void AssetManager::cleanAudioSettings()
	{
		_audioSettings.clear();
		std::cout << "Audio settings cleared" << std::endl;
	}

	void AssetManager::cleanTextures()
	{
		std::map <std::string, SDL_Texture*>::iterator _tIT = _textures.begin();
		while (_tIT != _textures.end())
		{
			SDL_DestroyTexture(_tIT->second);
			_tIT++;
		}
		_textures.clear();
		std::cout << "Textures cleared" << std::endl;
	}

	void AssetManager::cleanMusic()
	{
		std::map <std::string, Mix_Music*>::iterator _mIT = _music.begin();
		while (_mIT != _music.end())
		{
			Mix_FreeMusic(_mIT->second);
			_mIT++;
		}
		_music.clear();
		std::cout << "Music cleared" << std::endl;
	}

	void AssetManager::cleanSoundEffects()
	{
		std::map <std::string, Mix_Chunk*>::iterator _seIT = _soundEffects.begin();
		while (_seIT != _soundEffects.end())
		{
			Mix_FreeChunk(_seIT->second);
			_seIT++;
		}
		_soundEffects.clear();
		std::cout << "Sound effects cleared" << std::endl;
	}
}