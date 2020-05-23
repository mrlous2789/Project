#include "InputManager.h"
namespace Mer
{
	InputManager::InputManager()
	{

	}

	bool InputManager::IsTexturePressed(SDL_Rect* texRect)
	{
		SDL_Point mp = getMousePosition();
		if (mp.x > texRect->x && mp.x < texRect->w + texRect->x && mp.y > texRect->y &&  mp.y < texRect->h + texRect->y)
		{
			return true;
		}
		return false;
	}

	SDL_Point& InputManager::getMousePosition()
	{
		SDL_Point mouse_position;
		SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
		return mouse_position;
		std::cout << mouse_position.x << mouse_position.y << std::endl;
	}
}