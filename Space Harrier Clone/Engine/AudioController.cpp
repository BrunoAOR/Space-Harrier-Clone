#include "AudioController.h"

#include "globals.h"
#include "Music.h"
#include "SFX.h"
#include "engineUtils.h"


AudioController::AudioController()
{
}


AudioController::~AudioController()
{
	OutputLog("INFO: Freeing audio system and audio resources");
	for (auto ptr : musicPtrs)
	{
		Mix_FreeMusic(ptr);
	}
	musicPtrs.clear();
	for (auto ptr : sfxPtrs)
	{
		Mix_FreeChunk(ptr);
	}
	sfxPtrs.clear();
}


Music AudioController::loadMusic(const std::string& path)
{
	Mix_Music* sdlMusic = nullptr;
	sdlMusic = Mix_LoadMUS(path.c_str());
	if (sdlMusic == nullptr)
	{
		OutputLog("WARNING: Could not load music with path: %s. Mix_LoadMUS: %s", path.c_str(), Mix_GetError());
	}
	else
	{
		musicPtrs.push_back(sdlMusic);
	}
	return Music(sdlMusic);
}


bool AudioController::unloadMusic(Music& music)
{
	auto it = std::find(musicPtrs.begin(), musicPtrs.end(), music.m_music);
	if (it != musicPtrs.end())
	{
		Mix_FreeMusic(*it);
		musicPtrs.erase(it);
		music.m_music = nullptr;
		return true;
	}
	return false;
}


void AudioController::unloadAllMusic()
{
	stopMusic();
	for (auto ptr : musicPtrs)
	{
		Mix_FreeMusic(ptr);
	}
	musicPtrs.clear();
}


SFX AudioController::loadSFX(const std::string& path)
{
	Mix_Chunk* sdlSfx = nullptr;
	sdlSfx = Mix_LoadWAV(path.c_str());
	if (sdlSfx == nullptr)
	{
		OutputLog("WARNING: Could not load sfx with path: %s. Mix_LoadWAV: %s", path.c_str(), Mix_GetError());
	}
	else
	{
		sfxPtrs.push_back(sdlSfx);
	}
	return SFX(sdlSfx);
}


bool AudioController::unloadSFX(SFX& sfx)
{
	auto it = std::find(sfxPtrs.begin(), sfxPtrs.end(), sfx.m_sfx);
	if (it != sfxPtrs.end())
	{
		Mix_FreeChunk(*it);
		sfxPtrs.erase(it);
		sfx.m_sfx = nullptr;
		return true;
	}
	return false;
}


void AudioController::unloadAllSFX()
{
	Mix_HaltChannel(-1);
	for (auto ptr : sfxPtrs)
	{
		Mix_FreeChunk(ptr);
	}
	sfxPtrs.clear();
}


void AudioController::playMusic(const Music& music, int repetitions) const
{
	Mix_Music* sdlMusic = music.m_music;
	if (Mix_PlayMusic(sdlMusic, repetitions) != 0)
	{
		OutputLog("WARNING: Could not play music. Mix_PlayMusic: %s", Mix_GetError());
	}
}


void AudioController::pauseMusic() const
{
	Mix_PauseMusic();
}


void AudioController::unpauseMusic() const
{
	Mix_ResumeMusic();
}


void AudioController::stopMusic() const
{
	Mix_HaltMusic();
}


bool AudioController::isMusicPaused() const
{
	return Mix_PausedMusic() == 1;
}


bool AudioController::isMusicPlaying() const
{
	return Mix_PlayingMusic() != 0;
}


float AudioController::getMusicVolume() const
{
	return (Mix_VolumeMusic(-1) / (float)MAX_VOLUME);
}


void AudioController::setMusicVolume(float normalizedVolume) const
{
	if (normalizedVolume < 0 || normalizedVolume > 1)
	{
		OutputLog("WARNING: Parameter normalizedVolume (%f) for setMusicVolume function is out of range (0-1). It will be clamped to the range!", normalizedVolume);
	}
	normalizedVolume = EngineUtils::clamp(normalizedVolume, 0, 1);
	Mix_VolumeMusic((int)(normalizedVolume * MAX_VOLUME));
}


void AudioController::playSFX(const SFX& sfx, int repetitions) const
{
	Mix_Chunk* sdlSfx = sfx.m_sfx;
	if (Mix_PlayChannel(-1, sdlSfx, repetitions) == -1)
	{
		OutputLog("WARNING: Could not play chunk. Mix_PlayChannel: %s", Mix_GetError());
	}
}


float AudioController::getSFXAverageVolume() const
{
	return (Mix_Volume(-1, -1) / (float)MAX_VOLUME);
}


void AudioController::setSFXVolume(float normalizedVolume) const
{
	if (normalizedVolume < 0 || normalizedVolume > 1)
	{
		OutputLog("WARNING: Parameter normalizedVolume (%f) for setSFXVolume function is out of range (0-1). It will be clamped to the range!", normalizedVolume);
	}
	normalizedVolume = EngineUtils::clamp(normalizedVolume, 0, 1);
	Mix_Volume(-1, (int)(normalizedVolume * MAX_VOLUME));
}
