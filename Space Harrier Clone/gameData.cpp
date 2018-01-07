#include "gameData.h"


const int POST_DIE_BLINK_CYCLE_DURATION = 150;
const int POST_DIE_BLINK_FLOOR_CYCLE_COUNT = 7;
const int POST_DIE_BLINK_FREE_CYCLE_COUNT = 15;
const int LIVES_PER_COIN = 3;
int player_lives = 3;

// Asset files
const std::string ASSET_BGM_MAIN = "assets/audio/bgm/Theme.ogg";
const std::string ASSET_BGM_BOSS = "assets/audio/bgm/S1 MOOT Boss (Skyra).ogg";
const std::string ASSET_BGM_WIN = "assets/audio/bgm/Lake Side Memory (WIN).ogg";
const std::string ASSET_BGM_RANKING = "assets/audio/bgm/Winners Song (Name Entry).ogg";

const std::string ASSET_SFX_BOSS_SHOT = "assets/audio/sfx/SFX - BossShot.wav";
const std::string ASSET_SFX_BULLET_BOUNCE = "assets/audio/sfx/SFX - Bullet_Bounce.wav";
const std::string ASSET_SFX_EXPLOSION = "assets/audio/sfx/SFX - Explosion.wav";
const std::string ASSET_SFX_SPAWN_SHIP = "assets/audio/sfx/SFX - Spawn_Ship.wav";
const std::string ASSET_SFX_SPAWN_BALL = "assets/audio/sfx/SFX - Spawn_Ball.wav";
const std::string ASSET_SFX_ENEMY_SHOT = "assets/audio/sfx/SFX - EnemyShot.wav";
const std::string ASSET_SFX_WELCOME = "assets/audio/sfx/SFX - Voice - Welcome to the fantasy zone.wav";
const std::string ASSET_SFX_COIN = "assets/audio/sfx/SFX - Coin.wav";
const std::string ASSET_SFX_PLAYER_TRIP = "assets/audio/sfx/SFX - Voice - Ouch.wav";
const std::string ASSET_SFX_PLAYER_DIE = "assets/audio/sfx/SFX - Voice - Aaaaargh.wav";
const std::string ASSET_SFX_PLAYER_REVIVE = "assets/audio/sfx/SFX - Voice - Get ready.wav";
const std::string ASSET_SFX_PLAYER_SHOT = "assets/audio/sfx/SFX - PlayerShot.wav";

const std::string ASSET_IMG_UI = "assets/sprites/UI.png";
const std::string ASSET_IMG_BOSS = "assets/sprites/Boss_lvl1.png";
const std::string ASSET_IMG_ENEMIES  = "assets/sprites/Enemies.png";
const std::string ASSET_IMG_CHARACTER = "assets/sprites/Character.png";
const std::string ASSET_IMG_OBSTACLES = "assets/sprites/Floor_objects.png";
const std::string ASSET_IMG_EXPLOSION = "assets/sprites/Explosion.png";
const std::string ASSET_IMG_HOME_SCREEN = "assets/sprites/Home_screen.png";
const std::string ASSET_IMG_FLOOR_GREEN = "assets/sprites/FloorGreen.png";
const std::string ASSET_IMG_BACKGROUND = "assets/sprites/Background_lvl1.png";
const std::string ASSET_IMG_BG_MOUNTAINS = "assets/sprites/Background_lvl1_mountains.png";
const std::string ASSET_IMG_BG_TREES= "assets/sprites/Background_lvl1_trees.png";

// Prefab names
const std::string PLAYER_PREFAB = "PlayerPrefab";
const std::string TREE_PREFAB = "TreePrefab";
const std::string SMALL_BUSH_PREFAB = "SmallBushPrefab";
const std::string BIG_BUSH_PREFAB = "BigBushPrefab";
const std::string ROCK_PREFAB = "RockPrefab";
const std::string PLAYER_SHOT_PREFAB = "PlayerShotPrefab";
const std::string EXPLOSION_PREFAB = "ExplosionPrefab";
const std::string ENEMY_SHOT_PREFAB = "EnemyShotPrefab";
const std::string ENEMY_SHIP_PREFAB = "EnemyShipPrefab";
const std::string ENEMY_BALL_PREFAB = "EnemyBallPrefab";
const std::string BOSS_1_SHOT_PREFAB = "Boss1ShotPrefab";
const std::string BOSS_1_PREFAB = "Boss1Prefab";
const std::string BOSS_1_CHAIN_LINK_PREFAB = "Boss1ChainLinkPrefab";
const std::string BOSS_1_EXPLOSION_PREFAB = "Boss1ExplosionPrefab";	
const std::string SCENE_FADER_PREFAB = "SceneFaderPrefab";

// Render Layers names
const std::string RENDER_LAYER_0_BACKGROUND = "Background";
const std::string RENDER_LAYER_1_SHADOWS = "Shadows";
const std::string RENDER_LAYER_2_MAIN = "Main";
const std::string RENDER_LAYER_3_ENEMY_SHOTS = "EnemyShots";
const std::string RENDER_LAYER_4_FOREGROUND = "Foreground";
const std::string RENDER_LAYER_5_UI = "UI";

// Collision Layers names
const std::string COLLISION_LAYER_0_PLAYER = "Player";
const std::string COLLISION_LAYER_1_PLAYER_SHOT = "PlayerShot";
const std::string COLLISION_LAYER_2_ENEMY = "Enemy";
const std::string COLLISION_LAYER_3_ENEMY_SHOT = "EnemyShot";
const std::string COLLISION_LAYER_4_OBSTACLE = "Obstacle";


#include "ScoreInfo.h"
std::vector<ScoreInfo> scoreInfos {
	ScoreInfo(1000000, "CAT"),
	ScoreInfo(900000, "PUC"),
	ScoreInfo(800000, "CIN"),
	ScoreInfo(700000, "O.S"),
	ScoreInfo(600000, "TUD"),
	ScoreInfo(500000, "IOS"),
	ScoreInfo(400000, "."),
	ScoreInfo(0, ""),
	ScoreInfo(0, ""),
	ScoreInfo(0, "")
};


#include "AnimationSection.h"
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


#include "MotionPattern.h"
#include "MotionPatternPoint.h"
std::vector<MotionPattern> getMotionPatterns()
{
	std::vector<MotionPattern> motionPatterns;

	std::vector<MotionPatternPoint> points;
	points.reserve(16);

	// MP0 (SHIP - Wave 1)
	points.clear();
	points.push_back(MotionPatternPoint(0, -155, 80, 0.93f, 0, false, "fly", true, 6));
	points.push_back(MotionPatternPoint(1066, -25, 80, 0.93f));
	points.push_back(MotionPatternPoint(2016, 172, 80, 0.93f));
	points.push_back(MotionPatternPoint(2816, 65, 73, 0.92f));
	points.push_back(MotionPatternPoint(3850, -175, 45, 0.53f));
	motionPatterns.push_back(MotionPattern(points));

	// MP1 (SHIP - Wave 2, Right)
	points.clear();
	points.push_back(MotionPatternPoint(0, 110, 12, 0.95f, 0, false, "fly", true, 6));
	points.push_back(MotionPatternPoint(416, 105, 12, 0.85f));
	points.push_back(MotionPatternPoint(483, 105, 17, 0.85f));
	points.push_back(MotionPatternPoint(733, 105, 0, 0.85f));
	points.push_back(MotionPatternPoint(1066, 105, 0, 0.85f));
	points.push_back(MotionPatternPoint(2983, 105, 110, 0.85f, 1, true));
	points.push_back(MotionPatternPoint(3550, 105, 0, 0.85f));
	points.push_back(MotionPatternPoint(3616, 105, 0, 0.85f));
	points.push_back(MotionPatternPoint(4533, 105, 33, 0.05f));
	motionPatterns.push_back(MotionPattern(points));

	// MP2 (SHIP - Wave 2, Center)
	points.clear();
	points.push_back(MotionPatternPoint(0, 0, 12, 0.95f, 0, false, "fly", true, 6));
	points.push_back(MotionPatternPoint(416, 0, 12, 0.85f));
	points.push_back(MotionPatternPoint(483, 0, 17, 0.85f));
	points.push_back(MotionPatternPoint(733, 0, 0, 0.85f));
	points.push_back(MotionPatternPoint(1066, 0, 0, 0.85f));
	points.push_back(MotionPatternPoint(2983, 0, 110, 0.85f, 1, true));
	points.push_back(MotionPatternPoint(3550, 0, 0, 0.85f));
	points.push_back(MotionPatternPoint(3616, 0, 0, 0.85f));
	points.push_back(MotionPatternPoint(4533, 0, 33, 0.05f));
	motionPatterns.push_back(MotionPattern(points));

	// MP3 (SHIP - Wave 2, Left)
	points.clear();
	points.push_back(MotionPatternPoint(0, -92, 12, 0.95f, 0, false, "fly", true, 6));
	points.push_back(MotionPatternPoint(416, -95, 12, 0.85f));
	points.push_back(MotionPatternPoint(483, -95, 17, 0.85f));
	points.push_back(MotionPatternPoint(733, -95, 0, 0.85f));
	points.push_back(MotionPatternPoint(1066, -95, 0, 0.85f));
	points.push_back(MotionPatternPoint(2983, -95, 110, 0.85f, 1, true));
	points.push_back(MotionPatternPoint(3550, -95, 0, 0.85f));
	points.push_back(MotionPatternPoint(3616, -95, 0, 0.85f));
	points.push_back(MotionPatternPoint(4533, -95, 33, 0.05f));
	motionPatterns.push_back(MotionPattern(points));

	// MP4 (SHIP - Wave 3, Start Left)
	points.clear();
	points.push_back(MotionPatternPoint(0, 170, 32, 0.55f, 0, false, "fly", true, 6));
	points.push_back(MotionPatternPoint(683, 0, 23, 0.82f));
	points.push_back(MotionPatternPoint(950, -47, 20, 0.87f, 1, true));
	points.push_back(MotionPatternPoint(1183, -85, 20, 0.9f));
	points.push_back(MotionPatternPoint(1300, -92, 20, 0.9f));
	points.push_back(MotionPatternPoint(1466, -110, 20, 0.92f));
	points.push_back(MotionPatternPoint(1583, -110, 20, 0.92f));
	points.push_back(MotionPatternPoint(1766, -120, 20, 0.94f));
	points.push_back(MotionPatternPoint(2266, -120, 20, 0.94f));
	points.push_back(MotionPatternPoint(3800, -35, 15, 0.97f));
	motionPatterns.push_back(MotionPattern(points));

	// MP5 (SHIP - Wave 3, Start Right)
	points.clear();
	points.push_back(MotionPatternPoint(0, -170, 32, 0.55f, 0, false, "fly", true, 6));
	points.push_back(MotionPatternPoint(683, 0, 23, 0.82f));
	points.push_back(MotionPatternPoint(950, 47, 20, 0.87f, 1, true));
	points.push_back(MotionPatternPoint(1183, 85, 20, 0.9f));
	points.push_back(MotionPatternPoint(1300, 92, 20, 0.9f));
	points.push_back(MotionPatternPoint(1466, 110, 20, 0.92f));
	points.push_back(MotionPatternPoint(1583, 110, 20, 0.92f));
	points.push_back(MotionPatternPoint(1766, 120, 20, 0.94f));
	points.push_back(MotionPatternPoint(2266, 120, 20, 0.94f));
	points.push_back(MotionPatternPoint(3800, 35, 15, 0.97f));
	motionPatterns.push_back(MotionPattern(points));

	// MP6 (BALL - Wave 4, up)
	points.clear();
	points.push_back(MotionPatternPoint(0, 0, 41, 1));
	points.push_back(MotionPatternPoint(1066, 0, 41, 0.95f));
	points.push_back(MotionPatternPoint(1583, 0, 41, 0.95f));
	points.push_back(MotionPatternPoint(1950, 0, 82, 0.92f, 0, false, "open", false, 10));
	points.push_back(MotionPatternPoint(2600, 0, 82, 0.87f));
	points.push_back(MotionPatternPoint(3116, 0, 82, 0.87f, 1, true));
	points.push_back(MotionPatternPoint(3366, 0, 82, 0.87f, 2, false, "close", false, 20));
	points.push_back(MotionPatternPoint(4033, 0, 82, 0.87f, 3, false, "open", false, 10));
	points.push_back(MotionPatternPoint(4766, 0, 82, 0.78f));
	points.push_back(MotionPatternPoint(5450, 0, 82, 0.78f, 4, true));
	points.push_back(MotionPatternPoint(5633, 0, 82, 0.78f, 5, false, "close", false, 20));
	points.push_back(MotionPatternPoint(6266, 0, 82, 0.78f, 6, false, "open", false, 10));
	points.push_back(MotionPatternPoint(6916, 0, 82, 0.65f));
	points.push_back(MotionPatternPoint(7783, 0, 82, 0.65f, 7, true));
	points.push_back(MotionPatternPoint(7833, 0, 82, 0.65f, 8, false, "close", false, 20));
	points.push_back(MotionPatternPoint(8216, 0, 82, 0.65f));
	points.push_back(MotionPatternPoint(8683, 0, 42, 0.77f));
	points.push_back(MotionPatternPoint(9666, 0, 42, 1));
	motionPatterns.push_back(MotionPattern(points));

	// MP7 (BALL - Wave 4, left-down)
	points.clear();
	points.push_back(MotionPatternPoint(0, 0, 41, 1));
	points.push_back(MotionPatternPoint(1066, 0, 41, 0.95f));
	points.push_back(MotionPatternPoint(1583, 0, 41, 0.95f));
	points.push_back(MotionPatternPoint(1950, -60, 12, 0.92f, 0, false, "open", false, 10));
	points.push_back(MotionPatternPoint(2600, -60, 12, 0.87f));
	points.push_back(MotionPatternPoint(3233, -60, 12, 0.87f, 1, true));
	points.push_back(MotionPatternPoint(3366, -60, 12, 0.87f, 2, false, "close", false, 20));
	points.push_back(MotionPatternPoint(4033, -60, 12, 0.87f, 3, false, "open", false, 10));
	points.push_back(MotionPatternPoint(4766, -60, 12, 0.78f));
	points.push_back(MotionPatternPoint(5566, -60, 12, 0.78f, 4, true));
	points.push_back(MotionPatternPoint(5633, -60, 12, 0.78f, 5, false, "close", false, 20));
	points.push_back(MotionPatternPoint(6266, -60, 12, 0.78f, 6, false, "open", false, 10));
	points.push_back(MotionPatternPoint(6916, -60, 12, 0.65f));
	points.push_back(MotionPatternPoint(7550, -60, 12, 0.65f, 7, true));
	points.push_back(MotionPatternPoint(7833, -60, 12, 0.65f, 8, false, "close", false, 20));
	points.push_back(MotionPatternPoint(8216, -60, 82, 0.65f));
	points.push_back(MotionPatternPoint(8683, 0, 42, 0.77f));
	points.push_back(MotionPatternPoint(9666, 0, 42, 1));
	motionPatterns.push_back(MotionPattern(points));

	// MP8 (BALL - Wave 4, right-down)
	points.clear();
	points.push_back(MotionPatternPoint(0, 0, 41, 1));
	points.push_back(MotionPatternPoint(1066, 0, 41, 0.95f));
	points.push_back(MotionPatternPoint(1583, 0, 41, 0.95f));
	points.push_back(MotionPatternPoint(1950, 60, 12, 0.92f, 0, false, "open", false, 10));
	points.push_back(MotionPatternPoint(2600, 60, 12, 0.87f));
	points.push_back(MotionPatternPoint(3350, 60, 12, 0.87f, 1, true));
	points.push_back(MotionPatternPoint(3366, 60, 12, 0.87f, 2, false, "close", false, 20));
	points.push_back(MotionPatternPoint(4033, 60, 12, 0.87f, 3, false, "open", false, 10));
	points.push_back(MotionPatternPoint(4766, 60, 12, 0.78f));
	points.push_back(MotionPatternPoint(5333, 60, 12, 0.78f, 4, true));
	points.push_back(MotionPatternPoint(5633, 60, 12, 0.78f, 5, false, "close", false, 20));
	points.push_back(MotionPatternPoint(6266, 60, 12, 0.78f, 6, false, "open", false, 10));
	points.push_back(MotionPatternPoint(6916, 60, 12, 0.65f));
	points.push_back(MotionPatternPoint(7666, 60, 12, 0.65f, 7, true));
	points.push_back(MotionPatternPoint(7833, 60, 12, 0.65f, 8, false, "close", false, 20));
	points.push_back(MotionPatternPoint(8216, 60, 82, 0.65f));
	points.push_back(MotionPatternPoint(8683, 0, 42, 0.77f));
	points.push_back(MotionPatternPoint(9666, 0, 42, 1));
	motionPatterns.push_back(MotionPattern(points));

	// MP9 (SHIP - Wave 5)
	points.clear();
	points.push_back(MotionPatternPoint(0, -166, 44, 0.55f, 0, false, "fly", true, 6));
	points.push_back(MotionPatternPoint(633, -4, 62, 0.85f));
	points.push_back(MotionPatternPoint(733, 4, 67, 0.88f));
	points.push_back(MotionPatternPoint(1583, -103, 90, 0.97f));
	points.push_back(MotionPatternPoint(1816, -111, 90, 0.92f));
	points.push_back(MotionPatternPoint(2883, 50, 90, 0.05f));
	motionPatterns.push_back(MotionPattern(points));

	// MP10 (SHIP - Wave 6, Start right)
	points.clear();
	points.push_back(MotionPatternPoint(0, 172, 62, 0.53f, 0, false, "fly", true, 6));
	points.push_back(MotionPatternPoint(133, 112, 62, 0.66f));
	points.push_back(MotionPatternPoint(383, 51, 56, 0.75f));
	points.push_back(MotionPatternPoint(816, -105, 42, 0.88f));
	points.push_back(MotionPatternPoint(1183, -120, 31, 0.92f));
	points.push_back(MotionPatternPoint(1600, -81, 23, 0.95f));
	points.push_back(MotionPatternPoint(2050, 0, 20, 0.95f));
	points.push_back(MotionPatternPoint(2400, 57, 35, 0.93f, 1, true));
	points.push_back(MotionPatternPoint(2833, 130, 58, 0.78f));
	points.push_back(MotionPatternPoint(3183, 182, 85, 0.5f));
	motionPatterns.push_back(MotionPattern(points));

	// MP11 (SHIP - Wave 6, Start left)
	points.clear();
	points.push_back(MotionPatternPoint(0, -172, 62, 0.53f, 0, false, "fly", true, 6));
	points.push_back(MotionPatternPoint(133, -112, 62, 0.66f));
	points.push_back(MotionPatternPoint(383, -51, 56, 0.75f));
	points.push_back(MotionPatternPoint(816, 105, 42, 0.88f));
	points.push_back(MotionPatternPoint(1183, 120, 31, 0.92f));
	points.push_back(MotionPatternPoint(1600, 81, 23, 0.95f));
	points.push_back(MotionPatternPoint(2050, 0, 20, 0.95f));
	points.push_back(MotionPatternPoint(2400, -57, 35, 0.93f, 1, true));
	points.push_back(MotionPatternPoint(2833, -130, 58, 0.78f));
	points.push_back(MotionPatternPoint(3183, -182, 85, 0.5f));
	motionPatterns.push_back(MotionPattern(points));

	return motionPatterns;
}


#include "EnemySpawnInfo.h"
std::vector<EnemySpawnInfo> getEnemiesSpawnInfo()
{
	std::vector<EnemySpawnInfo> info;

	// Wave 1
	info.push_back(EnemySpawnInfo(ENEMY_SHIP_PREFAB, 5716, 0, ASSET_SFX_SPAWN_SHIP));
	info.push_back(EnemySpawnInfo(ENEMY_SHIP_PREFAB, 5850, 0, ASSET_SFX_SPAWN_SHIP));
	info.push_back(EnemySpawnInfo(ENEMY_SHIP_PREFAB, 5983, 0, ASSET_SFX_SPAWN_SHIP));
	info.push_back(EnemySpawnInfo(ENEMY_SHIP_PREFAB, 6116, 0, ASSET_SFX_SPAWN_SHIP));
	info.push_back(EnemySpawnInfo(ENEMY_SHIP_PREFAB, 6250, 0, ASSET_SFX_SPAWN_SHIP));
	info.push_back(EnemySpawnInfo(ENEMY_SHIP_PREFAB, 6383, 0, ASSET_SFX_SPAWN_SHIP));

	// Wave 2
	info.push_back(EnemySpawnInfo(ENEMY_SHIP_PREFAB, 11150, 1, ASSET_SFX_SPAWN_SHIP));
	info.push_back(EnemySpawnInfo(ENEMY_SHIP_PREFAB, 11700, 2, ASSET_SFX_SPAWN_SHIP));
	info.push_back(EnemySpawnInfo(ENEMY_SHIP_PREFAB, 12250, 3, ASSET_SFX_SPAWN_SHIP));

	// Wave 3
	info.push_back(EnemySpawnInfo(ENEMY_SHIP_PREFAB, 18133, 4, ASSET_SFX_SPAWN_SHIP));
	info.push_back(EnemySpawnInfo(ENEMY_SHIP_PREFAB, 18466, 4, ASSET_SFX_SPAWN_SHIP));
	info.push_back(EnemySpawnInfo(ENEMY_SHIP_PREFAB, 18800, 4, ASSET_SFX_SPAWN_SHIP));
	info.push_back(EnemySpawnInfo(ENEMY_SHIP_PREFAB, 19133, 4, ASSET_SFX_SPAWN_SHIP));
	info.push_back(EnemySpawnInfo(ENEMY_SHIP_PREFAB, 19800, 5, ASSET_SFX_SPAWN_SHIP));
	info.push_back(EnemySpawnInfo(ENEMY_SHIP_PREFAB, 20133, 5, ASSET_SFX_SPAWN_SHIP));
	info.push_back(EnemySpawnInfo(ENEMY_SHIP_PREFAB, 20466, 5, ASSET_SFX_SPAWN_SHIP));
	info.push_back(EnemySpawnInfo(ENEMY_SHIP_PREFAB, 20800, 5, ASSET_SFX_SPAWN_SHIP));

	// Wave 4
	info.push_back(EnemySpawnInfo(ENEMY_BALL_PREFAB, 26300, 6, ASSET_SFX_SPAWN_BALL));
	info.push_back(EnemySpawnInfo(ENEMY_BALL_PREFAB, 26316, 7, ASSET_SFX_SPAWN_BALL));
	info.push_back(EnemySpawnInfo(ENEMY_BALL_PREFAB, 26333, 8, ASSET_SFX_SPAWN_BALL));

	// Wave 5
	info.push_back(EnemySpawnInfo(ENEMY_SHIP_PREFAB, 35350, 9, ASSET_SFX_SPAWN_SHIP));
	info.push_back(EnemySpawnInfo(ENEMY_SHIP_PREFAB, 35683, 9, ASSET_SFX_SPAWN_SHIP));
	info.push_back(EnemySpawnInfo(ENEMY_SHIP_PREFAB, 36016, 9, ASSET_SFX_SPAWN_SHIP));
	info.push_back(EnemySpawnInfo(ENEMY_SHIP_PREFAB, 36350, 9, ASSET_SFX_SPAWN_SHIP));

	// Wave 6
	info.push_back(EnemySpawnInfo(ENEMY_SHIP_PREFAB, 42266, 10, ASSET_SFX_SPAWN_SHIP));
	info.push_back(EnemySpawnInfo(ENEMY_SHIP_PREFAB, 42366, 11, ASSET_SFX_SPAWN_SHIP));
	info.push_back(EnemySpawnInfo(ENEMY_SHIP_PREFAB, 42366, 10, ASSET_SFX_SPAWN_SHIP));
	info.push_back(EnemySpawnInfo(ENEMY_SHIP_PREFAB, 42433, 11, ASSET_SFX_SPAWN_SHIP));
	info.push_back(EnemySpawnInfo(ENEMY_SHIP_PREFAB, 42483, 10, ASSET_SFX_SPAWN_SHIP));
	info.push_back(EnemySpawnInfo(ENEMY_SHIP_PREFAB, 42533, 11, ASSET_SFX_SPAWN_SHIP));

	// Wave 7
	info.push_back(EnemySpawnInfo(ENEMY_BALL_PREFAB, 48516, 6, ASSET_SFX_SPAWN_BALL));
	info.push_back(EnemySpawnInfo(ENEMY_BALL_PREFAB, 48533, 7, ASSET_SFX_SPAWN_BALL));
	info.push_back(EnemySpawnInfo(ENEMY_BALL_PREFAB, 48550, 8, ASSET_SFX_SPAWN_BALL));

	// Boss
	info.push_back(EnemySpawnInfo(BOSS_1_PREFAB, 58516, -1, ""));
	
	return info;
}


#include "ObstacleSpawnInfo.h"
std::vector<ObstacleSpawnInfo> getObstaclesSpawnInfo()
{
	float normSpawnY = 1.0f;
	float normDespawnY = 0.05f;

	std::vector<ObstacleSpawnInfo> info;

	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 1750, -9.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 2033, 14.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 2316, 9.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 2583, -0.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 2866, 16.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(ROCK_PREFAB, 2950, -9.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(ROCK_PREFAB, 3050, 0.20f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 3150, -7.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(ROCK_PREFAB, 3150, 2.70f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(ROCK_PREFAB, 3233, 7.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(ROCK_PREFAB, 3350, 2.20f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 3416, 4.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(ROCK_PREFAB, 3450, 2.80f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(ROCK_PREFAB, 3550, 10.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(ROCK_PREFAB, 3650, -1.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 3700, -12.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 3983, 12.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 4250, -3.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 4533, 8.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 4816, -6.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 5083, 1.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 5366, 14.80f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 5650, -1.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 5916, 6.20f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 6200, 12.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 6483, -7.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 6750, 4.00f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 7033, 12.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 7316, 0.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 7583, 8.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 7866, -4.00f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 8150, 4.00f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 8416, 10.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(ROCK_PREFAB, 8500, 7.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(ROCK_PREFAB, 8600, -4.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 8700, -0.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 8983, -7.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 9250, 1.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 9533, 5.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(ROCK_PREFAB, 9700, -3.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(ROCK_PREFAB, 9800, 8.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 9816, 0.00f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(ROCK_PREFAB, 10000, -6.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 10083, 3.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 10366, 1.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 10650, 8.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 10916, 6.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 11200, 13.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 11483, 16.80f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 11750, 10.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 12033, 16.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 12316, 7.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 12583, 13.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 12866, 7.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 13150, 11.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 13416, 7.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 13700, 4.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 13983, 8.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 14250, -2.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 14533, 0.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 14816, 5.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 15083, -6.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(ROCK_PREFAB, 15166, 3.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(ROCK_PREFAB, 15266, -2.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(ROCK_PREFAB, 15366, -6.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 15366, -1.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(ROCK_PREFAB, 15466, -5.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(ROCK_PREFAB, 15566, 3.00f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 15650, 10.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(ROCK_PREFAB, 15766, 3.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 15916, -3.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 16200, 2.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(ROCK_PREFAB, 16366, 0.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 16483, 6.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 16750, 14.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(ROCK_PREFAB, 16966, -3.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 17033, 2.00f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 17316, 11.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 17583, -2.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 17866, 4.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 18150, 13.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 18416, 7.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 18700, 3.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 18983, -2.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 19250, -18.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 19533, -6.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 19816, -13.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 20083, 4.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 20366, -15.80f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 20650, -1.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 20916, -11.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 21200, 2.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 21483, -6.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 21750, 8.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 22033, -9.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 22316, -3.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 22583, -1.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 22866, 3.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 23150, -7.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 23416, -0.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(ROCK_PREFAB, 23500, -5.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(ROCK_PREFAB, 23600, -7.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 23700, -9.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(ROCK_PREFAB, 23700, 9.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 23983, -5.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 24250, 0.00f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 24533, -5.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 24816, 8.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 25083, -1.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 25366, 2.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 25650, -7.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 25916, -1.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 26200, 0.00f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(ROCK_PREFAB, 26400, 7.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 26483, -3.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(ROCK_PREFAB, 26500, -3.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(ROCK_PREFAB, 26600, 6.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(ROCK_PREFAB, 26700, -4.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 26750, 1.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(ROCK_PREFAB, 26800, -2.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 27033, -8.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 27316, 6.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 27583, -6.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 27866, -1.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 28150, -11.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 28416, 2.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 28700, -0.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 28983, -3.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(ROCK_PREFAB, 29166, -0.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 29250, -7.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(ROCK_PREFAB, 29266, 8.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(ROCK_PREFAB, 29366, 7.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(ROCK_PREFAB, 29466, 6.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 29533, 4.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(ROCK_PREFAB, 29566, 6.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 29816, -4.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 30083, -14.80f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(SMALL_BUSH_PREFAB, 30366, -7.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 30650, -11.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 30916, 1.45f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 31200, -17.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 31483, -4.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 31750, -11.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 32033, 15.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 32316, 3.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(ROCK_PREFAB, 32400, 2.50f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(ROCK_PREFAB, 32500, 0.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 32583, -14.80f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(ROCK_PREFAB, 32600, -7.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(ROCK_PREFAB, 32700, 8.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(ROCK_PREFAB, 32800, 8.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 32866, 8.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 33150, -8.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 33416, 8.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 33700, -13.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 33983, 3.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 34250, -15.80f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 34533, -14.80f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 34816, 8.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 35083, -2.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 35366, 14.80f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 35650, -8.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 35916, 4.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 36200, 12.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 36483, -11.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 36750, -0.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 37033, 10.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 37316, -9.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 37583, 14.80f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 37866, -13.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 38150, 13.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 38416, -9.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 38700, -7.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 38983, -3.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 39233, 6.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 39250, -0.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 39500, 10.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 39533, -1.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 39766, 10.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 39816, -3.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 40033, 4.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 40083, 9.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 40300, 5.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 40366, -8.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 40650, 14.80f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 40916, 3.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 41200, -13.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 41483, 11.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 41750, -1.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 42000, -2.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 42033, 4.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 42266, 6.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 42316, 15.80f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 42583, 7.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 42866, -11.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 43166, 12.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 43433, 1.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 43716, 8.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 43983, 3.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 44250, 11.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 44533, 4.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 44783, 12.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 44816, -10.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 45050, 10.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 45083, -6.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 45366, 1.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 45650, 11.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 45916, -9.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 46200, 0.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 46483, -2.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 46750, 9.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 47033, 16.80f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 47316, 12.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 47316, 4.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 47583, -6.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 47583, -7.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 47866, -5.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 47866, 8.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 48150, -8.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 48150, 0.00f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 48416, -3.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 48700, 11.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 48983, -5.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 49250, 5.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 49533, -8.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 49816, 8.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 50083, -8.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 50083, 6.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 50366, -4.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 50366, -1.45f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 50650, 2.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 50650, 6.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 50916, 0.00f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 51200, 3.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 51200, -3.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 51483, 4.40f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 51750, -7.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 52033, 12.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 52316, 7.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 52583, -12.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 52866, 14.80f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 53150, 9.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 53416, -10.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 53700, 17.30f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 53983, -14.80f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 54133, -9.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 54250, 14.80f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 54400, 10.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 54533, -14.80f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 54683, 1.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 54816, 12.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(BIG_BUSH_PREFAB, 54966, -10.35f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 55083, -19.75f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 55233, -0.95f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 55366, 19.75f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 56233, 0.00f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 56400, 12.85f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 56733, -5.90f, normSpawnY, normDespawnY));
	info.push_back(ObstacleSpawnInfo(TREE_PREFAB, 57066, -5.40f, normSpawnY, normDespawnY));

	return info;
}


#include "Engine/Font.h"
#include "Engine/PixelPosition.h"
Font getFont(const std::string& fontName)
{
	Font font;

	if (fontName == "lifeIcons")
	{
		font.path = ASSET_IMG_UI;
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
		font.path = ASSET_IMG_UI;
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
		font.path = ASSET_IMG_UI;
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
		if (foundSmall)
		{
			font.charsTopLeftCorners['<'] = PixelPosition{ font.characterWidth * widthFactor++, heightOffset };
			font.charsTopLeftCorners['>'] = PixelPosition{ font.characterWidth * widthFactor++, heightOffset };
		}

		return font;
	}

	return Font();
}


#include "Boss1ChainConfig.h"
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
