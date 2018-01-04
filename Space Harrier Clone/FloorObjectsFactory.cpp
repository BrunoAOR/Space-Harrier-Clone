#include "FloorObjectsFactory.h"

#include <algorithm>
#include <assert.h>
#include "Engine/API.h"
#include "Engine/PrefabsFactory.h"
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "FloorManager.h"
#include "TreePrefab.h"
#include "FloorObjectMover.h"
#include "ObjectEffectType.h"
#include "GameObjectPool.h"
#include "ExplosionPrefab.h"
#include "ExplosiveObject.h"
#include "ObstacleSpawnInfo.h"


void FloorObjectsFactory::onDestroy()
{
	for (auto it = m_prefabPools.begin(); it != m_prefabPools.end(); ++it)
	{
		delete (it->second);
	}
	m_prefabPools.clear();

	Audio::unloadSFX(m_sfxExplosion);

	delete m_explosionsPool;
	m_explosionsPool = nullptr;
}


void FloorObjectsFactory::init(const Reference<FloorManager>& floorManager, const std::vector<ObstacleSpawnInfo>& spawnInfos)
{
	m_floorManager = floorManager;
	m_spawnInfos = spawnInfos;

	assert(m_floorManager);

	// Ensure spawnInfos are sorted by spawnTime
	std::sort(m_spawnInfos.begin(), m_spawnInfos.end(), [](ObstacleSpawnInfo info1, ObstacleSpawnInfo info2) -> bool { return info1.spawnTime < info2.spawnTime; });

	// Get the required Prefabs
	for (ObstacleSpawnInfo spawnInfo : m_spawnInfos)
	{
		if (m_prefabPools.count(spawnInfo.prefabName) == 0)
		{
			Reference<Prefab> prefab = Prefabs::getPrefab(spawnInfo.prefabName);
			assert(prefab);
			m_prefabPools[spawnInfo.prefabName] = (new GameObjectPool(prefab, 4));
		}
	}

	m_explosionsPool = new GameObjectPool(Prefabs::getPrefab("ExplosionPrefab"), 3);
	assert(m_explosionsPool);

}


void FloorObjectsFactory::awake()
{
	m_sfxExplosion = Audio::loadSFX("assets/audio/sfx/SFX - Explosion.wav");
	assert(m_sfxExplosion);
}

void FloorObjectsFactory::start()
{
	m_elapsedTime = 0;
	if (m_spawnInfos.size() > 0)
	{
		setupNextSpawnInfo();
	}
}


void FloorObjectsFactory::update()
{
	if (m_nextSpawnIndex == -1 || m_floorManager->freezeAtBottom)
	{
		return;
	}

	while (m_elapsedTime > m_nextSpawnTime && m_nextSpawnIndex != -1)
	{
		spawnObject();
		setupNextSpawnInfo();
	}

	m_elapsedTime += Time::deltaTime();
}

void FloorObjectsFactory::spawnObject()
{
	ObstacleSpawnInfo spawnInfo = m_spawnInfos[m_nextSpawnIndex];
	auto go = m_prefabPools[spawnInfo.prefabName]->getGameObject();

	if (go)
	{
		go->transform->setParent(gameObject()->transform);
		Reference<FloorObjectMover> mover = go->getComponent<FloorObjectMover>();
		if (mover)
		{
			mover->init(m_floorManager, spawnInfo.absoluteSpawnXPos, 1 - spawnInfo.normalizedSpawnYPos, 1 - spawnInfo.normalizedDespawnYPos, 0, 1);
		}
		auto explosiveObject = go->getComponent<ExplosiveObject>();
		if (explosiveObject)
		{
			explosiveObject->init(m_explosionsPool, m_sfxExplosion);
		}
		go->setActive(true);
	}
}


void FloorObjectsFactory::setupNextSpawnInfo()
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
		m_elapsedTime = 0;
	}
}
