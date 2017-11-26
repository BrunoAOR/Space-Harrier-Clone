#include "GameScene.h"

#include "Engine/API.h"
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Engine/Behaviour.h"
#include "Engine/Sprite.h"
#include "Engine/Vector2.h"
#include "Engine/gameConfig.h"

#include "FloorManager.h"
#include "TimeLogger.h"


bool GameScene::load()
{
	auto floor = GameObject::createNew();
	if (floor)
	{
		floor->addComponent<TimeLogger>();
		floor->transform->setLocalPosition(Vector2(SCREEN_WIDTH / 2.0f, 0));

		auto floorManager = floor->addComponent<FloorManager>();

		if (floorManager)
		{
			floorManager->texturePath = "assets/FloorGreen.png";
		}
	}

	return true;
}

void GameScene::unload()
{
}
