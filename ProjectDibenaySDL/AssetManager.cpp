#include "AssetManager.h"
namespace Mer
{
	AssetManager::AssetManager() //constructor
	{

	}


	void AssetManager::LoadTexture(std::string name, std::string filename, SDL_Renderer* renderer)
	{
		SDL_ClearError(); //clear error queue
		SDL_Texture* tex = IMG_LoadTexture(renderer, filename.c_str()); //load texture from file
		const char* error = SDL_GetError(); // store any errors in variable
		if (!*error) // if no error store texture into texture map
		{
			this->_textures[name] = tex;
		}
		else //print to console error info
		{
			std::cout << "Failed to load: " << name << " at: " << filename << std::endl << SDL_GetError() << std::endl;
		}
	}

	SDL_Texture* AssetManager::getTexture(std::string name) //return texture by key value
	{
		return this->_textures.at(name);
	}


	void AssetManager::LoadMusic(std::string name, std::string filename)
	{
		Mix_ClearError();//clear error queue
		Mix_Music* mus = Mix_LoadMUS(filename.c_str()); //load audio file 
		const char* error = Mix_GetError(); //store any error in variable
		if (!*error)// if no error store music map
		{
			this->_music[name] = mus;
		}
		else //print to console error info
		{
			std::cout << "Failed to load: " << name << " at: " << filename << std::endl << Mix_GetError() << std::endl;
		}
	}

	Mix_Music* AssetManager::getMusic(std::string name) //return music by key value
	{
		return this->_music.at(name);
	}


	void AssetManager::LoadEffect(std::string name, std::string filename)
	{
		Mix_ClearError(); //clear errors
		Mix_Chunk* eff = Mix_LoadWAV(filename.c_str());//load sound effect file
		const char* error = Mix_GetError();//store any erros in variable
		if (!*error)//if no error store sound effect to sound effects map
		{
			this->_soundEffects[name] = eff;
		}
		else //print error info
		{
			std::cout << "Failed to load: " << name << " at: " << filename << std::endl << Mix_GetError() << std::endl;
		}
	}

	Mix_Chunk* AssetManager::getEffect(std::string name)//return sound effects by key value
	{
		return this->_soundEffects.at(name);
	}


	void AssetManager::LoadDisplaySetting(std::string name, std::string setting)
	{//load display setting into display setting map
		this->_displaySettings[name] = std::stoi(setting);
	}

	Uint16 AssetManager::getDisplaySetting(std::string name)
	{//return display setting by key value
		return this->_displaySettings.at(name);
	}


	void AssetManager::LoadAudioSetting(std::string name, std::string setting)
	{//load audio setting into audio setting map
		this->_audioSettings[name] = std::stoi(setting);
	}

	Uint16 AssetManager::getAudioSetting(std::string name)
	{//return audio setting by key value
		return this->_audioSettings.at(name);
	}


	void AssetManager::ProccessLocationFile(SDL_Renderer* renderer, std::string locationsFile)
	{
		std::ifstream file;//new file

		float fileSize = calcFileSize(locationsFile), currentProgress = 0.0f;

		file.open(locationsFile);//open file that will be proccessed

		std::string line;//line variable

		while (std::getline(file, line))//while not at end of file
		{
			currentProgress++;//count up current progress through file
			std::string type, name, location;//string variables to store important parts of line

			int typeLimiterPos, nameLimiterPos;
			std::tie(typeLimiterPos, nameLimiterPos) = calcLimiterPositions(line);//position variables of breakpoints in line

			if (typeLimiterPos == 0 || nameLimiterPos == 0)//if breakpoints werent found output error to console
			{
				std::cout << line << " is a bad line" << std::endl;
			}
			else//seperate out line to important bits
			{
				std::tie(type, name, location) = seperateLine(line, typeLimiterPos, nameLimiterPos);

				if (type == "texture")//if type is texture load to texture map
				{
					LoadTexture(name, location, renderer);
				}
				else if (type == "music")//if type is music load to music map
				{
					LoadMusic(name, location);
				}
				else if (type == "effect")//if type is effect load to sound effects  map
				{
					LoadEffect(name, location);
				}
				else//else output error
				{
					std::cout << type << " Bad Type" << std::endl;
				}
			}
			loadingPercentage = (currentProgress / fileSize) * 100;//workout loaded files as a percentage
			std::cout << "Loading: " << loadingPercentage << "%" << std::endl;
		}
		file.close();//close file
	}


	void AssetManager::ProcessSettingsFile(std::string settingsFile)
	{
		std::ifstream file;//new file

		float fileSize = calcFileSize(settingsFile), currentProgress = 0.0f;

		file.open(settingsFile);//open settings file to process

		std::string line;

		while (std::getline(file, line))//while not at end of file
		{
			currentProgress++;//count up current progress through file
			std::string type, name, value;//string variables to store important parts of the line

			int typeLimiterPos, nameLimiterPos;
			std::tie(typeLimiterPos, nameLimiterPos) = calcLimiterPositions(line);//position variables of breakpoints in line

			if (typeLimiterPos == 0 || nameLimiterPos == 0)//if breakpoints werent found output error to console
			{
				std::cout << line << " is a bad line" << std::endl;
			}
			else//seperate out line to important bits
			{
				std::tie(type, name, value) = seperateLine(line, typeLimiterPos, nameLimiterPos);

				if (type == "display")//if type = display save to display setting map
				{
					LoadDisplaySetting(name, value);
				}
				else if (type == "audio")//if type = audio save to audio settings
				{
					LoadAudioSetting(name, value);
				}
				else//else output error to console
				{
					std::cout << type << " Bad Type" << std::endl;
				}
			}
			loadingPercentage = (currentProgress / fileSize) * 100;//workout loaded files as a percentage
			std::cout << "Loading: " << loadingPercentage << "%" << std::endl;
		}
		file.close();//close file
	}

	float AssetManager::calcFileSize(std::string filename)
	{
		std::ifstream tmpFile;
		std::string tmpLine;//tmpline to work out how many lines in file
		float fileSize = 0.0f;
		tmpFile.open(filename);
		while (std::getline(tmpFile, tmpLine))//while not at end of file 'fileSize' counts up
		{
			fileSize++;
		}
		std::cout << "File " << filename << " Size: " << fileSize << std::endl;
		tmpFile.close();

		return fileSize;
	}

	std::tuple<int, int> AssetManager::calcLimiterPositions(std::string line)
	{
		int tlPos = 0, nlPos = 0;
		for (int i = 0; i < line.size() - 1; i++)//loop through line  character by character
		{
			if (line[i] == typeLimiter) // finds first occurrence of type : name breakpoint ':'
			{
				tlPos = i;
			}
			if (line[i] == nameLimiter) //finds first occurrence of name:value breakpoint '='
			{
				nlPos = i;
			}
		}

		return { tlPos, nlPos };
	}
	std::tuple<std::string, std::string, std::string> AssetManager::seperateLine(std::string line, int tlPos, int nlPos)
	{
		std::string type = line;
		type = type.substr(0, tlPos);//type = start of line to position of type:name breakpoint ':'
		std::string name = line;
		name = name.substr(tlPos + 1, (nlPos - tlPos) - 1); //name = characters between ':' and '='
		std::string value = line;
		value = value.substr(nlPos + 1, (line.size() - nlPos) - 1); //location = from '=' to end of file

		return { type, name, value };
	}


	void AssetManager::CleanUp()//delete all assets in asset manager instance when called
	{
		if (!_textures.empty()) { cleanTextures(); } // if any textures in texture map delete them
		if (!_music.empty()) { cleanMusic(); } // if any music in music map delete them
		if (!_soundEffects.empty()) { cleanSoundEffects(); } // if any sound effects in sound effects map delete them
		if (!_displaySettings.empty()) { cleanDisplaySettings(); } // if any display settings in display settings map delete them
		if (!_audioSettings.empty()) { cleanAudioSettings(); } // if any audio settings in audio settings map delete them
	}

	void AssetManager::cleanDisplaySettings()//clears display settings map
	{
		_displaySettings.clear();
		std::cout << "Display settings cleared" << std::endl;
	}
	
	void AssetManager::cleanAudioSettings()//clears audio settings map
	{
		_audioSettings.clear();
		std::cout << "Audio settings cleared" << std::endl;
	}

	void AssetManager::cleanTextures()//iterates through textures map and deystroys them then clears map
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

	void AssetManager::cleanMusic()//iterates through music map and frees them from memory then clears map
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

	void AssetManager::cleanSoundEffects()//iterates through sound effects map and frees them from memory then clears map
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