#include "TreePrefab.h"

#include "Engine/Reference.h"
#include "Engine/GameObject.h"
#include "Engine/Sprite.h"
#include "FloorObjectMover.h"


Reference<GameObject> TreePrefab::configureGameObject()
{
	auto go = GameObject::createNew();
	if (go)
	{
		auto sprite = go->addComponent<Sprite>();
		if (sprite)
		{
			sprite->setActive(false);
			sprite->loadImage("assets/Tree.png");
			sprite->setAllPivots(Vector2(0.5f, 0));
			sprite->setRenderLayer("Main");
		}
		go->addComponent<FloorObjectMover>();
	}
	return go;
}
