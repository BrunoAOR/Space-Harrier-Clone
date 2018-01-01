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
int initial_player_lives = 3;


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

	return success;
}


std::vector<std::string> renderLayersConfig()
{
	return std::vector<std::string>{"Background", "Shadows", "Main", "Foreground", "UI" };
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
	
	info.push_back(EnemySpawnInfo("EnemyShipPrefab", 2000, 4000, 0, "assets/audio/sfx/SFX - Spawn_Ship.wav"));
	info.push_back(EnemySpawnInfo("EnemyShipPrefab", 2200, 4000, 0, "assets/audio/sfx/SFX - Spawn_Ship.wav"));
	info.push_back(EnemySpawnInfo("EnemyShipPrefab", 2400, 4000, 0, "assets/audio/sfx/SFX - Spawn_Ship.wav"));
	info.push_back(EnemySpawnInfo("EnemyShipPrefab", 2600, 4000, 0, "assets/audio/sfx/SFX - Spawn_Ship.wav"));
	info.push_back(EnemySpawnInfo("EnemyShipPrefab", 2800, 4000, 0, "assets/audio/sfx/SFX - Spawn_Ship.wav"));
	info.push_back(EnemySpawnInfo("EnemyShipPrefab", 3000, 4000, 0, "assets/audio/sfx/SFX - Spawn_Ship.wav"));
	
	info.push_back(EnemySpawnInfo("EnemyShipPrefab", 3000, 4000, 1, "assets/audio/sfx/SFX - Spawn_Ship.wav"));
	
	info.push_back(EnemySpawnInfo("EnemyBallPrefab", 3000, 6000, 2, "assets/audio/sfx/SFX - Spawn_Ball.wav"));

	return info;
}


#include "../ObstacleSpawnInfo.h"
std::vector<ObstacleSpawnInfo> getObstaclesSpawnInfo()
{
	float normSpawnY = 1.0f;
	float normDespawnY = 0.05f;

	std::vector<ObstacleSpawnInfo> info;

	info.push_back(ObstacleSpawnInfo("TreePrefab", 500, 5.0f, normSpawnY, normDespawnY));

	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 1733, -9.9f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 2003, 13.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 2272, 9.75f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 2538, -0.50f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("SmallBushPrefab", 2867, 16.8f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("RockPrefab", 2935, -9.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo("RockPrefab", 3005, -0.30f, normSpawnY, normDespawnY));

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
		font.path = "../assets/sprites/UI.png";
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

