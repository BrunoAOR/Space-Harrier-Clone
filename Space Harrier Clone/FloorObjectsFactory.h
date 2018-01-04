#ifndef H_FLOOR_OBJECTS_FACTORY
#define H_FLOOR_OBJECTS_FACTORY

#include <random>
#include <vector>
#include <map>
#include "Engine/Reference.h"
#include "Engine/Behaviour.h"
#include "Engine/SFX.h"
class FloorManager;
class GameObjectPool;
class Prefab;
struct ObstacleSpawnInfo;


class FloorObjectsFactory :
	public Behaviour
{
public:
	virtual void onDestroy() override;
	
	void init(const Reference<FloorManager>& floorManager, const std::vector<ObstacleSpawnInfo>& spawnInfos);
	virtual void awake() override;
	virtual void start() override;
	virtual void update() override;


private:
	void spawnObject();
	void setupNextSpawnInfo();
	
	Reference<FloorManager> m_floorManager;
	std::vector<ObstacleSpawnInfo> m_spawnInfos;

	std::map<std::string, GameObjectPool*> m_prefabPools;

	GameObjectPool* m_explosionsPool = nullptr;
	SFX m_sfxExplosion;
	
	int m_nextSpawnIndex = -1;
	int m_nextSpawnTime = -1;
	int m_elapsedTime = 0;
};


#endif // !H_FLOOR_OBJECTS_FACTORY
