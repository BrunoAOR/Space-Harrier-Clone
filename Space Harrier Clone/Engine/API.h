#ifndef H_API
#define H_API

#include <string>
#include "SDL2/include/SDL_scancode.h"
#include "Reference.h"
class Prefab;
class GameObject;
struct Music;
struct SFX;


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


namespace Audio
{
	Music LoadMusic(const std::string& path);
	SFX LoadSFX(const std::string& path);
	void PlayMusic(const Music& music, int repetitions = -1);
	void PlaySFX(const SFX& sfx, int repetitions = 0);
	void PauseMusic();
	void UnpauseMusic();
	void StopMusic();
	bool isMusicPaused();
	bool isMusicPlaying();
	float getMusicVolume();
	void setMusicVolume(float normalizedVolume);
	float getSFXAverageVolume();
	void setSFXVolume(float normalizedVolume);
}


namespace Prefabs
{
	Reference<Prefab> getPrefab(const std::string& id);
	Reference<GameObject> instantiate(const Reference<Prefab>& prefab);
}


#endif // !H_API
