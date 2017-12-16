#include "Player.h"

#include <assert.h>
#include "Engine/gameConfig.h"
#include "Engine/API.h"
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Engine/Sprite.h"
#include "Engine/SpriteSheet.h"
#include "Engine/Collider.h"
#include "Utils.h"
#include "FloorManager.h"
#include "FloorObjectMover.h"
#include "FloorObjectType.h"
#include "AnimationSection.h"


Player::~Player()
{
	delete m_dieAnimation;
	m_dieAnimation = nullptr;
}


void Player::init(const Reference<GameObject>& characterGo, const Reference<GameObject>& shadowGo)
{
	m_shadowGo = shadowGo;
	m_characterGo = characterGo;
	m_spriteSheet = characterGo->getComponent<SpriteSheet>();
	assert(m_characterGo && m_shadowGo && m_spriteSheet);

	m_state = PlayerState::MOVE;

	m_motionSpeed = 1.0f / 1300; // One normalized screen dimension (could be height or width) divided by the time taken to go over it
	// x-coordinates-related fields
	m_minX = -0.42f;
	m_midX = 0;
	m_maxX = 0.42f;
	m_xTarget = m_midX;

	// y-coordinates-related fields
	m_minY = 0;
	m_midY = 0.35f;
	m_maxY = 0.71f;
	m_yTarget = m_midY;

	// Die Animation
	m_dieAnimation = new TimedAnimation(getDieAnimationInfo(), m_spriteSheet);
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
	switch (m_state)
	{
	case PlayerState::STOP:
		break;
	case PlayerState::MOVE:
		float normalizedRequestedX;
		float normalizedRequestedY;
		handleInput(normalizedRequestedX, normalizedRequestedY);
		move(normalizedRequestedX, normalizedRequestedY);
		moveAnimationUpdate();
		break;
	case PlayerState::SHORT_TRIP:
		m_state = PlayerState::SHORT_TRIP;
		tripUpdate();
		break;
	case PlayerState::LONG_TRIP:
		m_state = PlayerState::LONG_TRIP;
		tripUpdate();
		break;
	case PlayerState::DIE:
		dieUpdate();
		break;
	case PlayerState::POST_DIE:
		postDieUpdate();
		break;
	default:
		break;
	}
}


void Player::onTriggerEnter(Reference<Collider>& other)
{
	Reference<FloorObjectMover> fom = other->gameObject()->getComponentInParent<FloorObjectMover>();
	if (fom)
	{
		handleFOMCollision(fom);
	}
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


void Player::move(float normalizedRequestedX, float normalizedRequestedY, bool horizontalOnly, bool verticalOnly)
{
	if (!verticalOnly)
	{
		// Get motion direction
		int xDirection = normalizedRequestedX - m_currentNormalizedPosition.x > 0 ? 1 : (normalizedRequestedX - m_currentNormalizedPosition.x < 0 ? -1 : 0);
		// Modify currentPosition (clamp so we don't overshoot the requested position)
		m_currentNormalizedPosition.x = clamp(m_currentNormalizedPosition.x + xDirection * m_motionSpeed * Time::deltaTime(), m_currentNormalizedPosition.x, normalizedRequestedX);
		float xPos = m_currentNormalizedPosition.x * SCREEN_WIDTH;

		// Apply the modified position to the corresponding transform (x moves this GO while y moves the characterGp)
		Vector2 goPos = gameObject()->transform->getLocalPosition();
		goPos.x = xPos;
		gameObject()->transform->setLocalPosition(goPos);
	}

	if (!horizontalOnly)
	{
		// Get motion direction
		int yDirection = normalizedRequestedY - m_currentNormalizedPosition.y > 0 ? 1 : (normalizedRequestedY - m_currentNormalizedPosition.y < 0 ? -1 : 0);
		// Modify currentPosition (clamp so we don't overshoot the requested position)
		m_currentNormalizedPosition.y = clamp(m_currentNormalizedPosition.y + yDirection * m_motionSpeed * Time::deltaTime(), m_currentNormalizedPosition.y, normalizedRequestedY);
		float yPos = m_currentNormalizedPosition.y * SCREEN_HEIGHT;

		// Apply the modified position to the corresponding transform (x moves this GO while y moves the characterGp)
		Vector2 charPos = m_characterGo->transform->getLocalPosition();
		charPos.y = yPos;
		m_characterGo->transform->setLocalPosition(charPos);
	}
}


void Player::moveAnimationUpdate()
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
		if (normalizedXPos < m_minX * 0.9f)
		{
			requestedAnimation = "flyLeft";
		}
		else if (normalizedXPos > m_maxX * 0.9f)
		{
			requestedAnimation = "flyRight";
		}
		else if (normalizedXPos < (m_midX + m_minX) / 2.0f)
		{
			requestedAnimation = "flyCenterLeft";
		}
		else if (normalizedXPos > (m_maxX + m_midX) / 2.0f)
		{
			requestedAnimation = "flyCenterRight";
		}
		else
		{
			requestedAnimation = "flyCenter";
		}
	}

	// Play new animation if required
	if (requestedAnimation != m_currentAnimation)
	{
		m_currentAnimation = requestedAnimation;
		m_spriteSheet->playAnimation(m_currentAnimation, 16.0f);
	}
}


void Player::tripUpdate()
{
	if (floorManager)
	{
		floorManager->stopHorizontal = true;
	}
	// Start animations
	if (m_state == PlayerState::SHORT_TRIP && m_currentAnimation != "shortTrip" || m_state == PlayerState::LONG_TRIP && m_currentAnimation != "longTrip")
	{
		if (m_state == PlayerState::SHORT_TRIP && m_currentAnimation != "shortTrip")
		{
			m_currentAnimation = "shortTrip";
		}
		else
		{
			m_currentAnimation = "longTrip";
		}
		m_spriteSheet->playAnimation(m_currentAnimation, 8.0f);
		Vector2 charPos = m_characterGo->transform->getLocalPosition();
		charPos.y = m_minY;
		m_characterGo->transform->setLocalPosition(charPos);
	}

	int currentFrame = m_spriteSheet->getCurrentAnimationFrameIndex();
	int framesCount = m_spriteSheet->getCurrentAnimationFrameCount();

	if (currentFrame == framesCount - 1)
	{
		if (floorManager)
		{
			floorManager->stopHorizontal = false;
		}
		m_state = PlayerState::MOVE;
	}
}


void Player::dieUpdate()
{
	if (m_dieAnimation->isFinished())
	{
		m_state = PlayerState::POST_DIE;
		return;
	}
	Vector2 currentCharPos = m_characterGo->transform->getLocalPosition();
	m_dieAnimation->update(currentCharPos.y);
	m_characterGo->transform->setLocalPosition(currentCharPos);
}


void Player::postDieUpdate()
{
	if (m_postDieElapsedTime == INT_MIN)
	{
		m_postDieElapsedTime = -(int)Time::deltaTime();
		m_spriteSheet->playAnimation("flyCenter", 16.0f);
		if (floorManager)
		{
			floorManager->freezeAtBottom = true;
		}
		// LOSE LIFE HERE
	}
	
	// Limited motion
	float normalizedRequestedX;
	float normalizedRequestedY;
	handleInput(normalizedRequestedX, normalizedRequestedY);
	

	m_postDieElapsedTime += Time::deltaTime();
	float pastCyclesTime = 0;

	// Blinking and limited motion (horizontal only) starts
	for (int i = 0; i < POST_DIE_BLINK_FLOOR_CYCLE_COUNT; ++i)
	{
		if (m_postDieElapsedTime - pastCyclesTime < POST_DIE_BLINK_CYCLE_DURATION)
		{
			if (m_postDieElapsedTime - pastCyclesTime < POST_DIE_BLINK_CYCLE_DURATION / 2)
			{
				m_spriteSheet->gameObject()->transform->setLocalScale(Vector2(0, 0));
			}
			else
			{
				m_spriteSheet->gameObject()->transform->setLocalScale(Vector2(1, 1));
			}
			move(normalizedRequestedX, normalizedRequestedY, true);
			return;
		}
		pastCyclesTime += POST_DIE_BLINK_CYCLE_DURATION;
	}
	
	// Blinking and free motion starts (free motion)
	if (floorManager)
	{
		floorManager->freezeAtBottom = false;
	}

	move(normalizedRequestedX, normalizedRequestedY);
	moveAnimationUpdate();
	for (int i = 0; i < POST_DIE_BLINK_FREE_CYCLE_COUNT; ++i)
	{
		// Off-part of the blink
		if (m_postDieElapsedTime - pastCyclesTime < POST_DIE_BLINK_CYCLE_DURATION / 2)
		{
			m_spriteSheet->gameObject()->transform->setLocalScale(Vector2(0, 0));
			return;
		}
		// On-part of the blink
		else if (m_postDieElapsedTime - pastCyclesTime < POST_DIE_BLINK_CYCLE_DURATION)
		{
			m_spriteSheet->gameObject()->transform->setLocalScale(Vector2(1, 1));
			return;
		}
		pastCyclesTime += POST_DIE_BLINK_CYCLE_DURATION;
	}

	// postDie is finished
	m_spriteSheet->gameObject()->transform->setLocalScale(Vector2(1, 1));
	m_postDieElapsedTime = INT_MIN;
	m_state = PlayerState::MOVE;	
}


void Player::handleFOMCollision(const Reference<FloorObjectMover>& fom)
{
	switch (fom->getType())
	{
	case FloorObjectType::SHORT_TRIP:
		m_state = PlayerState::SHORT_TRIP;
		break;
	case FloorObjectType::LONG_TRIP:
		m_state = PlayerState::LONG_TRIP;
		break;
	case FloorObjectType::DIE:
		if (m_state != PlayerState::DIE && m_state != PlayerState::POST_DIE) {
			m_currentNormalizedPosition.y = m_minY;
			m_spriteSheet->selectAnimation("die", 0);
			m_dieAnimation->start(m_characterGo->transform->getLocalPosition().y);
			if (floorManager)
			{
				floorManager->freezeAtBottom = true;
			}
			m_state = PlayerState::DIE;
		}
		break;
	case FloorObjectType::UNDEFINED:
	default:
		assert(false);
		break;
	}
}
