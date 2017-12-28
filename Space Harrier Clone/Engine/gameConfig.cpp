#include "gameConfig.h"

#include "Engine.h"
#include "SceneManager.h"
#include "PrefabsFactory.h"
#include "CollisionSystemSetup.h"


const int SCREEN_SIZE = 2;
const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 224;

const int POST_DIE_BLINK_CYCLE_DURATION = 150;
const int POST_DIE_BLINK_FLOOR_CYCLE_COUNT = 7;
const int POST_DIE_BLINK_FREE_CYCLE_COUNT = 15;

#include "../GameScene.h"
bool scenesConfig()
{
	// Success flag
	bool success = true;

	success &= engine->sceneManager->addScene<GameScene>();
	if (success)
	{
		engine->sceneManager->loadScene(0);
	}
	return success;
}


#include "../PlayerPrefab.h"
#include "../TreePrefab.h"
#include "../SmallBushPrefab.h"
#include "../BigBushPrefab.h"
#include "../RockPrefab.h"
#include "../PlayerShotPrefab.h"
#include "../ExplosionPrefab.h"
#include "../EnemyShipPrefab.h"
#include "../EnemyShotPrefab.h"
bool prefabsConfig()
{
	// Success flag
	bool success = true;

	success &= engine->prefabsFactory->addPrefab<PlayerPrefab>("PlayerPrefab");
	success &= engine->prefabsFactory->addPrefab<TreePrefab>("TreePrefab");
	success &= engine->prefabsFactory->addPrefab<SmallBushPrefab>("SmallBushPrefab");
	success &= engine->prefabsFactory->addPrefab<BigBushPrefab>("BigBushPrefab");
	success &= engine->prefabsFactory->addPrefab<RockPrefab>("RockPrefab");
	success &= engine->prefabsFactory->addPrefab<PlayerShotPrefab>("PlayerShotPrefab");
	success &= engine->prefabsFactory->addPrefab<ExplosionPrefab>("ExplosionPrefab");
	success &= engine->prefabsFactory->addPrefab<EnemyShipPrefab>("EnemyShipPrefab");
	success &= engine->prefabsFactory->addPrefab<EnemyShotPrefab>("EnemyShotPrefab");

	return success;
}


std::vector<std::string> renderLayersConfig()
{
	return std::vector<std::string>{"Background", "Shadows", "Main", "Foreground" };
}


CollisionSystemSetup collisionSystemSetup()
{
	CollisionSystemSetup css;
	// The list of collisionLayers. There is always a "default" layer that collides with everything else
	css.layersNames = std::vector<std::string>{ "Player", "PlayerShot", "Enemy", "EnemyShot", "Obstacle" };
	// The matrix that describes whether a collider from a certain layer collides with one from another (or the same) layer
	css.collisionMatrix.push_back(std::vector<bool>{ false, false, true, true, true });
	css.collisionMatrix.push_back(std::vector<bool>{ false, false, true, false, true });
	css.collisionMatrix.push_back(std::vector<bool>{  true, true, false, false, false });
	css.collisionMatrix.push_back(std::vector<bool>{  true, false, false, false, false });
	css.collisionMatrix.push_back(std::vector<bool>{  true, true, false, false, false });
	// Whether the zIndexCollisionRange is taken into account when calculating collisions within a layer (if not, collisions are calculated regardless of the zIndex)
	css.useZIndexWithinLayer = true;
	// Whether the zIndexCollisionRange is taken into account when calculating collisions among different colliding layers (if not, collisions are calculated regardless of the zIndex)
	css.useZIndexAmongLayers = true;
	// The zIndex difference range within which a pair of colliders are considered as candidates for collision
	css.zIndexCollisionRange = 2;
	return css;
}


#include "../AnimationSection.h"
std::vector<AnimationSection> getDieAnimationInfo()
{
	std::vector<AnimationSection> animationSections;
	animationSections.push_back(AnimationSection{ 0,  312, 3, 42, false, false });
	animationSections.push_back(AnimationSection{ 1,  250, 45, 63, false, false });
	animationSections.push_back(AnimationSection{ 1,   83, 63, 63, false, false });
	animationSections.push_back(AnimationSection{ 2,   83, 63, 63, false, false });
	animationSections.push_back(AnimationSection{ 2,  250, 63, 47, false, false });
	animationSections.push_back(AnimationSection{ 3,  200, 45, 0, false, true });
	animationSections.push_back(AnimationSection{ 3, 1000, 0, 0, true, true });
	animationSections.push_back(AnimationSection{ 4,  125, 0, 0, true, true });
	animationSections.push_back(AnimationSection{ 5,  125, 0, 0, true, true });
	animationSections.push_back(AnimationSection{ 6,  125, 0, 0, true, true });
	return animationSections;
}


#include "../MotionPattern.h"
#include "../MotionPatternPoint.h"
std::vector<MotionPattern> getMotionPatterns()
{
	std::vector<MotionPattern> motionPatterns;

	std::vector<MotionPatternPoint> points;
	points.reserve(16);
	// MP0
	points.clear();
	points.push_back(MotionPatternPoint(0, -0.5 * SCREEN_WIDTH, 80, 0.93f, 0, false, "fly", true));
	points.push_back(MotionPatternPoint(0.35f, 0, 80, 0.93f));
	points.push_back(MotionPatternPoint(0.5f, 0.5 * SCREEN_WIDTH, 80, 0.93f));
	points.push_back(MotionPatternPoint(0.75f, 0, 61, 0.8f));
	points.push_back(MotionPatternPoint(1, -0.5 * SCREEN_WIDTH, 42, 0.5f));
	motionPatterns.push_back(MotionPattern(points));

	// MP1
	points.clear();
	points.push_back(MotionPatternPoint(0, 0, 0, 1, 0, false, "fly", true));
	points.push_back(MotionPatternPoint(0.1f, 0, 10, 0.9f, 1, true, "", false));
	points.push_back(MotionPatternPoint(0.4f, 0, 40, 0.6f, 2, true, "", false));
	points.push_back(MotionPatternPoint(1, 0, 100, 0.05f));
	motionPatterns.push_back(MotionPattern(points));

	return motionPatterns;
}


#include "../EnemySpawnInfo.h"
std::vector<EnemySpawnInfo> getEnemiesSpawnInfo()
{
	std::vector<EnemySpawnInfo> info;

	// Wave 1
	info.push_back(EnemySpawnInfo("EnemyShipPrefab", 2000, 4000, 0, "assets/audio/sfx/SFX - Spawn_Ship.wav"));
	info.push_back(EnemySpawnInfo("EnemyShipPrefab", 2200, 4000, 0, "assets/audio/sfx/SFX - Spawn_Ship.wav"));
	info.push_back(EnemySpawnInfo("EnemyShipPrefab", 2400, 4000, 0, "assets/audio/sfx/SFX - Spawn_Ship.wav"));
	info.push_back(EnemySpawnInfo("EnemyShipPrefab", 2600, 4000, 0, "assets/audio/sfx/SFX - Spawn_Ship.wav"));
	info.push_back(EnemySpawnInfo("EnemyShipPrefab", 2800, 4000, 0, "assets/audio/sfx/SFX - Spawn_Ship.wav"));
	info.push_back(EnemySpawnInfo("EnemyShipPrefab", 3000, 4000, 0, "assets/audio/sfx/SFX - Spawn_Ship.wav"));
	
	info.push_back(EnemySpawnInfo("EnemyShipPrefab", 3000, 4000, 1, "assets/audio/sfx/SFX - Spawn_Ship.wav"));
	
	return info;
}


#include "../ObstacleSpawnInfo.h"
std::vector<ObstacleSpawnInfo> getObstaclesSpawnInfo()
{
	std::vector<ObstacleSpawnInfo> info;

	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 1733, -9.9f, 1, 0.05f));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 2003, 13.85f, 1, 0.05f));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 2272, 9.75f, 1, 0.05f));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 2538, -0.50f, 1, 0.05f));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 2867, 16.8f, 1, 0.05f));
	info.push_back(ObstacleSpawnInfo("RockPrefab", 2935, -9.85f, 1, 0.05f));
	info.push_back(ObstacleSpawnInfo("RockPrefab", 3005, -0.30f, 1, 0.05f));

	return info;
}

