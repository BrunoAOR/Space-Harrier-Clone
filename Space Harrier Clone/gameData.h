#ifndef H_GAME_DATA
#define H_GAME_DATA

#include <vector>
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


std::vector<AnimationSection> getDieAnimationInfo();
std::vector<MotionPattern> getMotionPatterns();
std::vector<EnemySpawnInfo> getEnemiesSpawnInfo();
std::vector<ObstacleSpawnInfo> getObstaclesSpawnInfo();
Font getFont(const std::string& fontName);
Boss1ChainConfig getBoss1ChainConfig();


#endif // !H_GAME_DATA
