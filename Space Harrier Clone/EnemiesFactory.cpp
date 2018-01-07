#include "EnemiesFactory.h"

#include <assert.h>
#include <algorithm>
#include "Engine/gameConfig.h"
#include "Engine/API.h"
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "gameData.h"
#include "FloorManager.h"
#include "GameObjectPool.h"
#include "Enemy.h"
#include "MotionPattern.h"
#include "ExplosiveObject.h"
#include "EnemySpawnInfo.h"
#include "Boss1.h"
#include "Messenger.h"
#include "MessengerEventType.h"


void EnemiesFactory::onDestroy()
{
	for (auto it = m_prefabPools.begin(); it != m_prefabPools.end(); ++it)
	{
		delete (it->second);
	}
	m_prefabPools.clear();

	Audio::unloadSFX(m_sfxExplosion);
	Audio::unloadSFX(m_sfxEnemyShot);
	for (auto it = m_spawnSfxs.begin(); it != m_spawnSfxs.end(); ++it)
	{
		Audio::unloadSFX(it->second);
	}
	m_spawnSfxs.clear();

	delete m_explosionsPool;
	m_explosionsPool = nullptr;
	delete m_enemyShotsPool;
	m_enemyShotsPool = nullptr;
}


void EnemiesFactory::init(const Reference<Transform>& playerTransform, const Reference<FloorManager>& floorManager, const std::vector<EnemySpawnInfo>& spawnInfos, const std::vector<MotionPattern>& motionPatterns)
{
	m_playerTransform = playerTransform;
	m_floorManager = floorManager;
	m_spawnInfos = spawnInfos;
	m_motionPatterns = motionPatterns;
	assert(m_playerTransform && m_floorManager);

	// Ensure spawnInfos are sorted by spawnTime
	std::sort(m_spawnInfos.begin(), m_spawnInfos.end(), [](EnemySpawnInfo info1, EnemySpawnInfo info2) -> bool { return info1.spawnTime < info2.spawnTime; });

	// Get the required Prefabs and Sfxs
	bool isBoss;
	for (EnemySpawnInfo spawnInfo : m_spawnInfos)
	{
		isBoss = spawnInfo.prefabName.find("Boss") != std::string::npos;
		if (m_prefabPools.count(spawnInfo.prefabName) == 0)
		{
			Reference<Prefab> prefab = Prefabs::getPrefab(spawnInfo.prefabName);
			assert(prefab);
			m_prefabPools[spawnInfo.prefabName] = (new GameObjectPool(prefab, isBoss ? 1 : 6));
		}

		if (!isBoss)
		{
			assert(spawnInfo.motionPatternIndex >= 0 && spawnInfo.motionPatternIndex < (int)m_motionPatterns.size());

			if (m_spawnSfxs.count(spawnInfo.spawnSfxName) == 0)
			{
				SFX sfx = Audio::loadSFX(spawnInfo.spawnSfxName);
				assert(sfx);
				m_spawnSfxs[spawnInfo.spawnSfxName] = sfx;
			}
		}
	}
}


void EnemiesFactory::awake()
{
	m_explosionsPool = new GameObjectPool(Prefabs::getPrefab(EXPLOSION_PREFAB), 4);
	m_enemyShotsPool = new GameObjectPool(Prefabs::getPrefab(ENEMY_SHOT_PREFAB), 6);
	assert(m_explosionsPool && m_enemyShotsPool);

	m_sfxExplosion = Audio::loadSFX(ASSET_SFX_EXPLOSION);
	m_sfxEnemyShot = Audio::loadSFX(ASSET_SFX_ENEMY_SHOT);
	assert(m_sfxExplosion && m_sfxEnemyShot);

}


void EnemiesFactory::start()
{
	m_elapsedTime = 0;
	if (m_spawnInfos.size() > 0)
	{
		setupNextSpawnInfo();
	}
}


void EnemiesFactory::update()
{
	if (m_nextSpawnIndex == -1 || m_floorManager->freezeAtBottom)
	{
		return;
	}
		
	while (m_elapsedTime > m_nextSpawnTime && m_nextSpawnIndex != -1)
	{
		spawnEnemy();
		setupNextSpawnInfo();
	}

	m_elapsedTime += Time::deltaTime();
}


void EnemiesFactory::spawnEnemy()
{
	EnemySpawnInfo spawnInfo = m_spawnInfos[m_nextSpawnIndex];
	
	bool isBoss = spawnInfo.prefabName.find("Boss") != std::string::npos;

	auto go = m_prefabPools[spawnInfo.prefabName]->getGameObject();
	assert(go);
	go->transform->setParent(gameObject()->transform);
	if (!isBoss) {
		auto enemy = go->getComponent<Enemy>();
		if (enemy)
		{
			enemy->init(m_motionPatterns[spawnInfo.motionPatternIndex].getLifeTimeMS(), m_motionPatterns[spawnInfo.motionPatternIndex], m_floorManager, m_playerTransform, m_enemyShotsPool, m_sfxEnemyShot);
		}

		auto explosiveObject = go->getComponent<ExplosiveObject>();
		if (explosiveObject)
		{
			explosiveObject->init(m_explosionsPool, m_sfxExplosion);
		}
		Audio::playSFX(m_spawnSfxs[spawnInfo.spawnSfxName]);
	}
	else
	{
		go->transform->setParent(gameObject()->transform);
		auto boss1 = go->getComponent<Boss1>();
		assert(boss1);
		boss1->init(m_floorManager, m_playerTransform, m_sfxExplosion);
		Messenger::broadcastEvent(MessengerEventType::BOSS_SPAWNED);
	}
	go->setActive(true);
}


void EnemiesFactory::spawnBoss()
{
	auto go = Prefabs::instantiate(Prefabs::getPrefab(BOSS_1_PREFAB));
	assert(go);

	go->transform->setParent(gameObject()->transform);
	auto boss1 = go->getComponent<Boss1>();
	assert(boss1);
	boss1->init(m_floorManager, m_playerTransform, m_sfxExplosion);
}


void EnemiesFactory::setupNextSpawnInfo()
{
	++m_nextSpawnIndex;
	if (m_nextSpawnIndex < (int)m_spawnInfos.size())
	{
		m_nextSpawnTime = m_spawnInfos[m_nextSpawnIndex].spawnTime;
	}
	else
	{
		m_nextSpawnIndex = -1;
		m_nextSpawnTime = -1;
		m_elapsedTime = -2000;
	}
}
