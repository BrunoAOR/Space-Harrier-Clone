#include "GameScene.h"

#include "Engine/API.h"
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Engine/Behaviour.h"
#include "Engine/Sprite.h"
#include "Engine/Vector2.h"
#include "Engine/gameConfig.h"

#include "FloorManager.h"
#include "FloorObjectsFactory.h"
#include "TreePrefab.h"
#include "TimeLogger.h"


bool GameScene::load()
{
	auto floorManagerGo = GameObject::createNew();
	if (floorManagerGo)
	{
		//floorManagerGo->addComponent<TimeLogger>();
		floorManagerGo->transform->setLocalPosition(Vector2(SCREEN_WIDTH / 2.0f, 0));

		auto floorManager = floorManagerGo->addComponent<FloorManager>();

		if (floorManager)
		{
			floorManager->texturePath = "assets/FloorGreen.png";
		}

		auto objectsFactoryGo = GameObject::createNew();
		if (objectsFactoryGo)
		{
			objectsFactoryGo->transform->setLocalPosition(Vector2(SCREEN_WIDTH / 2.0f, 0));
			auto floorObjectsFactory = objectsFactoryGo->addComponent<FloorObjectsFactory>();
			if (floorObjectsFactory)
			{
				floorObjectsFactory->floorManager = floorManager;
			}
		}
	}

	

	return true;
}

void GameScene::unload()
{
}
