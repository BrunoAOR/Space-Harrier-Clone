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


#include "../gameData.h"
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

	success &= engine->prefabsFactory->addPrefab<PlayerPrefab>(PLAYER_PREFAB);
	success &= engine->prefabsFactory->addPrefab<TreePrefab>(TREE_PREFAB);
	success &= engine->prefabsFactory->addPrefab<SmallBushPrefab>(SMALL_BUSH_PREFAB);
	success &= engine->prefabsFactory->addPrefab<BigBushPrefab>(BIG_BUSH_PREFAB);
	success &= engine->prefabsFactory->addPrefab<RockPrefab>(ROCK_PREFAB);
	success &= engine->prefabsFactory->addPrefab<PlayerShotPrefab>(PLAYER_SHOT_PREFAB);
	success &= engine->prefabsFactory->addPrefab<ExplosionPrefab>(EXPLOSION_PREFAB);
	success &= engine->prefabsFactory->addPrefab<EnemyShotPrefab>(ENEMY_SHOT_PREFAB);
	success &= engine->prefabsFactory->addPrefab<EnemyShipPrefab>(ENEMY_SHIP_PREFAB);
	success &= engine->prefabsFactory->addPrefab<EnemyBallPrefab>(ENEMY_BALL_PREFAB);
	success &= engine->prefabsFactory->addPrefab<Boss1ShotPrefab>(BOSS_1_SHOT_PREFAB);
	success &= engine->prefabsFactory->addPrefab<Boss1Prefab>(BOSS_1_PREFAB);
	success &= engine->prefabsFactory->addPrefab<Boss1ChainLinkPrefab>(BOSS_1_CHAIN_LINK_PREFAB);
	success &= engine->prefabsFactory->addPrefab<Boss1ExplosionPrefab>(BOSS_1_EXPLOSION_PREFAB);
	success &= engine->prefabsFactory->addPrefab<SceneFaderPrefab>(SCENE_FADER_PREFAB);

	return success;
}


std::vector<std::string> renderLayersConfig()
{
	return std::vector<std::string>{
		RENDER_LAYER_0_BACKGROUND,
			RENDER_LAYER_1_SHADOWS,
			RENDER_LAYER_2_MAIN,
			RENDER_LAYER_3_ENEMY_SHOTS,
			RENDER_LAYER_4_FOREGROUND,
			RENDER_LAYER_5_UI
	};
}


CollisionSystemSetup collisionSystemSetup()
{
	CollisionSystemSetup css;
	// The list of collisionLayers. There is always a "default" layer that collides with everything else
	css.layersNames = std::vector<std::string>{
		COLLISION_LAYER_0_PLAYER,
		COLLISION_LAYER_1_PLAYER_SHOT,
		COLLISION_LAYER_2_ENEMY,
		COLLISION_LAYER_3_ENEMY_SHOT,
		COLLISION_LAYER_4_OBSTACLE
	};
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
