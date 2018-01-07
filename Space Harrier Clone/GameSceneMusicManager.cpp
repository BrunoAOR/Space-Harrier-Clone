#include "GameSceneMusicManager.h"

#include <assert.h>
#include "Engine/API.h"
#include "gameData.h"
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

	m_musicLevel = Audio::loadMusic(ASSET_BGM_MAIN);
	m_musicBoss = Audio::loadMusic(ASSET_BGM_BOSS);
	m_musicGameWon = Audio::loadMusic(ASSET_BGM_WIN);
	m_sfxWelcome = Audio::loadSFX(ASSET_SFX_WELCOME);
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
