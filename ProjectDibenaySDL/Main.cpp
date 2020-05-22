

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <string>
#include "Game.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int main(int argc, char* args[])
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		Mer::Game(SCREEN_WIDTH, SCREEN_HEIGHT, "Dibenay");
	}

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}