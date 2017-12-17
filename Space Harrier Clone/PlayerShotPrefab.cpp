#include "PlayerShotPrefab.h"

#include "Engine/Reference.h"
#include "Engine/GameObject.h"
#include "Engine/SpriteSheet.h"
#include "Engine/RectangleCollider.h"
#include "PlayerShot.h"
#include "FloorObjectMover.h"
#include "FloorObjectType.h"

void PlayerShotPrefab::configureGameObject(Reference<GameObject>& gameObject) const
{
	auto spriteSheet = gameObject->addComponent<SpriteSheet>();
	if (spriteSheet)
	{
		spriteSheet->loadImage("assets/sprites/Character.png");
		spriteSheet->setAllPivots(Vector2(0.5f, 0));
		spriteSheet->setRenderLayer("Main");

		spriteSheet->addAnimation("shot");
		spriteSheet->addRectForAnimation("shot", Vector2(385, 60), 45, 30);
		spriteSheet->addRectForAnimation("shot", Vector2(385, 95), 45, 30);
		spriteSheet->addRectForAnimation("shot", Vector2(385, 130), 45, 30);
		spriteSheet->addRectForAnimation("shot", Vector2(385, 165), 45, 30);
	}

	auto rectColl = gameObject->addComponent<RectangleCollider>();
	if (rectColl)
	{
		rectColl->isTrigger = true;
		// Shot's collider is enlarged 20% to make hitting enemies easier
		rectColl->size = Vector2(45 * 1.2, 30 * 1.2);
		rectColl->offset.y += 45 / 2;
		rectColl->setCollisionLayer("PlayerShot");
	}

	auto pShot = gameObject->addComponent<PlayerShot>();
}
