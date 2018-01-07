#include "RockPrefab.h"

#include "Engine/Reference.h"
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Engine/Sprite.h"
#include "Engine/RectangleCollider.h"
#include "gameData.h"
#include "FloorObjectMover.h"
#include "ObjectEffectType.h"
#include "CollisionCallbackForwarder.h"
#include "ExplosiveObject.h"
#include "ObstaclePoints.h"


void RockPrefab::configureGameObject(Reference<GameObject>& gameObject) const
{
	auto shadowSprite = gameObject->addComponent<Sprite>();
	if (shadowSprite)
	{
		shadowSprite->loadImage(ASSET_IMG_OBSTACLES);
		shadowSprite->setClipRect(SDL_Rect{ 170, 190, 62, 18 });
		shadowSprite->setAllPivots(Vector2(0.5f, 0));
		shadowSprite->setRenderLayer(RENDER_LAYER_1_SHADOWS);
	}

	auto fom = gameObject->addComponent<FloorObjectMover>();
	if (fom)
	{
		fom->setType(ObjectEffectType::DIE);
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
			sprite->loadImage(ASSET_IMG_OBSTACLES);
			sprite->setClipRect(SDL_Rect{ 5, 5, 113, 76 });
			sprite->setAllPivots(Vector2(0.5f, 0));
			sprite->setRenderLayer(RENDER_LAYER_2_MAIN);
		}

		auto obstaclePoints = childGo->addComponent<ObstaclePoints>();
		if (obstaclePoints)
		{
			obstaclePoints->bigPointsBonus = true;
		}

		auto rectColl = childGo->addComponent<RectangleCollider>();
		if (rectColl)
		{
			rectColl->isTrigger = true;
			rectColl->size = Vector2(113, 76);
			rectColl->offset.y += rectColl->size.y / 2;
			rectColl->setCollisionLayer(COLLISION_LAYER_4_OBSTACLE);
		}

		auto ccf = childGo->addComponent<CollisionCallbackForwarder>();
		if (ccf)
		{
			ccf->addTarget(explosiveObject);
		}
	}
}
