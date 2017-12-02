#include "Player.h"

#include <assert.h>
#include "Engine/gameConfig.h"
#include "Engine/API.h"
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Engine/Sprite.h"
#include "Engine/SpriteSheet.h"
#include "Utils.h"


void Player::init(const Reference<GameObject>& characterGo, const Reference<GameObject> shadowGo)
{
	m_shadowGo = shadowGo;
	m_characterGo = characterGo;
	m_spriteSheet = characterGo->getComponent<SpriteSheet>();
	assert(m_characterGo && m_shadowGo && m_spriteSheet);

	m_motionSpeed = 1.0f / 900; // One normalized screen dimension (could be height or width) in 900 milliseconds
	// x-coordinates-related fields
	m_minX = -0.42f;
	m_midX = 0;
	m_maxX = 0.42f;
	m_xTarget = m_midX;

	// y-coordinates-related fields
	m_minY = 0;
	m_midY = 0.35f;
	m_maxY = 0.76f;
	m_yTarget = m_midY;
}


void Player::start()
{
	gameObject()->transform->setLocalPosition(Vector2(0, 0));
	m_currentNormalizedPosition.x = m_midX;
	m_currentNormalizedPosition.y = m_minY;
	m_shadowGo->transform->setLocalPosition(Vector2(m_midX * SCREEN_WIDTH, m_minY * SCREEN_HEIGHT));
	m_characterGo->transform->setLocalPosition(Vector2(m_midX * SCREEN_WIDTH, m_minY * SCREEN_HEIGHT));
	m_spriteSheet->setAnimationSpeed(16);
	m_spriteSheet->playAnimation("run");
	m_currentAnimation = "run";
	m_sfxOuch = Audio::LoadSFX("assets/audio/SFX - Voice - Aaaaargh.wav");
	m_m1 = Audio::LoadMusic("assets/audio/S1 MOOT Boss (Skyra).wav");
	m_m2 = Audio::LoadMusic("assets/audio/Theme.wav");
}


void Player::update()
{
	float normalizedRequestedX;
	float normalizedRequestedY;
	handleInput(normalizedRequestedX, normalizedRequestedY);
	move(normalizedRequestedX, normalizedRequestedY);
	updateAnimation();
}


void Player::handleInput(float & normalizedRequestedX, float & normalizedRequestedY) const
{
	if (Input::getKeyDown(SDL_SCANCODE_LCTRL))
	{
		Audio::PlaySFX(m_sfxOuch);
	}
	if (Input::getKeyDown(SDL_SCANCODE_1))
	{
		Audio::PlayMusic(m_m1);
	}
	if (Input::getKeyDown(SDL_SCANCODE_2))
	{
		Audio::PlayMusic(m_m2);
	}

	normalizedRequestedX = m_midX;
	if (Input::getKey(SDL_SCANCODE_LEFT))
	{
		normalizedRequestedX = m_minX;
	}
	if (Input::getKey(SDL_SCANCODE_RIGHT))
	{
		normalizedRequestedX = m_maxX;
	}

	normalizedRequestedY = m_midY;
	if (Input::getKey(SDL_SCANCODE_DOWN))
	{
		normalizedRequestedY = m_minY;
	}
	if (Input::getKey(SDL_SCANCODE_UP))
	{
		normalizedRequestedY = m_maxY;
	}
}

void Player::move(float normalizedRequestedX, float normalizedRequestedY)
{
	// Get motion directions
	int xDirection = normalizedRequestedX - m_currentNormalizedPosition.x > 0 ? 1 : (normalizedRequestedX - m_currentNormalizedPosition.x < 0 ? -1 : 0);
	int yDirection = normalizedRequestedY - m_currentNormalizedPosition.y > 0 ? 1 : (normalizedRequestedY - m_currentNormalizedPosition.y < 0 ? -1 : 0);

	// Modify currentPosition (clamp so we don't overshoot the requested position)
	m_currentNormalizedPosition.x = clamp(m_currentNormalizedPosition.x + xDirection * m_motionSpeed * Time::deltaTime(), m_currentNormalizedPosition.x, normalizedRequestedX);
	m_currentNormalizedPosition.y = clamp(m_currentNormalizedPosition.y + yDirection * m_motionSpeed * Time::deltaTime(), m_currentNormalizedPosition.y, normalizedRequestedY);

	// Apply the modified position to the corresponding transform (x moves this GO while y moves the characterGp
	Vector2 pos(m_currentNormalizedPosition.x * SCREEN_WIDTH, m_currentNormalizedPosition.y * SCREEN_HEIGHT);

	Vector2 goPos = gameObject()->transform->getLocalPosition();
	goPos.x = pos.x;
	gameObject()->transform->setLocalPosition(goPos);

	Vector2 charPos = m_characterGo->transform->getLocalPosition();
	charPos.y = pos.y;
	m_characterGo->transform->setLocalPosition(charPos);
}


void Player::updateAnimation()
{
	std::string requestedAnimation = "";
	// Decide between run of a version of fly
	if (m_currentNormalizedPosition.y == m_minY)
	{
		requestedAnimation = "run";
	}
	else
	{
		// Decide between flying animations
		float normalizedXPos = m_currentNormalizedPosition.x;
		if (normalizedXPos == m_minX)
		{
			requestedAnimation = "flyLeft";
		}
		else if (normalizedXPos == m_maxX)
		{
			requestedAnimation = "flyRight";
		}
		else if (normalizedXPos < (m_minX - m_midX) / 2.0f)
		{
			requestedAnimation = "flyCenterLeft";
		}
		else if (normalizedXPos > (m_midX - m_maxX) / 2.0f)
		{
			requestedAnimation = "flyCenterRight";
		}
		else
		{
			requestedAnimation = "flyMid";
		}
	}

	// Play new animation if required
	if (requestedAnimation != m_currentAnimation)
	{
		m_currentAnimation = requestedAnimation;
		m_spriteSheet->playAnimation(m_currentAnimation);
	}
}
