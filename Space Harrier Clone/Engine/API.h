#ifndef H_API
#define H_API

#include "SDL2/include/SDL_scancode.h"


namespace Scenes
{
	void loadScene(unsigned int index);
}


namespace Input
{
	bool getKey(SDL_Scancode scancode);
	bool getKeyUp(SDL_Scancode scancode);
	bool getKeyDown(SDL_Scancode scancode);
}


namespace Time
{
	Uint32 time();
	Uint32 deltaTime();
}


#endif // !H_API
