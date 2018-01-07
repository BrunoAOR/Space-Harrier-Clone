#include "HomeScene.h"

#include <assert.h>
#include "Engine/API.h"
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Engine/Vector2.h"
#include "gameData.h"
#include "HomeSceneManager.h"
#include "SceneFader.h"


bool HomeScene::load()
{
	Audio::setSFXVolume(0.25f);
	
	{
		auto go = Prefabs::instantiate(Prefabs::getPrefab(SCENE_FADER_PREFAB));
		assert(go);
		auto sceneFader = go->getComponent<SceneFader>();
		assert(sceneFader);
		sceneFader->init(1, SDL_Color{ 0, 0, 0, 255 }, 100, 0, 100, false);
	}
	
	{
		auto go = GameObject::createNew();
		assert(go);
		{
			go->addComponent<HomeSceneManager>();
		}
	}

	return true;
}


void HomeScene::unload()
{
}
