#ifndef H_OBSTACLE_SPAWN_INFO
#define H_OBSTACLE_SPAWN_INFO

#include <string>
#include "Engine/Vector2.h"


struct ObstacleSpawnInfo
{
public:
	ObstacleSpawnInfo(const std::string& aPrefabName, int aSpawnTime, float anAbsoluteSpawnXPosition, float aNormalizedSpawnYPosition, float aNormalizedDespawnYPos)
		: prefabName(aPrefabName), spawnTime(aSpawnTime), absoluteSpawnXPos(anAbsoluteSpawnXPosition), normalizedSpawnYPos (aNormalizedSpawnYPosition), normalizedDespawnYPos (aNormalizedDespawnYPos) {}

	std::string prefabName;
	int spawnTime;
	float absoluteSpawnXPos;
	float normalizedSpawnYPos;
	float normalizedDespawnYPos;
};


#endif // !H_OBSTACLE_SPAWN_INFO
