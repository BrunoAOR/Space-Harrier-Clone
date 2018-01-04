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


Music Audio::loadMusic(const std::string& path)
{
	return engine->audio->loadMusic(path);
}


bool Audio::unloadMusic(Music& music)
{
	return engine->audio->unloadMusic(music);
}


void Audio::unloadAllMusic()
{
	engine->audio->unloadAllMusic();
}


SFX Audio::loadSFX(const std::string& path)
{
	return engine->audio->loadSFX(path);
}


bool Audio::unloadSFX(SFX& sfx)
{
	return engine->audio->unloadSFX(sfx);
}


void Audio::unloadAllSFX()
{
	engine->audio->unloadAllSFX();
}


void Audio::playMusic(const Music& music, int repetitions)
{
	engine->audio->playMusic(music, repetitions);
}


void Audio::playSFX(const SFX& sfx, int repetitions)
{
	engine->audio->playSFX(sfx, repetitions);
}


void Audio::pauseMusic()
{
	engine->audio->pauseMusic();
}


void Audio::unpauseMusic()
{
	engine->audio->unpauseMusic();
}


void Audio::stopMusic()
{
	engine->audio->stopMusic();
}


bool Audio::isMusicPaused()
{
	return engine->audio->isMusicPaused();
}


bool Audio::isMusicPlaying()
{
	return engine->audio->isMusicPlaying();
}


float Audio::getMusicVolume()
{
	return engine->audio->getMusicVolume();
}


void Audio::setMusicVolume(float normalizedVolume)
{
	engine->audio->setMusicVolume(normalizedVolume);
}


float Audio::getSFXAverageVolume()
{
	return engine->audio->getSFXAverageVolume();
}


void Audio::setSFXVolume(float normalizedVolume)
{
	engine->audio->setSFXVolume(normalizedVolume);
}


Reference<Prefab> Prefabs::getPrefab(const std::string& id)
{
	return engine->prefabsFactory->getPrefab(id);
}


Reference<GameObject> Prefabs::instantiate(const Reference<Prefab>& prefab)
{
	return engine->prefabsFactory->instantiate(prefab);
}
