#include "ExplosionPrefab.h"

#include "Engine/Reference.h"
#include "Engine/GameObject.h"
#include "Engine/SpriteSheet.h"
#include "Explosion.h"
#include "FloorObjectMover.h"
#include "FloorObjectType.h"


void ExplosionPrefab::configureGameObject(Reference<GameObject>& gameObject) const
{
	auto spriteSheet = gameObject->addComponent<SpriteSheet>();
	if (spriteSheet)
	{
		spriteSheet->loadImage("assets/sprites/Explosion.png");
		spriteSheet->setAllPivots(Vector2(0.5f, 0));
		spriteSheet->setRenderLayer("Main");

		spriteSheet->addAnimation("explosion");
		spriteSheet->addRectForAnimation("explosion", Vector2(5, 5), 152, 104);
		spriteSheet->addRectForAnimation("explosion", Vector2(160, 5), 152, 104);
		spriteSheet->addRectForAnimation("explosion", Vector2(315, 5), 152, 104);
		spriteSheet->addRectForAnimation("explosion", Vector2(470, 5), 152, 104);
		spriteSheet->addRectForAnimation("explosion", Vector2(5, 115), 152, 104);
		spriteSheet->addRectForAnimation("explosion", Vector2(160, 115), 152, 104);
		spriteSheet->addRectForAnimation("explosion", Vector2(315, 115), 152, 104);
		spriteSheet->addRectForAnimation("explosion", Vector2(470, 115), 152, 104);
		spriteSheet->addRectForAnimation("explosion", Vector2(5, 225), 152, 104);
		spriteSheet->addRectForAnimation("explosion", Vector2(160, 225), 152, 104);
		spriteSheet->addRectForAnimation("explosion", Vector2(315, 225), 152, 104);
		spriteSheet->addRectForAnimation("explosion", Vector2(470, 225), 152, 104);
	}

	auto fom = gameObject->addComponent<FloorObjectMover>();
	if (fom)
	{
		fom->setType(FloorObjectType::NEUTRAL);
	}

	auto explosion = gameObject->addComponent<Explosion>();
}
