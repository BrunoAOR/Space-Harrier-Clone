#include "EnemyBallPrefab.h"

#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Engine/SpriteSheet.h"
#include "Engine/Sprite.h"
#include "Engine/RectangleCollider.h"
#include "EnemyBall.h"
#include "CollisionCallbackForwarder.h"
#include "ExplosiveObject.h"
#include "BulletBouncer.h"


void EnemyBallPrefab::configureGameObject(Reference<GameObject>& gameObject) const
{
	auto enemy = gameObject->addComponent<EnemyBall>();
	auto explosiveObject = gameObject->addComponent<ExplosiveObject>();
	auto bulletBouncer = gameObject->addComponent<BulletBouncer>();
	if (enemy && explosiveObject)
	{
		auto characterGo = GameObject::createNew();
		if (characterGo)
		{
			characterGo->transform->setParent(gameObject->transform, false);

			auto rectColl = characterGo->addComponent<RectangleCollider>();
			if (rectColl)
			{
				rectColl->isTrigger = true;
				rectColl->size = Vector2(60, 59);
				rectColl->offset.y += rectColl->size.y / 2;
				rectColl->setCollisionLayer("Enemy");
			}

			auto spriteSheet = characterGo->addComponent<SpriteSheet>();
			if (spriteSheet)
			{
				spriteSheet->loadImage("assets/sprites/Enemies.png");
				spriteSheet->setAllPivots(Vector2(0.5f, 0));
				spriteSheet->setRenderLayer("Main");

				spriteSheet->addAnimation("open");
				spriteSheet->addRectForAnimation("open", Vector2(370, 135), 60, 59);
				spriteSheet->addRectForAnimation("open", Vector2(305, 135), 60, 59);
				spriteSheet->addRectForAnimation("open", Vector2(435, 70), 60, 59);
				spriteSheet->addRectForAnimation("open", Vector2(370, 70), 60, 59);
				spriteSheet->addRectForAnimation("open", Vector2(305, 70), 60, 59);
				spriteSheet->addRectForAnimation("open", Vector2(435, 5), 60, 59);
				spriteSheet->addRectForAnimation("open", Vector2(370, 5), 60, 59);
				spriteSheet->addRectForAnimation("open", Vector2(305, 5), 60, 59);

				spriteSheet->addAnimation("close");
				spriteSheet->addRectForAnimation("close", Vector2(305, 5), 60, 59);
				spriteSheet->addRectForAnimation("close", Vector2(370, 5), 60, 59);
				spriteSheet->addRectForAnimation("close", Vector2(435, 5), 60, 59);
				spriteSheet->addRectForAnimation("close", Vector2(305, 70), 60, 59);
				spriteSheet->addRectForAnimation("close", Vector2(370, 70), 60, 59);
				spriteSheet->addRectForAnimation("close", Vector2(435, 70), 60, 59);
				spriteSheet->addRectForAnimation("close", Vector2(305, 135), 60, 59);
				spriteSheet->addRectForAnimation("close", Vector2(370, 135), 60, 59);
			}

			auto ccf = characterGo->addComponent<CollisionCallbackForwarder>();
			if (ccf)
			{
				ccf->addTarget(enemy);
				ccf->addTarget(explosiveObject);
				ccf->addTarget(bulletBouncer);
			}
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
