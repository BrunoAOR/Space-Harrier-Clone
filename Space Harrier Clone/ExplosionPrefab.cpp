#include "ExplosionPrefab.h"

#include "Engine/Reference.h"
#include "Engine/GameObject.h"
#include "Engine/SpriteSheet.h"
#include "gameData.h"
#include "Explosion.h"
#include "FloorObjectMover.h"
#include "ObjectEffectType.h"


void ExplosionPrefab::configureGameObject(Reference<GameObject>& gameObject) const
{
	auto spriteSheet = gameObject->addComponent<SpriteSheet>();
	if (spriteSheet)
	{
		spriteSheet->loadImage(ASSET_IMG_EXPLOSION);
		spriteSheet->setAllPivots(Vector2(0.5f, 0));
		spriteSheet->setRenderLayer(RENDER_LAYER_2_MAIN);

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
		fom->setType(ObjectEffectType::NEUTRAL);
	}

	auto explosion = gameObject->addComponent<Explosion>();
}
