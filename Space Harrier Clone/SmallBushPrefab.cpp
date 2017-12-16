#include "SmallBushPrefab.h"

#include "Engine/Reference.h"
#include "Engine/GameObject.h"
#include "Engine/Sprite.h"
#include "Engine/RectangleCollider.h"
#include "FloorObjectMover.h"
#include "FloorObjectType.h"


void SmallBushPrefab::configureGameObject(Reference<GameObject>& gameObject) const
{
	auto sprite = gameObject->addComponent<Sprite>();
	if (sprite)
	{
		sprite->loadImage("assets/sprites/Floor_objects.png");
		sprite->setClipRect(SDL_Rect{ 5, 85, 124, 70 });
		sprite->setAllPivots(Vector2(0.5f, 0));
		sprite->setRenderLayer("Main");
	}

	auto rectColl = gameObject->addComponent<RectangleCollider>();
	if (rectColl)
	{
		rectColl->isTrigger = true;
		rectColl->size = Vector2(124, 5);
		rectColl->offset.y += rectColl->size.y / 2;
		rectColl->setCollisionLayer("Obstacle");
	}

	auto fom = gameObject->addComponent<FloorObjectMover>();
	if (fom)
	{
		fom->setType(FloorObjectType::SHORT_TRIP);
	}
}
