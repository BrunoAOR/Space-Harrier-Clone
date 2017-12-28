#ifndef H_ENEMIES_FACTORY
#define H_ENEMIES_FACTORY

#include <vector>
#include <map>
#include "Engine/Behaviour.h"
#include "Engine/Reference.h"
#include "Engine/SFX.h"
class Transform;
class MotionPattern;
class GameObjectPool;
class FloorManager;
class Prefab;
struct EnemySpawnInfo;


class EnemiesFactory :
	public Behaviour
{
public:
	~EnemiesFactory();

	void init(const Reference<Transform>& playerTransform, const Reference<FloorManager>& floorManager, const std::vector<EnemySpawnInfo>& spawnInfos, const std::vector<MotionPattern>& motionPAtterns);
	virtual void start() override;
	virtual void update() override;

private:
	void spawnEnemy();
	void setupNextSpawnInfo();

	Reference<Transform> m_playerTransform;
	Reference<FloorManager> m_floorManager;
	std::vector<EnemySpawnInfo> m_spawnInfos;
	std::vector<MotionPattern> m_motionPatterns;

	std::map<std::string, GameObjectPool*> m_prefabPools;
	std::map<std::string, SFX> m_spawnSfxs;

	GameObjectPool* m_explosionsPool = nullptr;
	GameObjectPool* m_enemyShotsPool = nullptr;
	SFX m_sfxExplosion;
	SFX m_sfxEnemyShot;

	int m_nextSpawnIndex = -1;
	int m_nextSpawnTime = -1;
	int m_elapsedTime = 0;
};


#endif // !H_ENEMIES_FACTORY
