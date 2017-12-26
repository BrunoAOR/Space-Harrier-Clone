#ifndef H_ENEMY_SPAWN_INFO
#define H_ENEMY_SPAWN_INFO

#include <string>


struct EnemySpawnInfo
{
public:
	EnemySpawnInfo(const std::string& aPrefabName, int aSpawnTime, int aLifeTime, int aMotionPatternIndex, const std::string& aSpawnSfxName)
		: prefabName(aPrefabName), spawnTime(aSpawnTime), lifeTime(aLifeTime), motionPatternIndex(aMotionPatternIndex), spawnSfxName(aSpawnSfxName) {}

	std::string prefabName;
	int spawnTime;
	int lifeTime;
	int motionPatternIndex;
	std::string spawnSfxName;
};


#endif // !H_ENEMY_SPAWN_INFO
