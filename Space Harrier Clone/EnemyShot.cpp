#include "EnemyShot.h"

#include <assert.h>
#include "Engine/API.h"
#include "Engine/GameObject.h"
#include "Engine/SpriteSheet.h"
#include "Engine/Collider.h"
#include "PooledGameObject.h"
#include "FloorManager.h"
#include "Player.h"
#include "MessengerEventType.h"
#include "Messenger.h"


void EnemyShot::init(const Reference<FloorManager>& floorManager, const Vector2& startPos, float normalizedStartDepth, const Vector2& targetPos, float normalizedTargetDepth)
{
	if (!m_spriteSheet)
	{
		m_spriteSheet = gameObject()->getComponentInChildren<SpriteSheet>();
	}
	if (!m_collider)
	{
		m_collider = gameObject()->getComponentInChildren<Collider>();
	}
	if (!m_poolHandler)
	{
		m_poolHandler = gameObject()->getComponent<PooledGameObject>();
	}
	assert(m_spriteSheet && m_collider && m_poolHandler);

	m_floorManager = floorManager;
	assert(m_floorManager);

	m_spriteSheet->playAnimation("shot", 16.0f);

	m_startPos = startPos;
	m_targetPos = targetPos;

	gameObject()->transform->setWorldPosition(m_startPos);

	m_normalizedStartProgress = 1 - normalizedStartDepth;
	m_fullMotionDuration = m_floorManager->getFullMotionDuration();
	m_elapsedTime = 0;

	update();
}


void EnemyShot::onDestroy()
{
	Messenger::removeListener(this, MessengerEventType::PLAYER_DEAD);
	Messenger::removeListener(this, MessengerEventType::PLAYER_REVIVED);
}


void EnemyShot::awake()
{
	if (!m_spriteSheet)
	{
		m_spriteSheet = gameObject()->getComponentInChildren<SpriteSheet>();
	}
	if (!m_collider)
	{
		m_collider = gameObject()->getComponentInChildren<Collider>();
	}
	if (!m_poolHandler)
	{
		m_poolHandler = gameObject()->getComponent<PooledGameObject>();
	}
	assert(m_spriteSheet && m_collider && m_poolHandler);

	Messenger::addListener(this, MessengerEventType::PLAYER_DEAD);
	Messenger::addListener(this, MessengerEventType::PLAYER_REVIVED);
}


void EnemyShot::update()
{
	int correctedElapsedTime = m_elapsedTime + (int)(m_normalizedStartProgress * m_fullMotionDuration);
	if (correctedElapsedTime >= m_fullMotionDuration * 0.95f)
	{
		m_poolHandler->returnToPool();
	}

	float normalizedProgress = correctedElapsedTime / (float)m_fullMotionDuration;
	float normalizedCorrectedProgress = m_floorManager->getNormalizedYPos(normalizedProgress);

	// The scale reaches 1 when the shot reaches the closest point (getNormalizedYPos returns 0 at this point)
	Vector2 scale;
	scale.y = scale.x = (1 - normalizedCorrectedProgress);
	gameObject()->transform->setLocalScale(scale);

	// Move the main Game Object (shadow-holding) and the spritesheet-holding gameObjects
	float interpolationProgress = m_elapsedTime / (m_fullMotionDuration - (m_normalizedStartProgress * m_fullMotionDuration));
	Vector2 shotPos = (1 - interpolationProgress) * m_startPos + interpolationProgress * m_targetPos;
	
	Vector2 shadowPos = Vector2(shotPos.x, normalizedCorrectedProgress * m_floorManager->getCurrentFloorHeight());

	gameObject()->transform->setWorldPosition(shadowPos);
	m_spriteSheet->gameObject()->transform->setWorldPosition(shotPos);

	// Update zIndexes
	int zIndex = (int)((1 - normalizedCorrectedProgress) * 100);
	m_collider->zIndex = zIndex;
	m_spriteSheet->setZIndex(zIndex);

	// Update m_elapsedTime for next update if allowed
	if (m_shouldFreezeInPlace)
	{
		if (!m_floorManager->freezeAtBottom)
		{
			m_shouldFreezeInPlace = false;
		}
	}
	else
	{
		m_elapsedTime += Time::deltaTime();
	}
}


void EnemyShot::onTriggerEnter(Reference<Collider>& other)
{
	// Note: EnemyShot (collisionLayer) can only collide againts the Player layer, so it's known that this collision occured against the Player
	if (!other->gameObject()->getComponentInParent<Player>()->isAnimatingDeath())
	{
		// So, the shot has just killed the player and should freeze in position
		m_shouldFreezeInPlace = true;
	}
}


void EnemyShot::eventsCallback(MessengerEventType eventType)
{
	if (eventType == MessengerEventType::PLAYER_DEAD)
	{
		m_spriteSheet->pauseAnimation();
	}
	else if (eventType == MessengerEventType::PLAYER_REVIVED)
	{
		m_spriteSheet->resumeAnimation();
	}
}
