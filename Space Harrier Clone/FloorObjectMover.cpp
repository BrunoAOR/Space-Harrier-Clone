#include "FloorObjectMover.h"

#include <assert.h>
#include "Engine/API.h"
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Engine/Collider.h"
#include "PooledGameObject.h"
#include "FloorManager.h"
#include "FloorObjectType.h"


void FloorObjectMover::init(const Reference<FloorManager>& floorManager, FloorObjectType type, float startXPos, float normalizedStartProgress, float normalizedEndProgress, float startScale, float endScale)
{
	m_floorManager = floorManager;
	m_floorObjectType = type;
	if (!m_poolHandler)
	{
		m_poolHandler = gameObject()->getComponent<PooledGameObject>();
	}
	if (!m_collider)
	{
		m_collider = gameObject()->getComponent<Collider>();
	}
	if (!m_sprite)
	{
		m_sprite = gameObject()->getComponent<Sprite>();
	}
	assert(m_floorManager && m_floorObjectType != FloorObjectType::UNDEFINED && m_poolHandler && m_collider && m_sprite);
	m_startXPos = startXPos;
	m_normalizedStartProgress = normalizedStartProgress;
	m_normalizedEndProgress = normalizedEndProgress;
	m_startScale = startScale;
	m_endScale = endScale;
	m_normalizedStartYPos = m_floorManager->getNormalizedYPos(m_normalizedStartProgress);
	m_collider->zIndex = 0;
}

void FloorObjectMover::restart()
{
	assert(m_floorManager && m_poolHandler && m_collider && m_sprite);
	m_fullMotionDuration = m_floorManager->getFullMotionDuration();
	m_elapsedTime = m_fullMotionDuration * m_normalizedStartProgress;
	adjustScale(m_normalizedStartProgress);
	adjustPosition(m_normalizedStartProgress);
	m_sprite->setActive(true);
}


FloorObjectType FloorObjectMover::getType() const
{
	return m_floorObjectType;
}


void FloorObjectMover::update()
{
	if (m_floorManager->freezeAtBottom)
	{
		return;
	}
	// Calculate start time correcting for the normalizedStartProgress
	m_elapsedTime += Time::deltaTime();
	float normalizedCurrentProgress = m_elapsedTime / m_fullMotionDuration;
	// Destroy gameObject if motion is finished
	if (normalizedCurrentProgress > m_normalizedEndProgress)
	{
		m_poolHandler->returnToPool();
		return;
	}

	m_collider->zIndex = (int)(normalizedCurrentProgress * 100);
	adjustScale(normalizedCurrentProgress);
	adjustPosition(normalizedCurrentProgress);
}


void FloorObjectMover::adjustScale(float normalizedCurrentProgress)
{
	Vector2 scale = gameObject()->transform->getLocalScale();
	float interpolatedProgress = 1 - m_floorManager->getNormalizedYPos(normalizedCurrentProgress);
	scale.y = scale.x = (1 - interpolatedProgress) * m_startScale + interpolatedProgress * m_endScale;
	gameObject()->transform->setLocalScale(scale);
}


void FloorObjectMover::adjustPosition(float normalizedCurrentProgress)
{
	float normalizedYPosition = m_floorManager->getNormalizedYPos(normalizedCurrentProgress);
	// For y
	int floorSize = m_floorManager->getCurrentFloorHeight();
	float yPos = (floorSize * normalizedYPosition);
	// For x
	// Get xPos for current referenceStartX
	float xPos = m_floorManager->getXCoordinateForYPos(m_startXPos, m_normalizedStartYPos, normalizedYPosition);
	// Shift the position based on current speed of horizontal shifting
	xPos += m_floorManager->getXSpeedForYPos(normalizedYPosition) * Time::deltaTime() * 0.001f;
	// Recalculate the referenceStartX for future calculations
	m_startXPos = m_floorManager->getXCoordinateForYPos(xPos, normalizedYPosition, m_normalizedStartYPos);

	//xPos += m_xPosSpeedOffset;
	//OutputLog("%f gives %f", interpolatedProgress, m_xPosSpeedOffset);
	// Update
	Vector2 currentPos = gameObject()->transform->getLocalPosition();
	currentPos.x = xPos;
	currentPos.y = yPos;
	gameObject()->transform->setLocalPosition(currentPos);
}
