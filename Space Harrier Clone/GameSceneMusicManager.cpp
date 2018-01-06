#include "GameSceneMusicManager.h"

#include <assert.h>
#include "Engine/API.h"
#include "Messenger.h"
#include "MessengerEventType.h"


void GameSceneMusicManager::onDestroy()
{
	Messenger::removeListener(this, MessengerEventType::BOSS_SPAWNED);
	Messenger::removeListener(this, MessengerEventType::GAME_WON);

	Audio::unloadMusic(m_musicLevel);
	Audio::unloadMusic(m_musicBoss);
	Audio::unloadMusic(m_musicGameWon);
	Audio::unloadSFX(m_sfxWelcome);
}


void GameSceneMusicManager::awake()
{
	Messenger::addListener(this, MessengerEventType::BOSS_SPAWNED);
	Messenger::addListener(this, MessengerEventType::GAME_WON);

	m_musicLevel = Audio::loadMusic("assets/audio/bgm/Theme.ogg");
	m_musicBoss = Audio::loadMusic("assets/audio/bgm/S1 MOOT Boss (Skyra).ogg");
	m_musicGameWon = Audio::loadMusic("assets/audio/bgm/Lake Side Memory (WIN).ogg");
	m_sfxWelcome = Audio::loadSFX("assets/audio/sfx/SFX - Voice - Welcome to the fantasy zone.wav");
	assert(m_musicLevel && m_musicBoss && m_musicGameWon && m_sfxWelcome);
}


void GameSceneMusicManager::start()
{
	Audio::playMusic(m_musicLevel);
	Audio::playSFX(m_sfxWelcome);
}


void GameSceneMusicManager::eventsCallback(MessengerEventType eventType)
{
	if (eventType == MessengerEventType::BOSS_SPAWNED)
	{
		Audio::playMusic(m_musicBoss);
	}
	else if (eventType == MessengerEventType::GAME_WON)
	{
		Audio::playMusic(m_musicGameWon);
	}
}
