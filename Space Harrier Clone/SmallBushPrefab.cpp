#include "SmallBushPrefab.h"

#include "Engine/Reference.h"
#include "Engine/GameObject.h"
#include "Engine/Sprite.h"
#include "Engine/RectangleCollider.h"
#include "gameData.h"
#include "FloorObjectMover.h"
#include "ObjectEffectType.h"


void SmallBushPrefab::configureGameObject(Reference<GameObject>& gameObject) const
{
	auto sprite = gameObject->addComponent<Sprite>();
	if (sprite)
	{
		sprite->loadImage(ASSET_IMG_OBSTACLES);
		sprite->setClipRect(SDL_Rect{ 5, 85, 124, 70 });
		sprite->setAllPivots(Vector2(0.5f, 0));
		sprite->setRenderLayer(RENDER_LAYER_2_MAIN);
	}

	auto rectColl = gameObject->addComponent<RectangleCollider>();
	if (rectColl)
	{
		rectColl->isTrigger = true;
		rectColl->size = Vector2(124, 5);
		rectColl->offset.y += rectColl->size.y / 2;
		rectColl->setCollisionLayer(COLLISION_LAYER_4_OBSTACLE);
	}

	auto fom = gameObject->addComponent<FloorObjectMover>();
	if (fom)
	{
		fom->setType(ObjectEffectType::SHORT_TRIP);
	}
}
