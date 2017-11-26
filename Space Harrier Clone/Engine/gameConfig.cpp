#include "gameConfig.h"

#include "Engine.h"
#include "SceneManager.h"


const int SCREEN_SIZE = 2;
const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 224 + 32 / SCREEN_SIZE;


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


std::vector<std::string> renderLayersConfig()
{
	return std::vector<std::string>{"Background", "Main", "Foreground" };
}