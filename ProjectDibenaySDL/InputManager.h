#pragma once
#include <SDL.h>
#include <iostream>
namespace Mer
{
	class InputManager
	{
	public:
		InputManager();
		bool IsTexturePressed(SDL_Rect* texRect);
		SDL_Point& getMousePosition();
	private:
	};
}


