#include "GameSceneMusicManager.h"

#include <assert.h>
#include "Engine/API.h"
#include "Messenger.h"
#include "MessengerEventType.h"


void GameSceneMusicManager::onDestroy()
{
	Messenger::removeListener(this, MessengerEventType::BOSS_SPAWNED);
}


void GameSceneMusicManager::awake()
{
	Messenger::addListener(this, MessengerEventType::BOSS_SPAWNED);
	m_musicLevel = Audio::LoadMusic("assets/audio/bgm/Theme.wav");
	m_musicBoss = Audio::LoadMusic("assets/audio/bgm/S1 MOOT Boss (Skyra).wav");
	m_sfxWelcome = Audio::LoadSFX("assets/audio/sfx/SFX - Voice - Welcome to the fantasy zone.wav");
	assert(m_musicLevel && m_musicBoss && m_sfxWelcome);
}


void GameSceneMusicManager::start()
{
	Audio::PlayMusic(m_musicLevel);
	Audio::PlaySFX(m_sfxWelcome);
}


void GameSceneMusicManager::eventsCallback(MessengerEventType eventType)
{
	if (eventType == MessengerEventType::BOSS_SPAWNED)
	{
		Audio::PlayMusic(m_musicBoss);
	}
}
