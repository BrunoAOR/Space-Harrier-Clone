#include "EnemyShipPrefab.h"

#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Engine/SpriteSheet.h"
#include "Engine/Sprite.h"
#include "Engine/RectangleCollider.h"
#include "gameData.h"
#include "EnemyShip.h"
#include "CollisionCallbackForwarder.h"
#include "ExplosiveObject.h"


void EnemyShipPrefab::configureGameObject(Reference<GameObject>& gameObject) const
{
	auto enemy = gameObject->addComponent<EnemyShip>();
	auto explosiveObject = gameObject->addComponent<ExplosiveObject>();
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
				rectColl->size = Vector2(112, 48);
				rectColl->offset.y += rectColl->size.y / 2;
				rectColl->setCollisionLayer(COLLISION_LAYER_2_ENEMY);
			}

			auto spriteSheet = characterGo->addComponent<SpriteSheet>();
			if (spriteSheet)
			{
				spriteSheet->loadImage(ASSET_IMG_ENEMIES);
				spriteSheet->setAllPivots(Vector2(0.5f, 0));
				spriteSheet->setRenderLayer(RENDER_LAYER_2_MAIN);

				spriteSheet->addAnimation("fly");
				spriteSheet->addRectForAnimation("fly", Vector2(5, 150), 112, 48);
				spriteSheet->addRectForAnimation("fly", Vector2(120, 150), 112, 48);
				spriteSheet->addRectForAnimation("fly", Vector2(5, 205), 112, 48);
				spriteSheet->addRectForAnimation("fly", Vector2(120, 205), 112, 48);
			}

			auto ccf = characterGo->addComponent<CollisionCallbackForwarder>();
			if (ccf)
			{
				ccf->addTarget(enemy);
				ccf->addTarget(explosiveObject);
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
			shadow->setRenderLayer(RENDER_LAYER_1_SHADOWS);
			shadow->setZIndex(0);

			shadow->loadImage(ASSET_IMG_ENEMIES);
			shadow->setClipRect(SDL_Rect{ 235, 150, 62, 18 });
			shadow->setAllPivots(Vector2(0.5f, 0));
		}
	}
}
