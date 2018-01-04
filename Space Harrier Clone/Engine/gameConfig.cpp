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
const int LIVES_PER_COIN = 3;
int player_lives = 3;


#include "../HomeScene.h"
#include "../GameScene.h"
bool scenesConfig()
{
	// Success flag
	bool success = true;

	success &= engine->sceneManager->addScene<HomeScene>();
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
#include "../EnemyShotPrefab.h"
#include "../EnemyShipPrefab.h"
#include "../EnemyBallPrefab.h"
#include "../Boss1ShotPrefab.h"
#include "../Boss1Prefab.h"
#include "../Boss1ChainLinkPrefab.h"
#include "../Boss1ExplosionPrefab.h"
#include "../SceneFaderPrefab.h"
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
	success &= engine->prefabsFactory->addPrefab<EnemyShotPrefab>("EnemyShotPrefab");
	success &= engine->prefabsFactory->addPrefab<EnemyShipPrefab>("EnemyShipPrefab");
	success &= engine->prefabsFactory->addPrefab<EnemyBallPrefab>("EnemyBallPrefab");
	success &= engine->prefabsFactory->addPrefab<Boss1ShotPrefab>("Boss1ShotPrefab");
	success &= engine->prefabsFactory->addPrefab<Boss1Prefab>("Boss1Prefab");
	success &= engine->prefabsFactory->addPrefab<Boss1ChainLinkPrefab>("Boss1ChainLinkPrefab");
	success &= engine->prefabsFactory->addPrefab<Boss1ExplosionPrefab>("Boss1ExplosionPrefab");
	success &= engine->prefabsFactory->addPrefab<SceneFaderPrefab>("SceneFaderPrefab");

	return success;
}


std::vector<std::string> renderLayersConfig()
{
	return std::vector<std::string>{"Background", "Shadows", "Main", "EnemyShots", "Foreground", "UI" };
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
	// MP0 (SHIP)
	points.clear();
	points.push_back(MotionPatternPoint(0, -0.5 * SCREEN_WIDTH, 80, 0.93f, 0, false, "fly", true, 6));
	points.push_back(MotionPatternPoint(0.35f, 0, 80, 0.93f));
	points.push_back(MotionPatternPoint(0.5f, 0.5 * SCREEN_WIDTH, 80, 0.93f));
	points.push_back(MotionPatternPoint(0.75f, 0, 61, 0.8f));
	points.push_back(MotionPatternPoint(1, -0.5 * SCREEN_WIDTH, 42, 0.5f));
	motionPatterns.push_back(MotionPattern(points));

	// MP1 (SHIP)
	points.clear();
	points.push_back(MotionPatternPoint(0, 0, 0, 1, 0, false, "fly", true, 6));
	points.push_back(MotionPatternPoint(0.1f, 50, 10, 0.9f, 1, true));
	points.push_back(MotionPatternPoint(0.4f, 50, 40, 0.6f, 2, true));
	points.push_back(MotionPatternPoint(1, 0, 100, 0.05f));
	motionPatterns.push_back(MotionPattern(points));

	// MP7 (BALL)
	points.clear();
	points.push_back(MotionPatternPoint(0, 0, 41, 1));
	points.push_back(MotionPatternPoint(0.10f, 0, 41, 0.5f));
	points.push_back(MotionPatternPoint(0.15f, 0, 79, 0.5f, 0, false, "open", false, 4));
	points.push_back(MotionPatternPoint(0.45f, 0, 79, 0.5f, 1, true));
	points.push_back(MotionPatternPoint(0.70f, 0, 41, 0.5f, 2, false, "close", false, 4));
	points.push_back(MotionPatternPoint(0.90f, 0, 41, 0.5f));
	points.push_back(MotionPatternPoint(1, 0, 41, 1));
	motionPatterns.push_back(MotionPattern(points));

	return motionPatterns;
}


#include "../EnemySpawnInfo.h"
std::vector<EnemySpawnInfo> getEnemiesSpawnInfo()
{
	std::vector<EnemySpawnInfo> info;

	// Wave 1
	/*
	info.push_back(EnemySpawnInfo("EnemyShipPrefab", 2000, 4000, 0, "assets/audio/sfx/SFX - Spawn_Ship.wav"));
	info.push_back(EnemySpawnInfo("EnemyShipPrefab", 2200, 4000, 0, "assets/audio/sfx/SFX - Spawn_Ship.wav"));
	info.push_back(EnemySpawnInfo("EnemyShipPrefab", 2400, 4000, 0, "assets/audio/sfx/SFX - Spawn_Ship.wav"));
	info.push_back(EnemySpawnInfo("EnemyShipPrefab", 2600, 4000, 0, "assets/audio/sfx/SFX - Spawn_Ship.wav"));
	info.push_back(EnemySpawnInfo("EnemyShipPrefab", 2800, 4000, 0, "assets/audio/sfx/SFX - Spawn_Ship.wav"));
	info.push_back(EnemySpawnInfo("EnemyShipPrefab", 3000, 4000, 0, "assets/audio/sfx/SFX - Spawn_Ship.wav"));
	*/
	info.push_back(EnemySpawnInfo("EnemyShipPrefab", 3000, 4000, 1, "assets/audio/sfx/SFX - Spawn_Ship.wav"));
	
	info.push_back(EnemySpawnInfo("EnemyBallPrefab", 3000, 6000, 2, "assets/audio/sfx/SFX - Spawn_Ball.wav"));
	
	info.push_back(EnemySpawnInfo("Boss1Prefab", 8000, -1, -1, ""));
	
	return info;
}


#include "../ObstacleSpawnInfo.h"
std::vector<ObstacleSpawnInfo> getObstaclesSpawnInfo()
{
	float normSpawnY = 1.0f;
	float normDespawnY = 0.05f;

	std::vector<ObstacleSpawnInfo> info;

	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 1750,  -9.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 2033,  14.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 2316,   9.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 2583,  -0.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab",	2866,  16.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("RockPrefab",		2950,  -9.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("RockPrefab",		3050,   0.20f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab",	3150,  -7.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("RockPrefab",		3150,   2.70f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("RockPrefab",		3233,   7.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("RockPrefab",		3350,   2.20f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab",	3416,   4.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("RockPrefab",		3450,   2.80f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("RockPrefab",		3550,  10.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("RockPrefab",		3650,  -1.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab",	3700, -12.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab",	3983,  12.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab",	4250,  -3.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab",	4533,   8.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab",	4816,  -6.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 5083,   1.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 5366,  14.80f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 5650,  -1.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 5916,   6.20f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 6200,  12.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 6483,  -7.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 6750,   4.00f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 7033,  12.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 7316,   0.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 7583,   8.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 7866,  -4.00f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 8150,   4.00f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 8416,  10.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("RockPrefab",		8500,   7.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("RockPrefab",		8600,  -4.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 8700,  -0.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 8983,  -7.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 9250,   1.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 9533,   5.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("RockPrefab",		9700,  -3.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("RockPrefab",		9800,   8.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 9816,   0.00f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("RockPrefab",		10000,  -6.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 10083,   3.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 10366,   1.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 10650,   8.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 10916,   6.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 11200,  13.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	11483,  16.80f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	11750,  10.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 12033,  16.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 12316,   7.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	12583,  13.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 12866,   7.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	13150,  11.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	13416,   7.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	13700,   4.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 13983,   8.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 14250,  -2.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 14533,   0.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	14816,   5.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 15083,  -6.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("RockPrefab",		15166,   3.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("RockPrefab",		15266,  -2.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("RockPrefab",		15366,  -6.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	15366,  -1.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("RockPrefab",		15466,  -5.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("RockPrefab",		15566,   3.00f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 15650,  10.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("RockPrefab",		15766,   3.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	15916,  -3.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 16200,   2.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("RockPrefab",		16366,   0.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 16483,   6.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	16750,  14.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("RockPrefab",		16966,  -3.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	17033,   2.00f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 17316,  11.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 17583,  -2.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	17866,   4.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 18150,  13.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	18416,   7.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	18700,   3.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 18983,  -2.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	19250, -18.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 19533,  -6.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	19816, -13.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	20083,   4.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	20366, -15.80f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 20650,  -1.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	20916, -11.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 21200,   2.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	21483,  -6.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 21750,   8.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	22033,  -9.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 22316,  -3.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	22583,  -1.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 22866,   3.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	23150,  -7.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 23416,  -0.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("RockPrefab",		23500,  -5.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("RockPrefab",		23600,  -7.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	23700,  -9.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("RockPrefab",		23700,   9.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 23983,  -5.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 24250,   0.00f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	24533,  -5.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 24816,   8.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	25083,  -1.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 25366,   2.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	25650,  -7.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 25916,  -1.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	26200,   0.00f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("RockPrefab",		26400,   7.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	26483,  -3.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("RockPrefab",		26500,  -3.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("RockPrefab",		26600,   6.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("RockPrefab",		26700,  -4.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 26750,   1.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("RockPrefab",		26800,  -2.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	27033,  -8.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 27316,   6.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	27583,  -6.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	27866,  -1.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	28150, -11.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 28416,   2.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	28700,  -0.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 28983,  -3.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("RockPrefab",		29166,  -0.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	29250,  -7.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("RockPrefab",		29266,   8.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("RockPrefab",		29366,   7.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("RockPrefab",		29466,   6.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 29533,   4.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("RockPrefab",		29566,   6.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	29816,  -4.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	30083, -14.80f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 30366,  -7.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	30650, -11.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	30916,   1.45f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	31200, -17.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		31483,  -4.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	31750, -11.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		32033,  15.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		32316,   3.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("RockPrefab",		32400,   2.50f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("RockPrefab",		32500,   0.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	32583, -14.80f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("RockPrefab",		32600,  -7.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("RockPrefab",		32700,   8.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("RockPrefab",		32800,   8.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		32866,   8.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		33150,  -8.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	33416,   8.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		33700, -13.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	33983,   3.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	34250, -15.80f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	34533, -14.80f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		34816,   8.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		35083,  -2.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	35366,  14.80f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		35650,  -8.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	35916,   4.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	36200,  12.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		36483, -11.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	36750,  -0.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		37033,  10.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		37316,  -9.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		37583,  14.80f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	37866, -13.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		38150,  13.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		38416,  -9.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	38700,  -7.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		38983,  -3.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	39233,   6.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		39250,  -0.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	39500,  10.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		39533,  -1.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	39766,  10.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	39816,  -3.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	40033,   4.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		40083,   9.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	40300,   5.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	40366,  -8.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		40650,  14.80f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	40916,   3.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	41200, -13.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		41483,  11.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	41750,  -1.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	42000,  -2.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		42033,   4.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	42266,   6.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		42316,  15.80f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		42583,   7.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	42866, -11.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		43166,  12.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	43433,   1.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		43716,   8.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		43983,   3.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	44250,  11.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		44533,   4.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	44783,  12.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		44816, -10.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	45050,  10.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		45083,  -6.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	45366,   1.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		45650,  11.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		45916,  -9.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	46200,   0.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	46483,  -2.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		46750,   9.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		47033,  16.80f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	47316,  12.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	47316,   4.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	47583,  -6.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		47583,  -7.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	47866,  -5.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		47866,   8.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	48150,  -8.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	48150,   0.00f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		48416,  -3.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		48700,  11.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		48983,  -5.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	49250,   5.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		49533,  -8.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	49816,   8.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	50083,  -8.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		50083,   6.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	50366,  -4.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		50366,  -1.45f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	50650,   2.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		50650,   6.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		50916,   0.00f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	51200,   3.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		51200,  -3.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	51483,   4.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		51750,  -7.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		52033,  12.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	52316,   7.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		52583, -12.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		52866,  14.80f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		53150,   9.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	53416, -10.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		53700,  17.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		53983, -14.80f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		54133,  -9.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	54250,  14.80f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	54400,  10.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		54533, -14.80f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		54683,   1.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		54816,  12.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("BigBushPrefab",	54966, -10.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		55083, -19.75f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		55233,  -0.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		55366,  19.75f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		56233,   0.00f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		56400,  12.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		56733,  -5.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("TreePrefab",		57066,  -5.40f, normSpawnY, normDespawnY));

	return info;
}


#include "Font.h"
#include "PixelPosition.h"
Font getFont(const std::string& fontName)
{
	Font font;

	if (fontName == "lifeIcons")
	{
		font.path = "assets/sprites/UI.png";
		font.characterWidth = 8;
		font.characterHeight = 16;
		font.charsTopLeftCorners['L'] = PixelPosition{ 0, 104 };
		font.charsTopLeftCorners['l'] = PixelPosition{ 0, 104 };
		font.charsTopLeftCorners['S'] = PixelPosition{ 8, 104 };
		font.charsTopLeftCorners['s'] = PixelPosition{ 8, 104 };
		return font;
	}

	bool foundSmall = false;
	bool foundBig = false;
	int widthFactor = 0;
	int heightOffset = 0;

	if (fontName.find("small") != std::string::npos)
	{
		font.path = "assets/sprites/UI.png";
		font.characterWidth = 8;
		font.characterHeight = 8;

		foundSmall = true;
		if (fontName == "smallGray")
		{
			heightOffset = 0;
		}
		else if (fontName == "smallPink")
		{
			heightOffset = 8;
		}
		else if (fontName == "smallRed")
		{
			heightOffset = 16;
		}
		else if (fontName == "smallGreen")
		{
			heightOffset = 24;
		}
		else if (fontName == "smallYellow")
		{
			heightOffset = 32;
		}
		else
		{
			foundSmall = false;
		}
	}
	else if (fontName.find("big") != std::string::npos)
	{
		font.path = "assets/sprites/UI.png";
		font.characterWidth = 16;
		font.characterHeight = 16;

		foundBig = true;
		if (fontName == "bigGray")
		{
			heightOffset = 40;
		}
		else if (fontName == "bigPink")
		{
			heightOffset = 72;
		}
		else
		{
			foundBig = false;
		}
	}

	if (foundSmall || foundBig)
	{
		font.charsTopLeftCorners['0'] = PixelPosition{ font.characterWidth * widthFactor++, heightOffset };
		font.charsTopLeftCorners['1'] = PixelPosition{ font.characterWidth * widthFactor++, heightOffset };
		font.charsTopLeftCorners['2'] = PixelPosition{ font.characterWidth * widthFactor++, heightOffset };
		font.charsTopLeftCorners['3'] = PixelPosition{ font.characterWidth * widthFactor++, heightOffset };
		font.charsTopLeftCorners['4'] = PixelPosition{ font.characterWidth * widthFactor++, heightOffset };
		font.charsTopLeftCorners['5'] = PixelPosition{ font.characterWidth * widthFactor++, heightOffset };
		font.charsTopLeftCorners['6'] = PixelPosition{ font.characterWidth * widthFactor++, heightOffset };
		font.charsTopLeftCorners['7'] = PixelPosition{ font.characterWidth * widthFactor++, heightOffset };
		font.charsTopLeftCorners['8'] = PixelPosition{ font.characterWidth * widthFactor++, heightOffset };
		font.charsTopLeftCorners['9'] = PixelPosition{ font.characterWidth * widthFactor++, heightOffset };
		if (foundSmall)
		{
			font.charsTopLeftCorners['.'] = PixelPosition{ font.characterWidth * widthFactor++, heightOffset };
			font.charsTopLeftCorners['!'] = PixelPosition{ font.characterWidth * widthFactor++, heightOffset };
			font.charsTopLeftCorners['?'] = PixelPosition{ font.characterWidth * widthFactor++, heightOffset };
		}
		font.charsTopLeftCorners['A'] = PixelPosition{ font.characterWidth * widthFactor++, heightOffset };
		font.charsTopLeftCorners['B'] = PixelPosition{ font.characterWidth * widthFactor++, heightOffset };
		font.charsTopLeftCorners['C'] = PixelPosition{ font.characterWidth * widthFactor++, heightOffset };
		font.charsTopLeftCorners['D'] = PixelPosition{ font.characterWidth * widthFactor++, heightOffset };
		font.charsTopLeftCorners['E'] = PixelPosition{ font.characterWidth * widthFactor++, heightOffset };
		font.charsTopLeftCorners['F'] = PixelPosition{ font.characterWidth * widthFactor++, heightOffset };
		font.charsTopLeftCorners['G'] = PixelPosition{ font.characterWidth * widthFactor++, heightOffset };
		font.charsTopLeftCorners['H'] = PixelPosition{ font.characterWidth * widthFactor++, heightOffset };
		if (foundBig)
		{
			widthFactor = 0;
			heightOffset += font.characterHeight;
		}
		font.charsTopLeftCorners['I'] = PixelPosition{ font.characterWidth * widthFactor++, heightOffset };
		font.charsTopLeftCorners['J'] = PixelPosition{ font.characterWidth * widthFactor++, heightOffset };
		font.charsTopLeftCorners['K'] = PixelPosition{ font.characterWidth * widthFactor++, heightOffset };
		font.charsTopLeftCorners['L'] = PixelPosition{ font.characterWidth * widthFactor++, heightOffset };
		font.charsTopLeftCorners['M'] = PixelPosition{ font.characterWidth * widthFactor++, heightOffset };
		font.charsTopLeftCorners['N'] = PixelPosition{ font.characterWidth * widthFactor++, heightOffset };
		font.charsTopLeftCorners['O'] = PixelPosition{ font.characterWidth * widthFactor++, heightOffset };
		font.charsTopLeftCorners['P'] = PixelPosition{ font.characterWidth * widthFactor++, heightOffset };
		font.charsTopLeftCorners['Q'] = PixelPosition{ font.characterWidth * widthFactor++, heightOffset };
		font.charsTopLeftCorners['R'] = PixelPosition{ font.characterWidth * widthFactor++, heightOffset };
		font.charsTopLeftCorners['S'] = PixelPosition{ font.characterWidth * widthFactor++, heightOffset };
		font.charsTopLeftCorners['T'] = PixelPosition{ font.characterWidth * widthFactor++, heightOffset };
		font.charsTopLeftCorners['U'] = PixelPosition{ font.characterWidth * widthFactor++, heightOffset };
		font.charsTopLeftCorners['V'] = PixelPosition{ font.characterWidth * widthFactor++, heightOffset };
		font.charsTopLeftCorners['W'] = PixelPosition{ font.characterWidth * widthFactor++, heightOffset };
		font.charsTopLeftCorners['X'] = PixelPosition{ font.characterWidth * widthFactor++, heightOffset };
		font.charsTopLeftCorners['Y'] = PixelPosition{ font.characterWidth * widthFactor++, heightOffset };
		font.charsTopLeftCorners['Z'] = PixelPosition{ font.characterWidth * widthFactor++, heightOffset };

		return font;
	}
	
	return Font();
}


#include "../Boss1ChainConfig.h"
Boss1ChainConfig getBoss1ChainConfig()
{
	Boss1ChainConfig b1cc;

	b1cc.chainLength = 9;
	b1cc.chainDelay = 100;
	b1cc.deathDelay = 300;

	// Position motion
	b1cc.minXAxisDistance = 0;
	b1cc.maxXAxisDistance = 200.0f;
	b1cc.maxXDifferencePerSecond = 200;
	b1cc.minYPos = 30.0f;
	b1cc.maxYPos = 200.0f;

	// Depth motion
	// Note: 0 progress means that the object is the furthest from the player (the player is at 0.95)
	b1cc.minNormalizedProgress = 0.3f;
	b1cc.maxNormalizedProgress = 0.9f;
	b1cc.depthCycleTimeMS = 8000;

	// Shooting
	b1cc.shotsSpreadDistance = 15;
	b1cc.normalizedCycleShootingTimes.push_back(0.13f);
	b1cc.normalizedCycleShootingTimes.push_back(0.14f);
	b1cc.normalizedCycleShootingTimes.push_back(0.15f);
	b1cc.normalizedCycleShootingTimes.push_back(0.16f);
	b1cc.normalizedCycleShootingTimes.push_back(0.17f);
	b1cc.normalizedCycleShootingTimes.push_back(0.18f);

	b1cc.normalizedCycleShootingTimes.push_back(0.33f);
	b1cc.normalizedCycleShootingTimes.push_back(0.34f);
	b1cc.normalizedCycleShootingTimes.push_back(0.35f);
	b1cc.normalizedCycleShootingTimes.push_back(0.36f);
	b1cc.normalizedCycleShootingTimes.push_back(0.37f);
	b1cc.normalizedCycleShootingTimes.push_back(0.38f);

	return b1cc;
}

