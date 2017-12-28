#include "EnemiesFactory.h"

#include <assert.h>
#include <algorithm>
#include "Engine/gameConfig.h"
#include "Engine/API.h"
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "FloorManager.h"
#include "GameObjectPool.h"
#include "Enemy.h"
#include "MotionPattern.h"
#include "ExplosiveObject.h"
#include "EnemySpawnInfo.h"


EnemiesFactory::~EnemiesFactory()
{
	for (auto it = m_prefabPools.begin(); it != m_prefabPools.end(); ++it)
	{
		delete (it->second);
	}
	m_prefabPools.clear();

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
	for (EnemySpawnInfo spawnInfo : m_spawnInfos)
	{
		assert(spawnInfo.motionPatternIndex >= 0 && spawnInfo.motionPatternIndex < (int)m_motionPatterns.size());
		if (m_prefabPools.count(spawnInfo.prefabName) == 0)
		{
			Reference<Prefab> prefab = Prefabs::getPrefab(spawnInfo.prefabName);
			assert(prefab);
			m_prefabPools[spawnInfo.prefabName] = (new GameObjectPool(prefab, 4));
		}
		if (m_spawnSfxs.count(spawnInfo.spawnSfxName) == 0)
		{
			SFX sfx = Audio::LoadSFX(spawnInfo.spawnSfxName);
			assert(sfx);
			m_spawnSfxs[spawnInfo.spawnSfxName] = sfx;
		}

	}

	m_explosionsPool = new GameObjectPool(Prefabs::getPrefab("ExplosionPrefab"), 4);
	m_enemyShotsPool = new GameObjectPool(Prefabs::getPrefab("EnemyShotPrefab"), 6);
	m_sfxExplosion = Audio::LoadSFX("assets/audio/sfx/SFX - Explosion.wav");
	m_sfxEnemyShot = Audio::LoadSFX("assets/audio/sfx/SFX - EnemyShot.wav");
	assert(m_explosionsPool && m_enemyShotsPool && m_sfxExplosion && m_sfxEnemyShot);
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
	auto go = m_prefabPools[spawnInfo.prefabName]->getGameObject();

	if (go)
	{
		go->transform->setParent(gameObject()->transform);
		auto enemy = go->getComponent<Enemy>();
		if (enemy)
		{
			enemy->init(spawnInfo.lifeTime, m_motionPatterns[spawnInfo.motionPatternIndex], m_floorManager, m_playerTransform, m_enemyShotsPool, m_sfxEnemyShot);
		}

		auto explosiveObject = go->getComponent<ExplosiveObject>();
		if (explosiveObject)
		{
			explosiveObject->init(m_explosionsPool, m_sfxExplosion);
		}
		go->setActive(true);
		Audio::PlaySFX(m_spawnSfxs[spawnInfo.spawnSfxName]);
	}
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
		setupNextSpawnInfo();
	}
}
