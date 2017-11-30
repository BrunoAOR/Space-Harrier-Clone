#include "PlayerPrefab.h"

#include "Engine/Reference.h"
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Engine/SpriteSheet.h"
#include "Engine/Sprite.h"
#include "Player.h"


Reference<GameObject> PlayerPrefab::configureGameObject()
{
	auto go = GameObject::createNew();
	if (go)
	{
		auto player = go->addComponent<Player>();
		if (player)
		{
			auto characterGo = GameObject::createNew();
			if (characterGo)
			{
				characterGo->transform->setParent(go->transform, false);

				auto spriteSheet = characterGo->addComponent<SpriteSheet>();
				if (spriteSheet)
				{
					spriteSheet->setRenderLayer("Foreground");
					spriteSheet->setZIndex(2);
					spriteSheet->loadImage("assets/Character.png");
					spriteSheet->setAllPivots(Vector2(0.5f, 0));

					// Animation: run
					spriteSheet->addAnimation("run");
					spriteSheet->addRectForAnimation("run", Vector2(3, 2), 18, 49);
					spriteSheet->addRectForAnimation("run", Vector2(27, 2), 18, 49);
					spriteSheet->addRectForAnimation("run", Vector2(51, 2), 21, 49);
					spriteSheet->addRectForAnimation("run", Vector2(77, 2), 17, 49);

					// Animation: flyCenter
					spriteSheet->addAnimation("flyCenter");
					spriteSheet->addRectForAnimation("flyCenter", Vector2(109, 2), 23, 49);
					spriteSheet->addRectForAnimation("flyCenter", Vector2(109, 2), 23, 50);
					

					// Animation: flyLeft
					spriteSheet->addAnimation("flyLeft");
					spriteSheet->addRectForAnimation("flyLeft", Vector2(143, 2), 19, 49);
					spriteSheet->addRectForAnimation("flyLeft", Vector2(143, 2), 19, 50);

					// Animation: flyCenterLeft
					spriteSheet->addAnimation("flyCenterLeft");
					spriteSheet->addRectForAnimation("flyCenterLeft", Vector2(171, 2), 16, 49);
					spriteSheet->addRectForAnimation("flyCenterLeft", Vector2(171, 2), 16, 50);

					// Animation: flyCenterRight
					spriteSheet->addAnimation("flyCenterRight");
					spriteSheet->addRectForAnimation("flyCenterRight", Vector2(198, 2), 16, 49);
					spriteSheet->addRectForAnimation("flyCenterRight", Vector2(198, 2), 16, 50);

					// Animation: flyRight
					spriteSheet->addAnimation("flyRight");
					spriteSheet->addRectForAnimation("flyRight", Vector2(222, 2), 19, 49);
					spriteSheet->addRectForAnimation("flyRight", Vector2(222, 2), 19, 50);
				}
			}
			
			auto shadowGo = GameObject::createNew();
			if (shadowGo)
			{
				shadowGo->transform->setParent(go->transform, false);

				auto shadow = shadowGo->addComponent<Sprite>();
				if (shadow)
				{
					shadow->setRenderLayer("Foreground");
					shadow->setZIndex(1);

					shadow->loadImage("assets/Character.png");
					shadow->setClipRect(SDL_Rect{ 197, 76, 43, 20 });
					shadow->setAllPivots(Vector2(0.5f, 0));
				}
			}
			if (characterGo && shadowGo)
			{
				player->init(characterGo, shadowGo);
			}
		}
	}

	return go;
}
