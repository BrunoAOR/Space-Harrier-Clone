#ifndef H_FLOOR_OBJECTS_FACTORY
#define H_FLOOR_OBJECTS_FACTORY

#include <random>
#include <vector>
#include "Engine/Reference.h"
#include "Engine/Behaviour.h"
#include "Engine/SFX.h"
class FloorManager;
class GameObjectPool;
class Prefab;


class FloorObjectsFactory :
	public Behaviour
{
public:
	~FloorObjectsFactory();
	
	void init(const Reference<FloorManager>& floorManager);
	virtual void start() override;
	virtual void update() override;


private:
	void spawnObject();
	
	Reference<FloorManager> m_floorManager;

	std::vector<Reference<Prefab>> m_prefabs;
	std::vector<GameObjectPool*> m_prefabPools;

	GameObjectPool* m_explosionsPool;
	SFX m_sfxExplosion;
	
	int m_currPrefabIndex = 0;
	int m_elapsedTime = 0;
	int m_spawnWaitTime = 0;

	float m_normalizedSpawnY = 0;
	float m_normalizedDespawnY = 0;
	int m_spawnMinX = 0;
	int m_spawnMaxX = 0;

	std::default_random_engine m_generator;
	std::uniform_int_distribution<int> m_distribution;
};


#endif // !H_FLOOR_OBJECTS_FACTORY
