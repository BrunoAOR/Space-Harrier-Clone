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
#include "BackgroundScroller.h"
#include "TimeLogger.h"
#include "PlayerPrefab.h"
#include "Player.h"
#include "EnemiesFactory.h"
#include "EnemySpawnInfo.h"
#include "MotionPattern.h"
#include "Engine/SDL2_mixer/include/SDL_mixer.h"

bool GameScene::load()
{
	Audio::setSFXVolume(0.25f);

	auto worldGO = GameObject::createNew();
	if (worldGO)
	{
		//worldGO->addComponent<TimeLogger>();
		worldGO->transform->setWorldPosition(Vector2(SCREEN_WIDTH / 2.0f, 0));

		auto floorManagerGo = GameObject::createNew();
		if (floorManagerGo)
		{
			floorManagerGo->transform->setParent(worldGO->transform, false);

			auto floorManager = floorManagerGo->addComponent<FloorManager>();

			if (floorManager)
			{
				floorManager->init("assets/sprites/FloorGreen.png");
			}

			auto playerGo = Prefabs::instantiate(Prefabs::getPrefab("PlayerPrefab"));
			if (playerGo)
			{
				playerGo->transform->setParent(worldGO->transform, false);
				Reference<Player>& player = playerGo->getComponent<Player>();
				if (player)
				{
					player->floorManager = floorManager;
				}

				auto enemiesFactoryGo = GameObject::createNew();
				if (enemiesFactoryGo)
				{
					enemiesFactoryGo->transform->setParent(worldGO->transform, false);
					auto enemiesFactory = enemiesFactoryGo->addComponent<EnemiesFactory>();
					if (enemiesFactory)
					{
						enemiesFactory->init(player->getCharacterTransform(), floorManager, getEnemiesSpawnInfo(), getMotionPatterns());
					}
				}
			}

			auto objectsFactoryGo = GameObject::createNew();
			if (objectsFactoryGo)
			{
				objectsFactoryGo->transform->setParent(worldGO->transform, false);
				auto floorObjectsFactory = objectsFactoryGo->addComponent<FloorObjectsFactory>();
				if (floorObjectsFactory)
				{
					floorObjectsFactory->init(floorManager);
				}
			}

			

			// True background
			auto backgroundScrollerGo = GameObject::createNew();
			if (backgroundScrollerGo)
			{
				auto backgroundScroller = backgroundScrollerGo->addComponent<BackgroundScroller>();
				if (backgroundScroller)
				{
					backgroundScroller->init(floorManager, "assets/sprites/Background_lvl1.png", 0, -3);
				}
			}

			// Mountains
			auto backgroundScrollerGoMountains = GameObject::createNew();
			if (backgroundScrollerGoMountains)
			{
				auto backgroundScroller = backgroundScrollerGoMountains->addComponent<BackgroundScroller>();
				if (backgroundScroller)
				{
					backgroundScroller->init(floorManager, "assets/sprites/Background_lvl1_mountains.png", 0.3f, -2);
				}
			}

			// Grass
			auto backgroundScrollerGoTrees = GameObject::createNew();
			if (backgroundScrollerGoTrees)
			{
				auto backgroundScroller = backgroundScrollerGoTrees->addComponent<BackgroundScroller>();
				if (backgroundScroller)
				{
					backgroundScroller->init(floorManager, "assets/sprites/Background_lvl1_trees.png", 0.6f, -1);
				}
			}
			
			
		}
	}

	return true;
}

void GameScene::unload()
{
}
