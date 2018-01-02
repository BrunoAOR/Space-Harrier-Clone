#include "PlayerShot.h"

#include <assert.h>
#include "Engine/gameConfig.h"
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Engine/SpriteSheet.h"
#include "Engine/API.h"
#include "Engine/Collider.h"
#include "PooledGameObject.h"
#include "FloorManager.h"


void PlayerShot::init(const Reference<FloorManager>& floorManager, Vector2 startPos)
{
	m_floorManager = floorManager;
	if (!m_spriteSheet)
	{
		m_spriteSheet = gameObject()->getComponent<SpriteSheet>();
	}
	if (!m_collider)
	{
		m_collider = gameObject()->getComponent<Collider>();
	}
	if (!m_poolHandler)
	{
		m_poolHandler = gameObject()->getComponent<PooledGameObject>();
	}
	
	assert(m_floorManager && m_spriteSheet && m_collider && m_poolHandler);

	m_collider->setActive(true);
	m_spriteSheet->playAnimation("shot", 16.0f);
	// Offset the startPos because the spritesheet has its pivot in the center
	startPos.y += m_spriteSheet->getCurrentAnimationFrameHeight() / 2.0f;
	gameObject()->transform->setWorldPosition(startPos);
	
	m_startScale = 2;
	m_endScale = 0.1f;
	m_shotDuration = 400;
	m_elapsedTime = 0;

	m_bounceDuration = 200;
	m_bounced = false;

	// Bounce distance
	int widthClearance = m_spriteSheet->getCurrentAnimationFrameWidth() + SCREEN_WIDTH;
	int heightClearance = m_spriteSheet->getCurrentAnimationFrameHeight() + SCREEN_HEIGHT;
	m_bounceClearanceDistance = sqrtf((float)(widthClearance * widthClearance + heightClearance * heightClearance));
}


void PlayerShot::update()
{
	if (m_elapsedTime > m_shotDuration)
	{
		m_poolHandler->returnToPool();
	}
	
	if (m_bounced)
	{
		bounce();
	}
	else
	{
		fly();
	}

	m_elapsedTime += Time::deltaTime();
}


void PlayerShot::bounceOut()
{
	if (m_bounced)
	{
		return;
	}

	m_bounced = true;
	m_elapsedTime = 0;
	m_collider->setActive(false);
	
	// Psuedo-random bounce direction based on the current game time
	m_bounceStart = gameObject()->transform->getWorldPosition();	
	m_bounceTarget.x = cosf((float)Time::time()) * m_bounceClearanceDistance;
	m_bounceTarget.y = sinf((float)Time::time()) * m_bounceClearanceDistance;
}


void PlayerShot::destroy()
{
	m_poolHandler->returnToPool();
}


void PlayerShot::fly()
{
	Vector2 scale;
	float normalizedProgress = m_elapsedTime / m_shotDuration;
	float correctedProgress = m_floorManager->getNormalizedYPos(1 - normalizedProgress);
	correctedProgress = correctedProgress > 0 ? correctedProgress : 0;
	scale.y = scale.x = (1 - correctedProgress) * m_startScale + correctedProgress * m_endScale;
	gameObject()->transform->setLocalScale(scale);

	int zIndex = (int)((1 - normalizedProgress) * 100);
	m_collider->zIndex = zIndex;
	m_spriteSheet->setZIndex(zIndex);
}


void PlayerShot::bounce()
{
	float u = m_elapsedTime / m_bounceDuration;
	Vector2 currentPos = (1 - u) * m_bounceStart + u * m_bounceTarget;
	gameObject()->transform->setWorldPosition(currentPos);
}
