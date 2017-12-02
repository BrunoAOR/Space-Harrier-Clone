#include "GameScene.h"

#include "Engine/API.h"
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Engine/Behaviour.h"
#include "Engine/Sprite.h"
#include "Engine/Vector2.h"
#include "Engine/gameConfig.h"
#include "Engine/PrefabsFactory.h"

#include "FloorManager.h"
#include "FloorObjectsFactory.h"
#include "PlayerPrefab.h"
#include "BackgroundScroller.h"
#include "TimeLogger.h"


bool GameScene::load()
{
	auto worldGO = GameObject::createNew();
	if (worldGO)
	{
		worldGO->transform->setWorldPosition(Vector2(SCREEN_WIDTH / 2.0f, 0));
		worldGO->addComponent<TimeLogger>();

		auto floorManagerGo = GameObject::createNew();
		if (floorManagerGo)
		{
			floorManagerGo->transform->setParent(worldGO->transform, false);

			auto floorManager = floorManagerGo->addComponent<FloorManager>();

			if (floorManager)
			{
				floorManager->texturePath = "assets/FloorGreen.png";
			}

			auto objectsFactoryGo = GameObject::createNew();
			if (objectsFactoryGo)
			{
				objectsFactoryGo->transform->setParent(worldGO->transform, false);
				auto floorObjectsFactory = objectsFactoryGo->addComponent<FloorObjectsFactory>();
				if (floorObjectsFactory)
				{
					floorObjectsFactory->floorManager = floorManager;
				}
			}

			// True background
			auto backgroundScrollerGo = GameObject::createNew();
			if (backgroundScrollerGo)
			{
				auto backgroundScroller = backgroundScrollerGo->addComponent<BackgroundScroller>();
				if (backgroundScroller)
				{
					backgroundScroller->init(floorManager, "assets/Background.png", 0.2f, -3);
				}
			}

			// Mountains
			auto backgroundScrollerGoMountains = GameObject::createNew();
			if (backgroundScrollerGoMountains)
			{
				auto backgroundScroller = backgroundScrollerGoMountains->addComponent<BackgroundScroller>();
				if (backgroundScroller)
				{
					backgroundScroller->init(floorManager, "assets/Background_lvl1_mountains.png", 0.3f, -2);
				}
			}

			// Grass
			auto backgroundScrollerGoTrees = GameObject::createNew();
			if (backgroundScrollerGoTrees)
			{
				auto backgroundScroller = backgroundScrollerGoTrees->addComponent<BackgroundScroller>();
				if (backgroundScroller)
				{
					backgroundScroller->init(floorManager, "assets/Background_lvl1_trees.png", 0.6f, -1);
				}
			}

		}
		
		auto playerGo = PrefabsFactory::instantiate<PlayerPrefab>();
		if (playerGo)
		{
			playerGo->transform->setParent(worldGO->transform, false);
		}

	}

	return true;
}

void GameScene::unload()
{
}
