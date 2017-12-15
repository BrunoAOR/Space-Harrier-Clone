#include "FloorObjectsFactory.h"

#include <random>
#include <assert.h>
#include "Engine/API.h"
#include "Engine/PrefabsFactory.h"
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "FloorManager.h"
#include "TreePrefab.h"
#include "FloorObjectMover.h"
#include "FloorObjectType.h"
#include "GameObjectPool.h"


FloorObjectsFactory::~FloorObjectsFactory()
{
	delete m_treePool;
	m_treePool = nullptr;
}


void FloorObjectsFactory::init(const Reference<FloorManager>& floorManager)
{
	m_floorManager = floorManager;
	assert(m_floorManager);
}

void FloorObjectsFactory::start()
{
	m_prefabTree = Prefabs::getPrefab("TreePrefab");
	assert(m_floorManager && m_prefabTree);

	m_treePool = new GameObjectPool(m_prefabTree, 4);

	m_spawnWaitTime = 2500;
	m_elapsedTime = 0;

	m_normalizedSpawnY = 0.8f;
	m_normalizedDespawnY = 0.05f;
	m_spawnMinX = -20;
	m_spawnMaxX = 20;
	m_distribution = std::uniform_int_distribution<int>(m_spawnMinX, m_spawnMaxX);
}


void FloorObjectsFactory::update()
{
	if (m_floorManager->freezeAtBottom)
	{
		return;
	}
	m_elapsedTime += Time::deltaTime();
	if (m_elapsedTime > m_spawnWaitTime)
	{
		m_elapsedTime -= m_spawnWaitTime;
		spawnObject();
	}

}

void FloorObjectsFactory::spawnObject()
{
	int currentFloorHeight = m_floorManager->getCurrentFloorHeight();
	float spawnX = (float)m_distribution(m_generator);

	auto go = m_treePool->getGameObject();
	if (go)
	{
		go->transform->setParent(gameObject()->transform);
		auto mover = go->getComponent<FloorObjectMover>();
		if (mover)
		{
			mover->init(m_floorManager, FloorObjectType::DIE, spawnX, 1 - m_normalizedSpawnY, 1 - m_normalizedDespawnY, 0, 1);
			mover->restart();
		}
		go->setActive(true);
	}
}
