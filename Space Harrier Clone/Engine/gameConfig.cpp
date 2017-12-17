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

	return success;
}


std::vector<std::string> renderLayersConfig()
{
	return std::vector<std::string>{"Background", "Main", "Foreground" };
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
