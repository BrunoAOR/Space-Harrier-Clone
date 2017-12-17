#include "RockPrefab.h"

#include "Engine/Reference.h"
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Engine/Sprite.h"
#include "Engine/RectangleCollider.h"
#include "FloorObjectMover.h"
#include "FloorObjectType.h"
#include "CollisionCallbackForwarder.h"
#include "ExplosiveObject.h"


void RockPrefab::configureGameObject(Reference<GameObject>& gameObject) const
{
	auto shadowSprite = gameObject->addComponent<Sprite>();
	if (shadowSprite)
	{
		shadowSprite->loadImage("assets/sprites/Floor_objects.png");
		shadowSprite->setClipRect(SDL_Rect{ 170, 190, 62, 18 });
		shadowSprite->setAllPivots(Vector2(0.5f, 0));
		shadowSprite->setRenderLayer("Main");
	}

	auto fom = gameObject->addComponent<FloorObjectMover>();
	if (fom)
	{
		fom->setType(FloorObjectType::DIE);
	}

	auto explosiveObject = gameObject->addComponent<ExplosiveObject>();

	Reference<GameObject> childGo = GameObject::createNew();
	if (childGo)
	{
		childGo->transform->setParent(gameObject->transform);
		childGo->transform->setLocalPosition(Vector2(0, 145));

		auto sprite = childGo->addComponent<Sprite>();
		if (sprite)
		{
			sprite->loadImage("assets/sprites/Floor_objects.png");
			sprite->setClipRect(SDL_Rect{ 5, 5, 113, 76 });
			sprite->setAllPivots(Vector2(0.5f, 0));
			sprite->setRenderLayer("Main");
		}

		auto rectColl = childGo->addComponent<RectangleCollider>();
		if (rectColl)
		{
			rectColl->isTrigger = true;
			rectColl->size = Vector2(113, 76);
			rectColl->offset.y += rectColl->size.y / 2;
			rectColl->setCollisionLayer("Obstacle");
		}

		auto ccf = childGo->addComponent<CollisionCallbackForwarder>();
		if (ccf)
		{
			ccf->target = explosiveObject;
		}
	}
}
