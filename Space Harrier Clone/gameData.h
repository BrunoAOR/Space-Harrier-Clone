#ifndef H_GAME_DATA
#define H_GAME_DATA

#include <vector>
#include <string>
#include "Engine/gameConfig.h"
class MotionPattern;
struct ScoreInfo;
struct AnimationSection;
struct EnemySpawnInfo;
struct ObstacleSpawnInfo;
struct Font;
struct Boss1ChainConfig;


extern const int POST_DIE_BLINK_CYCLE_DURATION;
extern const int POST_DIE_BLINK_FLOOR_CYCLE_COUNT;
extern const int POST_DIE_BLINK_FREE_CYCLE_COUNT;
extern const int LIVES_PER_COIN;
extern int player_lives;
extern std::vector<ScoreInfo> scoreInfos;

// Asset files
extern const std::string ASSET_BGM_MAIN;
extern const std::string ASSET_BGM_BOSS;
extern const std::string ASSET_BGM_WIN;
extern const std::string ASSET_BGM_RANKING;

extern const std::string ASSET_SFX_BOSS_SHOT;
extern const std::string ASSET_SFX_BULLET_BOUNCE;
extern const std::string ASSET_SFX_EXPLOSION;
extern const std::string ASSET_SFX_SPAWN_SHIP;
extern const std::string ASSET_SFX_SPAWN_BALL;
extern const std::string ASSET_SFX_ENEMY_SHOT;
extern const std::string ASSET_SFX_WELCOME;
extern const std::string ASSET_SFX_COIN;
extern const std::string ASSET_SFX_PLAYER_TRIP;
extern const std::string ASSET_SFX_PLAYER_DIE;
extern const std::string ASSET_SFX_PLAYER_REVIVE;
extern const std::string ASSET_SFX_PLAYER_SHOT;

extern const std::string ASSET_IMG_UI;
extern const std::string ASSET_IMG_BOSS;
extern const std::string ASSET_IMG_ENEMIES;
extern const std::string ASSET_IMG_CHARACTER;
extern const std::string ASSET_IMG_OBSTACLES;
extern const std::string ASSET_IMG_EXPLOSION;
extern const std::string ASSET_IMG_HOME_SCREEN;
extern const std::string ASSET_IMG_FLOOR_GREEN;
extern const std::string ASSET_IMG_BACKGROUND;
extern const std::string ASSET_IMG_BG_MOUNTAINS;
extern const std::string ASSET_IMG_BG_TREES;

// Prefab names
extern const std::string PLAYER_PREFAB;
extern const std::string TREE_PREFAB;
extern const std::string SMALL_BUSH_PREFAB;
extern const std::string BIG_BUSH_PREFAB;
extern const std::string ROCK_PREFAB;
extern const std::string PLAYER_SHOT_PREFAB;
extern const std::string EXPLOSION_PREFAB;
extern const std::string ENEMY_SHOT_PREFAB;
extern const std::string ENEMY_SHIP_PREFAB;
extern const std::string ENEMY_BALL_PREFAB;
extern const std::string BOSS_1_SHOT_PREFAB;
extern const std::string BOSS_1_PREFAB;
extern const std::string BOSS_1_CHAIN_LINK_PREFAB;
extern const std::string BOSS_1_EXPLOSION_PREFAB;
extern const std::string SCENE_FADER_PREFAB;

// Render Layers names
extern const std::string RENDER_LAYER_0_BACKGROUND;
extern const std::string RENDER_LAYER_1_SHADOWS;
extern const std::string RENDER_LAYER_2_MAIN;
extern const std::string RENDER_LAYER_3_ENEMY_SHOTS;
extern const std::string RENDER_LAYER_4_FOREGROUND;
extern const std::string RENDER_LAYER_5_UI;

// Collision Layers names
extern const std::string COLLISION_LAYER_0_PLAYER;
extern const std::string COLLISION_LAYER_1_PLAYER_SHOT;
extern const std::string COLLISION_LAYER_2_ENEMY;
extern const std::string COLLISION_LAYER_3_ENEMY_SHOT;
extern const std::string COLLISION_LAYER_4_OBSTACLE;


std::vector<AnimationSection> getDieAnimationInfo();
std::vector<MotionPattern> getMotionPatterns();
std::vector<EnemySpawnInfo> getEnemiesSpawnInfo();
std::vector<ObstacleSpawnInfo> getObstaclesSpawnInfo();
Font getFont(const std::string& fontName);
Boss1ChainConfig getBoss1ChainConfig();


#endif // !H_GAME_DATA
