#include "API.h"

#include "Engine.h"
#include "SceneManager.h"
#include "InputController.h"
#include "TimeController.h"


void Scenes::loadScene(unsigned int index)
{
	engine->sceneManager->loadScene(index);
}


bool Input::getKey(SDL_Scancode scancode)
{
	return engine->input->getKey(scancode);
}


bool Input::getKeyUp(SDL_Scancode scancode)
{
	return engine->input->getKeyUp(scancode);
}


bool Input::getKeyDown(SDL_Scancode scancode)
{
	return engine->input->getKeyDown(scancode);
}


Uint32 Time::time()
{
	return engine->time->time();
}


Uint32 Time::deltaTime()
{
	return engine->time->deltaTime();
}
