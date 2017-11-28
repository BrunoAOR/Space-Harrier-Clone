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


void FloorObjectsFactory::start()
{
	assert(floorManager);
	m_spawnWaitTime = 2500;
	m_timeStart = Time::time();

	m_normalizedSpawnY = 0.8f;
	m_normalizedDespawnY = 0.05f;
	m_spawnMinX = -20;
	m_spawnMaxX = 20;
	m_distribution = std::uniform_int_distribution<int>(m_spawnMinX, m_spawnMaxX);
}


void FloorObjectsFactory::update()
{
	int elapsedTime = Time::time() - m_timeStart;
	if (elapsedTime > m_spawnWaitTime)
	{
		m_timeStart += m_spawnWaitTime;
		spawnObject();
	}

}

void FloorObjectsFactory::spawnObject()
{
	int currentFloorHeight = floorManager->getCurrentFloorHeight();
	float spawnX = (float)m_distribution(m_generator);

	auto go = PrefabsFactory::instantiate<TreePrefab>();
	if (go)
	{
		go->transform->setParent(gameObject()->transform);
		auto mover = go->getComponent<FloorObjectMover>();
		if (mover)
		{
			mover->init(floorManager, spawnX, 1 - m_normalizedSpawnY, 1 - m_normalizedDespawnY, 0, 1);
		}
	}
}
