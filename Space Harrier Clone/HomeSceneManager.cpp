#include "HomeSceneManager.h"

#include "Engine/gameConfig.h"
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Engine/Sprite.h"
#include "Engine/SpriteSheet.h"
#include "Engine/TextRenderer.h"
#include "Engine/API.h"

#include <string>


void HomeSceneManager::awake()
{
	std::string imagePath = "assets/sprites/Home_screen.png";

	gameObject()->transform->setWorldPosition(Vector2(0, 0));
	
	// Background
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setParent(gameObject()->transform, false);

		auto sprite = go->addComponent<Sprite>();
		assert(sprite);
		bool success = sprite->loadImage(imagePath);
		assert(success);
		sprite->setRenderLayer("Background");
		sprite->setZIndex(0);
		sprite->setAllPivots(Vector2(0, 0));
		sprite->setClipRect(SDL_Rect{ 0, 225, 320, 224 });
	}

	// Game_title
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setParent(gameObject()->transform, false);
		go->transform->setLocalPosition(Vector2(162, (float)SCREEN_HEIGHT - 56));

		m_gameTitle = go->addComponent<SpriteSheet>();
		assert(m_gameTitle);
		bool success = m_gameTitle->loadImage(imagePath);
		assert(success);
		m_gameTitle->setRenderLayer("Main");
		m_gameTitle->setZIndex(0);
		m_gameTitle->setAllPivots(Vector2(0.5f, 0.5f));
		m_gameTitle->addAnimation("anim");
		// Note: Some rects are repeated because they need to be displayed for X times longer than the rest (where X is integer)
		for (int i = 0; i < 5; ++i)
		{
			m_gameTitle->addRectForAnimation("anim", Vector2(325, 5), 159, 83);
			m_gameTitle->addRectForAnimation("anim", Vector2(325, 90), 164, 74);
			m_gameTitle->addRectForAnimation("anim", Vector2(325, 165), 178, 52);
			m_gameTitle->addRectForAnimation("anim", Vector2(325, 220), 183, 18);
			m_gameTitle->addRectForAnimation("anim", Vector2(325, 240), 182, 18);
			m_gameTitle->addRectForAnimation("anim", Vector2(325, 260), 178, 51);
			m_gameTitle->addRectForAnimation("anim", Vector2(325, 315), 164, 73);
			m_gameTitle->addRectForAnimation("anim", Vector2(325, 390), 158, 83);
		}

		m_gameTitle->selectAnimation("anim", 7);
	}

	// Mammoth_head (to cover the game_title)
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setParent(gameObject()->transform, false);
		go->transform->setLocalPosition(Vector2(66, (float)SCREEN_HEIGHT - 86));

		auto sprite = go->addComponent<Sprite>();
		assert(sprite);
		bool success = sprite->loadImage(imagePath);
		assert(success);
		sprite->setRenderLayer("Main");
		sprite->setZIndex(1);
		sprite->setAllPivots(Vector2(0, 1));
		sprite->setClipRect(SDL_Rect{ 285, 110, 35, 17 });
	}

	// Robot_head (to cover the game_title)
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setParent(gameObject()->transform, false);
		go->transform->setLocalPosition(Vector2(219, (float)SCREEN_HEIGHT - 82));

		auto sprite = go->addComponent<Sprite>();
		assert(sprite);
		bool success = sprite->loadImage(imagePath);
		assert(success);
		sprite->setRenderLayer("Main");
		sprite->setZIndex(1);
		sprite->setAllPivots(Vector2(0, 1));
		sprite->setClipRect(SDL_Rect{ 285, 80, 30, 28 });
	}

	// Mammoth
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setParent(gameObject()->transform, false);
		go->transform->setLocalPosition(Vector2(66, (float)SCREEN_HEIGHT - 103));

		m_mammoth = go->addComponent<SpriteSheet>();
		assert(m_mammoth);
		bool success = m_mammoth->loadImage(imagePath);
		assert(success);
		m_mammoth->setRenderLayer("Main");
		m_mammoth->setZIndex(1);
		m_mammoth->setAllPivots(Vector2(0, 1));
		m_mammoth->addAnimation("anim");
		// Note: Some rects are repeated because they need to be displayed for X times longer than the rest (where X is integer)
		m_mammoth->addRectForAnimation("anim", Vector2( 0, 0), 36, 37);
		m_mammoth->addRectForAnimation("anim", Vector2(40, 0), 36, 37);
		m_mammoth->addRectForAnimation("anim", Vector2(80, 0), 36, 37);
		for (int i = 0; i < 2; ++i)
		{
			m_mammoth->addRectForAnimation("anim", Vector2(120, 0), 36, 37);
		}
		m_mammoth->addRectForAnimation("anim", Vector2(160, 0), 36, 37);
		m_mammoth->addRectForAnimation("anim", Vector2(200, 0), 36, 37);
		m_mammoth->addRectForAnimation("anim", Vector2(240, 0), 36, 37);
		m_mammoth->addRectForAnimation("anim", Vector2(280, 0), 36, 37);
		for (int i = 0; i < 10; ++i)
		{
			m_mammoth->addRectForAnimation("anim", Vector2(0, 40), 36, 37);
		}
		m_mammoth->addRectForAnimation("anim", Vector2( 40, 40), 36, 37);
		m_mammoth->addRectForAnimation("anim", Vector2( 80, 40), 36, 37);
		m_mammoth->addRectForAnimation("anim", Vector2(120, 40), 36, 37);
		m_mammoth->addRectForAnimation("anim", Vector2(160, 40), 36, 37);
		for (int i = 0; i < 7; ++i)
		{
			m_mammoth->addRectForAnimation("anim", Vector2(200, 40), 36, 37);
		}
		m_mammoth->addRectForAnimation("anim", Vector2(240, 40), 36, 37);
		m_mammoth->addRectForAnimation("anim", Vector2(280, 40), 36, 37);

		m_mammoth->selectAnimation("anim", 0);
	}

	// Character
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setParent(gameObject()->transform, false);
		go->transform->setLocalPosition(Vector2(241, (float)SCREEN_HEIGHT - 50));

		m_character = go->addComponent<SpriteSheet>();
		assert(m_character);
		bool success = m_character->loadImage(imagePath);
		assert(success);
		m_character->setRenderLayer("Main");
		m_character->setZIndex(1);
		m_character->setAllPivots(Vector2(0, 1));
		m_character->addAnimation("anim");
		// Note: Some rects are repeated because they need to be displayed for X times longer than the rest (where X is integer)
		m_character->addRectForAnimation("anim", Vector2(225, 120), 24, 21);
		m_character->addRectForAnimation("anim", Vector2(225, 145), 24, 21);
		m_character->addRectForAnimation("anim", Vector2(225, 170), 24, 21);
		m_character->addRectForAnimation("anim", Vector2(225, 195), 24, 21);

		m_character->selectAnimation("anim", 0);
	}

	// Robot_highlights
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setParent(gameObject()->transform, false);
		go->transform->setLocalPosition(Vector2(200, (float)SCREEN_HEIGHT - 83));

		m_robotHighlights = go->addComponent<SpriteSheet>();
		assert(m_robotHighlights);
		bool success = m_robotHighlights->loadImage(imagePath);
		assert(success);
		m_robotHighlights->setRenderLayer("Main");
		m_robotHighlights->setZIndex(1);
		m_robotHighlights->setAllPivots(Vector2(0, 1));
		m_robotHighlights->addAnimation("anim");
		// Note: Some rects are repeated because they need to be displayed for X times longer than the rest (where X is integer)
		m_robotHighlights->addRectForAnimation("anim", Vector2(5, 80), 106, 140);
		for (int i = 0; i < 14; ++i)
		{
			m_robotHighlights->addRectForAnimation("anim", Vector2(115, 80), 106, 140);
		}
		m_robotHighlights->addRectForAnimation("anim", Vector2(5, 80), 106, 140);

		m_robotHighlights->selectAnimation("anim", 0);
	}

	// Robot_eyes
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setParent(gameObject()->transform, false);
		go->transform->setLocalPosition(Vector2(223, (float)SCREEN_HEIGHT - 84));

		m_robotEyes = go->addComponent<SpriteSheet>();
		assert(m_robotEyes);
		bool success = m_robotEyes->loadImage(imagePath);
		assert(success);
		m_robotEyes->setRenderLayer("Main");
		m_robotEyes->setZIndex(1);
		m_robotEyes->setAllPivots(Vector2(0, 1));
		m_robotEyes->addAnimation("anim");
		// Note: Some rects are repeated because they need to be displayed for X times longer than the rest (where X is integer)
		m_robotEyes->addRectForAnimation("anim", Vector2(225,  80), 14, 16);
		m_robotEyes->addRectForAnimation("anim", Vector2(240,  80), 14, 16);
		m_robotEyes->addRectForAnimation("anim", Vector2(255,  80), 14, 16);
		m_robotEyes->addRectForAnimation("anim", Vector2(270,  80), 14, 16);
		m_robotEyes->addRectForAnimation("anim", Vector2(225, 100), 14, 16);
		m_robotEyes->addRectForAnimation("anim", Vector2(240, 100), 14, 16);
		m_robotEyes->addRectForAnimation("anim", Vector2(255, 100), 14, 16);
		m_robotEyes->addRectForAnimation("anim", Vector2(270, 100), 14, 16);
		// And back
		m_robotEyes->addRectForAnimation("anim", Vector2(270, 100), 14, 16);
		m_robotEyes->addRectForAnimation("anim", Vector2(255, 100), 14, 16);
		m_robotEyes->addRectForAnimation("anim", Vector2(240, 100), 14, 16);
		m_robotEyes->addRectForAnimation("anim", Vector2(225, 100), 14, 16);
		m_robotEyes->addRectForAnimation("anim", Vector2(270, 80), 14, 16);
		m_robotEyes->addRectForAnimation("anim", Vector2(255, 80), 14, 16);
		m_robotEyes->addRectForAnimation("anim", Vector2(240, 80), 14, 16);
		m_robotEyes->addRectForAnimation("anim", Vector2(225, 80), 14, 16);
		
		m_robotEyes->selectAnimation("anim", 0);
	}

	// Robot_shine
	m_robotShineStartPos = Vector2(214, (float)SCREEN_HEIGHT - 118);
	m_robotShineEndPos = Vector2(273, (float)SCREEN_HEIGHT - 157);
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setParent(gameObject()->transform, false);
		go->transform->setLocalPosition(m_robotShineStartPos);

		m_robotShine = go->addComponent<SpriteSheet>();
		assert(m_robotShine);
		bool success = m_robotShine->loadImage(imagePath);
		assert(success);
		m_robotShine->setRenderLayer("Main");
		m_robotShine->setZIndex(1);
		m_robotShine->setAllPivots(Vector2(0, 1));
		// Note: This animation should be played twice as fast as the others
		m_robotShine->addAnimation("anim");
		// Note: Some rects are repeated because they need to be displayed for X times longer than the rest (where X is integer)
		for (int i = 0; i < 7; ++i)
		{
			m_robotShine->addRectForAnimation("anim", Vector2(255, 120), 14, 14);
			m_robotShine->addRectForAnimation("anim", Vector2(255, 135), 14, 14);
			m_robotShine->addRectForAnimation("anim", Vector2(255, 150), 14, 14);
			m_robotShine->addRectForAnimation("anim", Vector2(255, 165), 14, 14);
		}
		for (int i = 0; i < 2; ++i)
		{
			m_robotShine->addRectForAnimation("anim", Vector2(255, 180), 14, 14);
			m_robotShine->addRectForAnimation("anim", Vector2(255, 195), 14, 14);
		}
		for (int i = 0; i < 32; ++i)
		{
			// Adding empty frames to the animation
			m_robotShine->addRectForAnimation("anim", Vector2(0, 0), 0, 0);
		}
		m_robotShine->selectAnimation("anim", 0);
	}

	// Lives_label
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setParent(gameObject()->transform, false);
		go->transform->setLocalPosition(Vector2(16, 16));

		auto livesLabel = go->addComponent<TextRenderer>();
		assert(livesLabel);
		bool success = livesLabel->loadFont(getFont("smallGray"));
		assert(success);
		livesLabel->setRenderLayer("UI");
		livesLabel->setAllPivots(Vector2(0, 0));
		livesLabel->setText("PLAYER");
	}

	// Lives_value
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setParent(gameObject()->transform, false);
		go->transform->setLocalPosition(Vector2(96, 16));

		m_livesValue = go->addComponent<TextRenderer>();
		assert(m_livesValue);
		bool success = m_livesValue->loadFont(getFont("smallGray"));
		assert(success);
		m_livesValue->setRenderLayer("UI");
		m_livesValue->setAllPivots(Vector2(1, 0));
		m_livesValue->setText("0");
	}

	// Copyright_symbol
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setParent(gameObject()->transform, false);
		go->transform->setLocalPosition(Vector2((float)SCREEN_WIDTH - 96, 16));

		auto sprite = go->addComponent<Sprite>();
		assert(sprite);
		bool success = sprite->loadImage("assets/sprites/UI.png");
		assert(success);
		sprite->setRenderLayer("UI");
		sprite->setAllPivots(Vector2(1, 0));
		sprite->setClipRect(SDL_Rect{ 96, 104, 8, 8 });
	}

	// Sega_label
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setParent(gameObject()->transform, false);
		go->transform->setLocalPosition(Vector2((float)SCREEN_WIDTH - 16, 16));

		auto segaLabel = go->addComponent<TextRenderer>();
		assert(segaLabel);
		bool success = segaLabel->loadFont(getFont("smallGray"));
		assert(success);
		segaLabel->setRenderLayer("UI");
		segaLabel->setAllPivots(Vector2(1, 0));
		segaLabel->setText("SEGA 1985");
	}

	// Insert_coins_prompt
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setParent(gameObject()->transform, false);
		go->transform->setLocalPosition(Vector2((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT - 96));
		
		m_insertCoinsPrompt = go->addComponent<TextRenderer>();
		assert(m_insertCoinsPrompt);
		bool success = m_insertCoinsPrompt->loadFont(getFont("smallRed"));
		assert(success);
		m_insertCoinsPrompt->setRenderLayer("UI");
		m_insertCoinsPrompt->setAllPivots(Vector2(0.5f, 1));
		m_insertCoinsPrompt->setText("INSERT COINS");
	}
	m_insertCoinsPrompt->gameObject()->setActive(true);

	// Push_start_prompt
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setParent(gameObject()->transform, false);
		go->transform->setLocalPosition(Vector2((float)SCREEN_WIDTH / 2, 72));

		m_pushStartPrompt = go->addComponent<TextRenderer>();
		assert(m_pushStartPrompt);
		bool success = m_pushStartPrompt->loadFont(getFont("smallGreen"));
		assert(success);
		m_pushStartPrompt->setRenderLayer("UI");
		m_pushStartPrompt->setAllPivots(Vector2(0.5f, 0));
		m_pushStartPrompt->setText("PUSH START BUTTON ");
	}
	m_pushStartPrompt->gameObject()->setActive(false);

	
	m_sfxCoin = Audio::LoadSFX("assets/audio/sfx/SFX - Coin.wav");
	assert(m_sfxCoin);
}


void HomeSceneManager::start()
{
	m_animationSpeed = 7.5f;
	m_gameTitle->playAnimation("anim", m_animationSpeed, false, 0);
	m_mammoth->playAnimation("anim", m_animationSpeed, true, 0);
	m_character->playAnimation("anim", m_animationSpeed, true, 0);
	m_robotHighlights->playAnimation("anim", m_animationSpeed, true, 0);
	m_robotEyes->playAnimation("anim", m_animationSpeed, true, 0);
	m_robotShine->playAnimation("anim", 2 * m_animationSpeed, true, 0);

	m_maxAnimationFrames = 32;
	m_totalAnimationCycleTimeMS = m_maxAnimationFrames / (m_animationSpeed / 1000);

	m_robotShineInMotion = false;
	m_gameTitleElapsedTime = 0;
	m_robotShineElapsedTime = 0;
	m_gameTitleScale = 0;

	m_playerLives = 0;
	m_promptsShowTime = 500;
	m_promptsHideTime = 500;
	m_promptsElapsedTime = 0;
	m_promptsShowing = true;
	m_livesValue->setText(std::to_string(m_playerLives));

	// Update gets called from start to avoid a 1-frame late start of the update in regards to the animations.
	update();
}


void HomeSceneManager::update()
{
	// Scale the Game_title
	{
		if (m_gameTitleScale < 1)
		{
			m_gameTitleScale = m_gameTitleElapsedTime / m_totalAnimationCycleTimeMS;
			m_gameTitleScale = m_gameTitleScale > 1 ? 1 : m_gameTitleScale;
			m_gameTitle->gameObject()->transform->setLocalScale(Vector2(m_gameTitleScale, m_gameTitleScale));
			m_gameTitleElapsedTime += Time::deltaTime();
		}
	}

	// Move the Robot_shine
	{
		if (!m_robotShineInMotion)
		{
			if (m_robotShine->getCurrentAnimationFrameIndex() == 0)
			{
				m_robotShineInMotion = true;
				m_robotShineElapsedTime = 0;
			}
		}
		// Separate if statement, because the first one might change the value of inMotion
		if (m_robotShineInMotion)
		{
			float u = 2 * m_robotShineElapsedTime / m_totalAnimationCycleTimeMS;
			//OutputLog("u: %f | elapsed: %f", u, m_robotShineElapsedTime);
			if (u <= 1)
			{
				Vector2 currPos = (1 - u) * m_robotShineStartPos + u * m_robotShineEndPos;
				m_robotShine->gameObject()->transform->setLocalPosition(currPos);
			}

			m_robotShineElapsedTime += Time::deltaTime();
			if (m_robotShine->getCurrentAnimationFrameIndex() == m_maxAnimationFrames)
			{
				m_robotShineInMotion = false;
			}
		}
	}

	// Receive user input
	{
		if (Input::getKeyDown(SDL_SCANCODE_Q))
		{
			m_insertCoinsPrompt->gameObject()->setActive(false);
			m_pushStartPrompt->gameObject()->setActive(true);
			m_playerLives += 3;
			Audio::PlaySFX(m_sfxCoin);
			m_livesValue->setText(std::to_string(m_playerLives));
		}

		if (m_playerLives > 0 && Input::getKeyDown(SDL_SCANCODE_LCTRL))
		{
			initial_player_lives = m_playerLives;
			Scenes::loadScene(1);
		}
	}

	// Show Insert_coins_prompt or Push_start_prompt
	{
		if (m_promptsElapsedTime >= (m_promptsShowTime + m_promptsHideTime))
		{
			m_promptsElapsedTime -= m_promptsShowTime + m_promptsHideTime;
		}

		bool wasShowing = m_promptsShowing;
		m_promptsShowing = m_promptsElapsedTime < m_promptsShowTime;
		if (m_promptsShowing != wasShowing)
		{
			togglePrompts(m_promptsShowing);
		}
		m_promptsElapsedTime += Time::deltaTime();
	}
}

void HomeSceneManager::togglePrompts(bool activeState)
{
	m_insertCoinsPrompt->setActive(activeState);
	m_pushStartPrompt->setActive(activeState);
}
