#ifndef H_GAME_CONFIG
#define H_GAME_CONFIG

#include <vector>
#include <string>
class MotionPattern;
struct AnimationSection;
struct CollisionSystemSetup;
struct EnemySpawnInfo;
struct ObstacleSpawnInfo;
struct Font;
struct Boss1ChainConfig;


extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int SCREEN_SIZE;

extern const int POST_DIE_BLINK_CYCLE_DURATION;
extern const int POST_DIE_BLINK_FLOOR_CYCLE_COUNT;
extern const int POST_DIE_BLINK_FREE_CYCLE_COUNT;
extern const int LIVES_PER_COIN;
extern int player_lives;


bool scenesConfig();
bool prefabsConfig();
std::vector<std::string> renderLayersConfig();
CollisionSystemSetup collisionSystemSetup();
std::vector<AnimationSection> getDieAnimationInfo();
std::vector<MotionPattern> getMotionPatterns();
std::vector<EnemySpawnInfo> getEnemiesSpawnInfo();
std::vector<ObstacleSpawnInfo> getObstaclesSpawnInfo();
Font getFont(const std::string& fontName);
Boss1ChainConfig getBoss1ChainConfig();


#endif // !H_GAME_CONFIG
