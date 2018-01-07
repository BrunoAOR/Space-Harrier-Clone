#include "PlayerShotPrefab.h"

#include "Engine/Reference.h"
#include "Engine/GameObject.h"
#include "Engine/SpriteSheet.h"
#include "Engine/RectangleCollider.h"
#include "gameData.h"
#include "PlayerShot.h"
#include "FloorObjectMover.h"
#include "ObjectEffectType.h"

void PlayerShotPrefab::configureGameObject(Reference<GameObject>& gameObject) const
{
	auto spriteSheet = gameObject->addComponent<SpriteSheet>();
	if (spriteSheet)
	{
		spriteSheet->loadImage(ASSET_IMG_CHARACTER);
		spriteSheet->setAllPivots(Vector2(0.5f, 0.5f));
		spriteSheet->setRenderLayer(RENDER_LAYER_2_MAIN);

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
		// Note: No need to offset the shot collider, because the sprite's pivot is at the center
		rectColl->setCollisionLayer(COLLISION_LAYER_1_PLAYER_SHOT);
	}

	auto pShot = gameObject->addComponent<PlayerShot>();
}
