#include "GameSceneMusicManager.h"

#include <assert.h>
#include "Engine/API.h"
#include "Messenger.h"
#include "MessengerEventType.h"


void GameSceneMusicManager::onDestroy()
{
	Messenger::removeListener(this, MessengerEventType::BOSS_SPAWNED);

	Audio::unloadMusic(m_musicLevel);
	Audio::unloadMusic(m_musicBoss);
	Audio::unloadSFX(m_sfxWelcome);
}


void GameSceneMusicManager::awake()
{
	Messenger::addListener(this, MessengerEventType::BOSS_SPAWNED);
	m_musicLevel = Audio::loadMusic("assets/audio/bgm/Theme.wav");
	m_musicBoss = Audio::loadMusic("assets/audio/bgm/S1 MOOT Boss (Skyra).wav");
	m_sfxWelcome = Audio::loadSFX("assets/audio/sfx/SFX - Voice - Welcome to the fantasy zone.wav");
	assert(m_musicLevel && m_musicBoss && m_sfxWelcome);
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
}
