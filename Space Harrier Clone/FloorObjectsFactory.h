#ifndef H_FLOOR_OBJECTS_FACTORY
#define H_FLOOR_OBJECTS_FACTORY

#include <random>
#include "Engine/Reference.h"
#include "Engine/Behaviour.h"
class FloorManager;
class GameObjectPool;
class Prefab;


class FloorObjectsFactory :
	public Behaviour
{
public:
	~FloorObjectsFactory();
	
	virtual void start() override;
	virtual void update() override;

	Reference<FloorManager> floorManager;

private:
	void spawnObject();

	Reference<Prefab> m_prefabTree;
	GameObjectPool* m_treePool = nullptr;
	
	int m_timeStart = 0;
	int m_spawnWaitTime = 0;

	float m_normalizedSpawnY = 0;
	float m_normalizedDespawnY = 0;
	int m_spawnMinX = 0;
	int m_spawnMaxX = 0;

	std::default_random_engine m_generator;
	std::uniform_int_distribution<int> m_distribution;
};


#endif // !H_FLOOR_OBJECTS_FACTORY
