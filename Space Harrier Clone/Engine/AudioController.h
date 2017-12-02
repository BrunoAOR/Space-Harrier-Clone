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

	Music LoadMusic(const std::string& path);
	SFX LoadSFX(const std::string& path);

	void PlayMusic(const Music& music, int repetitions = -1) const;
	void PauseMusic() const;
	void UnpauseMusic() const;
	void StopMusic() const;
	bool isMusicPaused() const;
	bool isMusicPlaying() const;

	void PlaySFX(const SFX& sfx, int repetitions = 0) const;

private:
	std::list<Mix_Music*> musicPtrs;
	std::list<Mix_Chunk*> sfxPtrs;

};


#endif // !H_AUDIO_CONTROLLER
