#ifndef H_AUDIO_CONTROLLER
#define H_AUDIO_CONTROLLER

#include <list>
#include <string>
#include "SDL2_mixer/include/SDL_mixer.h"
struct Music;
struct SFX;

class AudioController
{
public:
	AudioController();
	~AudioController();

	Music loadMusic(const std::string& path);
	bool unloadMusic(Music& music);
	void unloadAllMusic();
	SFX loadSFX(const std::string& path);
	bool unloadSFX(SFX& sfx);
	void unloadAllSFX();

	void playMusic(const Music& music, int repetitions = -1) const;
	void pauseMusic() const;
	void unpauseMusic() const;
	void stopMusic() const;
	bool isMusicPaused() const;
	bool isMusicPlaying() const;
	float getMusicVolume() const;
	void setMusicVolume(float normalizedVolume) const;

	void playSFX(const SFX& sfx, int repetitions = 0) const;
	float getSFXAverageVolume() const;
	void setSFXVolume(float normalizedVolume) const;

private:
	std::list<Mix_Music*> musicPtrs;
	std::list<Mix_Chunk*> sfxPtrs;

	const int MAX_VOLUME = 128;
};


#endif // !H_AUDIO_CONTROLLER
