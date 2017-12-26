#include "BigBushPrefab.h"

#include "Engine/Reference.h"
#include "Engine/GameObject.h"
#include "Engine/Sprite.h"
#include "Engine/RectangleCollider.h"
#include "FloorObjectMover.h"
#include "ObjectEffectType.h"


void BigBushPrefab::configureGameObject(Reference<GameObject>& gameObject) const
{
	auto sprite = gameObject->addComponent<Sprite>();
	if (sprite)
	{
		sprite->loadImage("assets/sprites/Floor_objects.png");
		sprite->setClipRect(SDL_Rect{ 5, 160, 152, 71 });
		sprite->setAllPivots(Vector2(0.5f, 0));
		sprite->setRenderLayer("Main");
	}

	auto rectColl = gameObject->addComponent<RectangleCollider>();
	if (rectColl)
	{
		rectColl->isTrigger = true;
		rectColl->size = Vector2(152, 5);
		rectColl->offset.y += rectColl->size.y / 2;
		rectColl->setCollisionLayer("Obstacle");
	}

	auto fom = gameObject->addComponent<FloorObjectMover>();
	if (fom)
	{
		fom->setType(ObjectEffectType::LONG_TRIP);
	}
}
