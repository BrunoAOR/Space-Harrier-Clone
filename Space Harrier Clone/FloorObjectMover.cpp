#include "FloorObjectMover.h"

#include <assert.h>
#include "Engine/API.h"
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Engine/Collider.h"
#include "PooledGameObject.h"
#include "FloorManager.h"
#include "FloorObjectType.h"
#include "PlayerShot.h"
#include "Explosion.h"


void FloorObjectMover::init(const Reference<FloorManager>& floorManager, float startXPos, float normalizedStartProgress, float normalizedEndProgress, float startScale, float endScale)
{
	m_floorManager = floorManager;
	if (!m_poolHandler)
	{
		m_poolHandler = gameObject()->getComponent<PooledGameObject>();
	}
	if (!m_collider)
	{
		m_collider = gameObject()->getComponentInChildren<Collider>();
	}
	assert(m_floorManager && m_floorObjectType != FloorObjectType::UNDEFINED && m_poolHandler);
	
	m_startXPos = startXPos;
	m_normalizedStartProgress = normalizedStartProgress;
	m_normalizedEndProgress = normalizedEndProgress;
	m_startScale = startScale;
	m_endScale = endScale;
	m_normalizedStartYPos = m_floorManager->getNormalizedYPos(m_normalizedStartProgress);

	m_fullMotionDuration = m_floorManager->getFullMotionDuration();
	m_elapsedTime = m_fullMotionDuration * m_normalizedStartProgress;
	adjustScale(m_normalizedStartProgress);
	adjustPosition(m_normalizedStartProgress);
	if (m_collider)
	{
		m_collider->zIndex = 0;
	}
}


FloorObjectType FloorObjectMover::getType() const
{
	return m_floorObjectType;
}


void FloorObjectMover::setType(FloorObjectType type)
{
	m_floorObjectType = type;
}


void FloorObjectMover::setupExplosion(Reference<Explosion>& explosion)
{
	float normalizedCurrentProgress = m_elapsedTime / m_fullMotionDuration;
	float interpolatedProgress = 1 - m_floorManager->getNormalizedYPos(normalizedCurrentProgress);
	float currentScale = (1 - interpolatedProgress) * m_startScale + interpolatedProgress * m_endScale;
	explosion->init(m_floorManager, gameObject()->transform->getLocalPosition().x, normalizedCurrentProgress, m_normalizedEndProgress, currentScale, m_endScale);
}


void FloorObjectMover::update()
{
	if (m_normalizedStartProgress > 0.3f)
	{
		int i = 3;
	}
	if (m_floorManager->freezeAtBottom)
	{
		return;
	}
	// Calculate elapsed time correcting for the normalizedStartProgress
	m_elapsedTime += Time::deltaTime();
	float normalizedCurrentProgress = m_elapsedTime / m_fullMotionDuration;
	// Destroy gameObject if motion is finished
	if (normalizedCurrentProgress > m_normalizedEndProgress)
	{
		m_poolHandler->returnToPool();
		return;
	}

	if (m_collider)
	{
		m_collider->zIndex = (int)(normalizedCurrentProgress * 100);
	}
	adjustScale(normalizedCurrentProgress);
	adjustPosition(normalizedCurrentProgress);
}


void FloorObjectMover::adjustScale(float normalizedCurrentProgress)
{
	Vector2 scale;
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
