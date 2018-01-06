#include "gameConfig.h"

#include "Engine.h"
#include "SceneManager.h"
#include "PrefabsFactory.h"
#include "CollisionSystemSetup.h"


const std::string GAME_NAME = "Space Harrier Tribute (by Bruno Ortiz)";
const bool USE_VSYNC = true;
const int SCREEN_SIZE = 2;
const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 224;


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
