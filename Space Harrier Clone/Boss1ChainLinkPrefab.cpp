#include "Boss1ChainLinkPrefab.h"

#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Engine/gameConfig.h"
#include "Engine/Sprite.h"
#include "Engine/RectangleCollider.h"
#include "gameData.h"
#include "Boss1ChainLink.h"
#include "BulletBouncer.h"
#include "CollisionCallbackForwarder.h"


void Boss1ChainLinkPrefab::configureGameObject(Reference<GameObject>& gameObject) const
{
	gameObject->transform->setWorldPosition(Vector2(SCREEN_WIDTH / 2.0f, 0));

	auto boss1ChainLink = gameObject->addComponent<Boss1ChainLink>();
	auto bulletBouncer = gameObject->addComponent<BulletBouncer>();

	auto childGo = GameObject::createNew();
	if (childGo)
	{
		childGo->transform->setParent(gameObject->transform, false);

		auto sprite = childGo->addComponent<Sprite>();
		if (sprite)
		{
			sprite->loadImage(ASSET_IMG_BOSS);
			sprite->setAllPivots(Vector2(0.5f, 0));
			sprite->setRenderLayer(RENDER_LAYER_2_MAIN);
			sprite->setClipRect(SDL_Rect{ 150, 10, 110, 73 });
		}

		auto rectCollider = childGo->addComponent<RectangleCollider>();
		if (rectCollider)
		{
			rectCollider->isTrigger = true;
			rectCollider->size = Vector2(75, 74);
			rectCollider->offset = Vector2(0, 74 / 2.0f);
			rectCollider->setCollisionLayer(COLLISION_LAYER_2_ENEMY);
		}

		auto ccf = childGo->addComponent<CollisionCallbackForwarder>();
		if (ccf)
		{
			ccf->addTarget(bulletBouncer);
		}
	}

	auto shadow = gameObject->addComponent<Sprite>();
	if (shadow)
	{
		shadow->setRenderLayer(RENDER_LAYER_1_SHADOWS);
		shadow->setZIndex(0);

		shadow->loadImage(ASSET_IMG_BOSS);
		shadow->setClipRect(SDL_Rect{ 340, 480, 62, 18 });
		shadow->setAllPivots(Vector2(0.5f, 0));

	}

	gameObject->setActive(false);
}
