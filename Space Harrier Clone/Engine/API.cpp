#include "API.h"

#include "Engine.h"
#include "SceneManager.h"
#include "InputController.h"
#include "TimeController.h"
#include "AudioController.h"
#include "PrefabsFactory.h"
#include "Music.h"
#include "SFX.h"


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


Music Audio::LoadMusic(const std::string & path)
{
	return engine->audio->LoadMusic(path);
}


SFX Audio::LoadSFX(const std::string & path)
{
	return engine->audio->LoadSFX(path);
}


void Audio::PlayMusic(const Music & music, int repetitions)
{
	engine->audio->PlayMusic(music, repetitions);
}


void Audio::PlaySFX(const SFX & sfx, int repetitions)
{
	engine->audio->PlaySFX(sfx, repetitions);
}


void Audio::PauseMusic()
{
	engine->audio->PauseMusic();
}


void Audio::UnpauseMusic()
{
	engine->audio->UnpauseMusic();
}


void Audio::StopMusic()
{
	engine->audio->StopMusic();
}


bool Audio::isMusicPaused()
{
	return engine->audio->isMusicPaused();
}


bool Audio::isMusicPlaying()
{
	return engine->audio->isMusicPlaying();
}


Reference<Prefab> Prefabs::getPrefab(const std::string& id)
{
	return engine->prefabsFactory->getPrefab(id);
}


Reference<GameObject> Prefabs::instantiate(const Reference<Prefab>& prefab)
{
	return engine->prefabsFactory->instantiate(prefab);
}
