#include "Boss1ExplosionPrefab.h"

#include "Engine/Reference.h"
#include "Engine/GameObject.h"
#include "Engine/SpriteSheet.h"
#include "Explosion.h"
#include "FloorObjectMover.h"
#include "ObjectEffectType.h"


void Boss1ExplosionPrefab::configureGameObject(Reference<GameObject>& gameObject) const
{
	auto spriteSheet = gameObject->addComponent<SpriteSheet>();
	if (spriteSheet)
	{
		spriteSheet->loadImage("assets/sprites/Boss_lvl1.png");
		spriteSheet->setAllPivots(Vector2(0.5f, 0));
		spriteSheet->setRenderLayer("Main");

		spriteSheet->addAnimation("explosion");
		spriteSheet->addRectForAnimation("explosion", Vector2(340,   5), 152, 104);
		spriteSheet->addRectForAnimation("explosion", Vector2(340, 110), 152, 104);
		spriteSheet->addRectForAnimation("explosion", Vector2(340, 215), 152, 104);
		spriteSheet->addRectForAnimation("explosion", Vector2(340, 320), 152, 104);

	}

	auto fom = gameObject->addComponent<FloorObjectMover>();
	if (fom)
	{
		fom->setType(ObjectEffectType::NEUTRAL);
	}

	auto explosion = gameObject->addComponent<Explosion>();
}
