#include "PlayerPrefab.h"

#include "Engine/Reference.h"
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Engine/SpriteSheet.h"
#include "Engine/Sprite.h"
#include "Engine/RectangleCollider.h"
#include "Player.h"
#include "PlayerCollisionController.h"


void PlayerPrefab::configureGameObject(Reference<GameObject>& gameObject) const
{
	auto player = gameObject->addComponent<Player>();
	if (player)
	{
		auto characterGo = GameObject::createNew();
		if (characterGo)
		{
			characterGo->transform->setParent(gameObject->transform, false);

			characterGo->addComponent<PlayerCollisionController>();

			auto rectColl = characterGo->addComponent<RectangleCollider>();
			if (rectColl)
			{
				rectColl->isTrigger = true;
				// The player collider size is intentionally smaller to lower the difficulty of the game
				rectColl->size = Vector2(14, 40);
				// Offset added to center the collider in the sprite
				rectColl->offset.y += 25;
				rectColl->setCollisionLayer("Player");
				rectColl->zIndex = 95;
			}

			auto spriteSheet = characterGo->addComponent<SpriteSheet>();
			if (spriteSheet)
			{
				spriteSheet->setRenderLayer("Foreground");
				spriteSheet->setZIndex(2);
				spriteSheet->loadImage("assets/sprites/Character.png");
				spriteSheet->setAllPivots(Vector2(0.5f, 0));

				// Animation: run
				spriteSheet->addAnimation("run");
				spriteSheet->addRectForAnimation("run", Vector2(5, 5), 33, 62);
				spriteSheet->addRectForAnimation("run", Vector2(40, 5), 33, 62);
				spriteSheet->addRectForAnimation("run", Vector2(75, 5), 33, 62);
				spriteSheet->addRectForAnimation("run", Vector2(110, 5), 33, 62);
				spriteSheet->addRectForAnimation("run", Vector2(145, 5), 33, 62);
				spriteSheet->addRectForAnimation("run", Vector2(180, 5), 33, 62);
				spriteSheet->addRectForAnimation("run", Vector2(215, 5), 33, 62);
				spriteSheet->addRectForAnimation("run", Vector2(250, 5), 33, 62);
				
				// Animation: flyLeft
				spriteSheet->addAnimation("flyLeft");
				spriteSheet->addRectForAnimation("flyLeft", Vector2(5, 70), 36, 60);
				spriteSheet->addRectForAnimation("flyLeft", Vector2(5, 135), 36, 60);
				spriteSheet->addRectForAnimation("flyLeft", Vector2(5, 200), 36, 60);
				spriteSheet->addRectForAnimation("flyLeft", Vector2(5, 265), 36, 60);
				spriteSheet->addRectForAnimation("flyLeft", Vector2(5, 265), 36, 60);
				spriteSheet->addRectForAnimation("flyLeft", Vector2(5, 200), 36, 60);
				spriteSheet->addRectForAnimation("flyLeft", Vector2(5, 135), 36, 60);
				spriteSheet->addRectForAnimation("flyLeft", Vector2(5, 70), 36, 60);


				// Animation: flyCenterLeft
				spriteSheet->addAnimation("flyCenterLeft");
				spriteSheet->addRectForAnimation("flyCenterLeft", Vector2(45, 70), 36, 60);
				spriteSheet->addRectForAnimation("flyCenterLeft", Vector2(45, 135), 36, 60);
				spriteSheet->addRectForAnimation("flyCenterLeft", Vector2(45, 200), 36, 60);
				spriteSheet->addRectForAnimation("flyCenterLeft", Vector2(45, 265), 36, 60);
				spriteSheet->addRectForAnimation("flyCenterLeft", Vector2(45, 265), 36, 60);
				spriteSheet->addRectForAnimation("flyCenterLeft", Vector2(45, 200), 36, 60);
				spriteSheet->addRectForAnimation("flyCenterLeft", Vector2(45, 135), 36, 60);
				spriteSheet->addRectForAnimation("flyCenterLeft", Vector2(45, 70), 36, 60);

				// Animation: flyCenter
				spriteSheet->addAnimation("flyCenter");
				spriteSheet->addRectForAnimation("flyCenter", Vector2(85, 70), 36, 60);
				spriteSheet->addRectForAnimation("flyCenter", Vector2(85, 135), 36, 60);
				spriteSheet->addRectForAnimation("flyCenter", Vector2(85, 200), 36, 60);
				spriteSheet->addRectForAnimation("flyCenter", Vector2(85, 265), 36, 60);
				spriteSheet->addRectForAnimation("flyCenter", Vector2(85, 265), 36, 60);
				spriteSheet->addRectForAnimation("flyCenter", Vector2(85, 200), 36, 60);
				spriteSheet->addRectForAnimation("flyCenter", Vector2(85, 135), 36, 60);
				spriteSheet->addRectForAnimation("flyCenter", Vector2(85, 70), 36, 60);

				// Animation: flyCenterRight
				spriteSheet->addAnimation("flyCenterRight");
				spriteSheet->addRectForAnimation("flyCenterRight", Vector2(125, 70), 36, 60);
				spriteSheet->addRectForAnimation("flyCenterRight", Vector2(125, 135), 36, 60);
				spriteSheet->addRectForAnimation("flyCenterRight", Vector2(125, 200), 36, 60);
				spriteSheet->addRectForAnimation("flyCenterRight", Vector2(125, 265), 36, 60);
				spriteSheet->addRectForAnimation("flyCenterRight", Vector2(125, 265), 36, 60);
				spriteSheet->addRectForAnimation("flyCenterRight", Vector2(125, 200), 36, 60);
				spriteSheet->addRectForAnimation("flyCenterRight", Vector2(125, 135), 36, 60);
				spriteSheet->addRectForAnimation("flyCenterRight", Vector2(125, 70), 36, 60);

				// Animation: flyRight
				spriteSheet->addAnimation("flyRight");
				spriteSheet->addRectForAnimation("flyRight", Vector2(165, 70), 36, 60);
				spriteSheet->addRectForAnimation("flyRight", Vector2(165, 135), 36, 60);
				spriteSheet->addRectForAnimation("flyRight", Vector2(165, 200), 36, 60);
				spriteSheet->addRectForAnimation("flyRight", Vector2(165, 265), 36, 60);
				spriteSheet->addRectForAnimation("flyRight", Vector2(165, 265), 36, 60);
				spriteSheet->addRectForAnimation("flyRight", Vector2(165, 200), 36, 60);
				spriteSheet->addRectForAnimation("flyRight", Vector2(165, 135), 36, 60);
				spriteSheet->addRectForAnimation("flyRight", Vector2(165, 70), 36, 60);

				// Animation: die
				spriteSheet->addAnimation("die");
				spriteSheet->addRectForAnimation("die", Vector2(205, 200), 54, 56);
				spriteSheet->addRectForAnimation("die", Vector2(260, 200), 54, 56);
				spriteSheet->addRectForAnimation("die", Vector2(315, 200), 54, 56);
				spriteSheet->addRectForAnimation("die", Vector2(370, 200), 54, 56);
				spriteSheet->addRectForAnimation("die", Vector2(205, 265), 54, 56);
				spriteSheet->addRectForAnimation("die", Vector2(260, 265), 54, 56);
				spriteSheet->addRectForAnimation("die", Vector2(315, 265), 54, 56);
				spriteSheet->addRectForAnimation("die", Vector2(370, 265), 54, 56);

				// Animation: postDie
				spriteSheet->addAnimation("postDie");
				spriteSheet->addRectForAnimation("postDie", Vector2(0, 0), 1, 1);
				spriteSheet->addRectForAnimation("postDie", Vector2(85, 265), 36, 60);

				// Animation: shortTrip
				spriteSheet->addAnimation("shortTrip");
				spriteSheet->addRectForAnimation("shortTrip", Vector2(205, 70), 41, 60);
				spriteSheet->addRectForAnimation("shortTrip", Vector2(250, 70), 41, 60);
				spriteSheet->addRectForAnimation("shortTrip", Vector2(295, 70), 41, 60);
				spriteSheet->addRectForAnimation("shortTrip", Vector2(340, 70), 41, 60);
				spriteSheet->addRectForAnimation("shortTrip", Vector2(295, 70), 41, 60);
				spriteSheet->addRectForAnimation("shortTrip", Vector2(250, 70), 41, 60);
				spriteSheet->addRectForAnimation("shortTrip", Vector2(205, 70), 41, 60);

				// Animation: longTrip
				spriteSheet->addAnimation("longTrip");
				spriteSheet->addRectForAnimation("longTrip", Vector2(205, 70), 41, 60);
				spriteSheet->addRectForAnimation("longTrip", Vector2(250, 70), 41, 60);
				spriteSheet->addRectForAnimation("longTrip", Vector2(295, 70), 41, 60);
				spriteSheet->addRectForAnimation("longTrip", Vector2(340, 70), 41, 60);
				spriteSheet->addRectForAnimation("longTrip", Vector2(205, 135), 41, 60);
				spriteSheet->addRectForAnimation("longTrip", Vector2(250, 135), 41, 60);
				spriteSheet->addRectForAnimation("longTrip", Vector2(295, 135), 41, 60);
				spriteSheet->addRectForAnimation("longTrip", Vector2(340, 135), 41, 60);
				spriteSheet->addRectForAnimation("longTrip", Vector2(295, 70), 41, 60);
				spriteSheet->addRectForAnimation("longTrip", Vector2(250, 70), 41, 60);
				spriteSheet->addRectForAnimation("longTrip", Vector2(205, 70), 41, 60);
			}
		}

		auto shadowGo = GameObject::createNew();
		if (shadowGo)
		{
			shadowGo->transform->setParent(gameObject->transform, false);

			auto shadow = shadowGo->addComponent<Sprite>();
			if (shadow)
			{
				shadow->setRenderLayer("Foreground");
				shadow->setZIndex(1);

				shadow->loadImage("assets/sprites/Character.png");
				shadow->setClipRect(SDL_Rect{ 300, 50, 62, 18 });
				shadow->setAllPivots(Vector2(0.5f, 0));
			}
		}
		if (characterGo && shadowGo)
		{
			player->init(characterGo, shadowGo);
		}
	}
}
