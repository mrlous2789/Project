

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <string>
#include "Game.h"
#include <SDL_mixer.h>

//Screen dimension constants
int SCREEN_WIDTH = 1280;
int SCREEN_HEIGHT = 720;
std::string gameTitle = "Dibenay";

bool initSDL();

int main(int argc, char* args[])
{
	//Initialize SDL
	if (!initSDL())
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		Mer::Game(SCREEN_WIDTH, SCREEN_HEIGHT, gameTitle);
	}

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}

bool initSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return false;
	}

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
	{
		return false;
	}

	return true;
}