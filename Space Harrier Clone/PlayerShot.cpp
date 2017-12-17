#include "PlayerShot.h"

#include <assert.h>
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Engine/SpriteSheet.h"
#include "Engine/Vector2.h"
#include "Engine/API.h"
#include "Engine/Collider.h"
#include "PooledGameObject.h"
#include "FloorManager.h"


void PlayerShot::init(const Vector2& startPos, const Reference<FloorManager>& floorManager)
{
	if (!m_spriteSheet)
	{
		m_spriteSheet = gameObject()->getComponent<SpriteSheet>();
	}
	if (!m_poolHandler)
	{
		m_poolHandler = gameObject()->getComponent<PooledGameObject>();
	}
	if (!m_collider)
	{
		m_collider = gameObject()->getComponent<Collider>();
	}
	m_floorManager = floorManager;
	assert(m_spriteSheet && m_poolHandler && m_collider && m_floorManager);

	gameObject()->transform->setWorldPosition(startPos);
	m_spriteSheet->playAnimation("shot", 16.0f);

	m_startScale = 2;
	m_endScale = 0.1f;
	m_shotDuration = 400;
	m_elapsedTime = 0;
}


void PlayerShot::update()
{
	if (m_elapsedTime > m_shotDuration)
	{
		m_poolHandler->returnToPool();
	}
	
	Vector2 scale;
	float normalizedProgress = m_elapsedTime / m_shotDuration;
	float correctedProgress = m_floorManager->getNormalizedYPos(1 - normalizedProgress);
	correctedProgress = correctedProgress > 0 ? correctedProgress : 0;
	scale.y = scale.x = (1 - correctedProgress) * m_startScale + correctedProgress * m_endScale;
	gameObject()->transform->setLocalScale(scale);

	m_collider->zIndex = (int)((1 - normalizedProgress) * 100);

	m_elapsedTime += Time::deltaTime();
	
}


void PlayerShot::onTriggerEnter(Reference<Collider>& other)
{
	OutputLog("Hit something");
	m_poolHandler->returnToPool();
}
