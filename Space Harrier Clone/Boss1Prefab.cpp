#include "Boss1Prefab.h"

#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Engine/gameConfig.h"
#include "Engine/Sprite.h"
#include "Engine/RectangleCollider.h"
#include "Boss1.h"
#include "CollisionCallbackForwarder.h"

void Boss1Prefab::configureGameObject(Reference<GameObject>& gameObject) const
{
	gameObject->transform->setWorldPosition(Vector2(SCREEN_WIDTH / 2.0f, 0));

	auto boss1 = gameObject->addComponent<Boss1>();

	auto childGo = GameObject::createNew();
	if (childGo)
	{
		childGo->transform->setParent(gameObject->transform, false);

		auto sprite = childGo->addComponent<Sprite>();
		if (sprite)
		{
			sprite->loadImage("assets/sprites/Boss_lvl1.png");
			sprite->setAllPivots(Vector2(0.5f, 0));
			sprite->setRenderLayer("Main");
		}

		auto rectCollider = childGo->addComponent<RectangleCollider>();
		if (rectCollider)
		{
			rectCollider->isTrigger = true;
			rectCollider->size = Vector2(68, 109);
			rectCollider->offset = Vector2(0, 109 / 2.0f);
			rectCollider->setCollisionLayer("Enemy");
		}

		auto ccf = childGo->addComponent<CollisionCallbackForwarder>();
		if (ccf)
		{
			ccf->addTarget(boss1);
		}
	}

	auto shadow = gameObject->addComponent<Sprite>();
	if (shadow)
	{
		shadow->setRenderLayer("Shadows");
		shadow->setZIndex(0);

		shadow->loadImage("assets/sprites/Boss_lvl1.png");
		shadow->setClipRect(SDL_Rect{ 340, 480, 62, 18 });
		shadow->setAllPivots(Vector2(0.5f, 0));
	}

	gameObject->setActive(false);
}
