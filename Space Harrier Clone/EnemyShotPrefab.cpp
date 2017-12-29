#include "EnemyShotPrefab.h"

#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Engine/Sprite.h"
#include "Engine/SpriteSheet.h"
#include "Engine/CircleCollider.h"
#include "EnemyShot.h"
#include "CollisionCallbackForwarder.h"


void EnemyShotPrefab::configureGameObject(Reference<GameObject>& gameObject) const
{
	auto eShot = gameObject->addComponent<EnemyShot>();

	auto childGo = GameObject::createNew();
	if (childGo)
	{
		childGo->transform->setParent(gameObject->transform, false);

		auto spriteSheet = childGo->addComponent<SpriteSheet>();
		if (spriteSheet)
		{
			spriteSheet->loadImage("assets/sprites/Enemies.png");
			spriteSheet->setAllPivots(Vector2(0.5f, 0.5f));
			spriteSheet->setRenderLayer("Main");

			spriteSheet->addAnimation("shot");
			spriteSheet->addRectForAnimation("shot", Vector2(5, 5), 68, 68);
			spriteSheet->addRectForAnimation("shot", Vector2(80, 5), 68, 68);
			spriteSheet->addRectForAnimation("shot", Vector2(155, 5), 68, 68);
			spriteSheet->addRectForAnimation("shot", Vector2(230, 5), 68, 68);
			spriteSheet->addRectForAnimation("shot", Vector2(5, 80), 68, 68);
			spriteSheet->addRectForAnimation("shot", Vector2(80, 80), 68, 68);
			spriteSheet->addRectForAnimation("shot", Vector2(155, 80), 68, 68);
			spriteSheet->addRectForAnimation("shot", Vector2(230, 80), 68, 68);

		}

		auto circColl = childGo->addComponent<CircleCollider>();
		if (circColl)
		{
			circColl->isTrigger = true;
			// Shot's collider is smaller than the sprite (only the central circle area)
			circColl->radius = 21;
			// Note: No need to offset the shot collider, because the sprite's pivot is at the center
			circColl->setCollisionLayer("EnemyShot");
		}

		auto ccf = childGo->addComponent<CollisionCallbackForwarder>();
		if (ccf)
		{
			ccf->addTarget(eShot);
		}
	}

	auto shadowGo = GameObject::createNew();
	if (shadowGo)
	{
		shadowGo->transform->setParent(gameObject->transform, false);

		auto shadow = shadowGo->addComponent<Sprite>();
		if (shadow)
		{
			shadow->setRenderLayer("Shadows");
			shadow->setZIndex(0);

			shadow->loadImage("assets/sprites/Enemies.png");
			shadow->setClipRect(SDL_Rect{ 235, 150, 62, 18 });
			shadow->setAllPivots(Vector2(0.5f, 0));
		}
	}

	

}
