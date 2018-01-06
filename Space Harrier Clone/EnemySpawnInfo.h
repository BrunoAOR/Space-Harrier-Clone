#ifndef H_ENEMY_SPAWN_INFO
#define H_ENEMY_SPAWN_INFO

#include <string>


struct EnemySpawnInfo
{
public:
	EnemySpawnInfo(const std::string& aPrefabName, int aSpawnTime, int aMotionPatternIndex, const std::string& aSpawnSfxName)
		: prefabName(aPrefabName), spawnTime(aSpawnTime), motionPatternIndex(aMotionPatternIndex), spawnSfxName(aSpawnSfxName) {}

	std::string prefabName;
	int spawnTime;
	int motionPatternIndex;
	std::string spawnSfxName;
};


#endif // !H_ENEMY_SPAWN_INFO
