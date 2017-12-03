#ifndef H_GAME_CONFIG
#define H_GAME_CONFIG

#include <vector>
#include <string>
struct CollisionSystemSetup;


extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int SCREEN_SIZE;

bool scenesConfig();
bool prefabsConfig();
std::vector<std::string> renderLayersConfig();
CollisionSystemSetup collisionSystemSetup();


#endif // !H_GAME_CONFIG
