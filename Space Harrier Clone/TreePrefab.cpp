#include "TreePrefab.h"

#include "Engine/Reference.h"
#include "Engine/GameObject.h"
#include "Engine/Sprite.h"
#include "Engine/RectangleCollider.h"
#include "FloorObjectMover.h"
#include "ObjectEffectType.h"
#include "ExplosiveObject.h"
#include "ObstaclePoints.h"


void TreePrefab::configureGameObject(Reference<GameObject>& gameObject) const
{
	auto sprite = gameObject->addComponent<Sprite>();
	if (sprite)
	{
		sprite->loadImage("assets/sprites/Floor_objects.png");
		sprite->setClipRect(SDL_Rect{ 165, 5, 84, 178 });
		sprite->setAllPivots(Vector2(0.5f, 0));
		sprite->setRenderLayer("Main");
	}

	auto obstaclePoints = gameObject->addComponent<ObstaclePoints>();
	if (obstaclePoints)
	{
		obstaclePoints->bigPointsBonus = false;
	}

	auto rectColl = gameObject->addComponent<RectangleCollider>();
	if (rectColl)
	{
		rectColl->isTrigger = true;
		// Tree's collider height is reduced by 20px to allow the player to fly over it
		rectColl->size = Vector2(84, 178 - 20);
		rectColl->offset.y += rectColl->size.y / 2;
		rectColl->setCollisionLayer("Obstacle");
	}

	auto fom = gameObject->addComponent<FloorObjectMover>();
	if (fom)
	{
		fom->setType(ObjectEffectType::DIE);
	}

	gameObject->addComponent<ExplosiveObject>();
}
