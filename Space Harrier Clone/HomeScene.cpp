#include "HomeScene.h"

#include "Engine/API.h"
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Engine/Vector2.h"
#include "HomeSceneManager.h"


bool HomeScene::load()
{
	Audio::setSFXVolume(0.25f);

	auto go = GameObject::createNew();

	if (go)
	{
		go->addComponent<HomeSceneManager>();
	}

	return true;
}


void HomeScene::unload()
{
}
