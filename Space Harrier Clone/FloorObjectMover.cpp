#include "FloorObjectMover.h"

#include <assert.h>
#include "Engine/API.h"
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "PooledGameObject.h"


void FloorObjectMover::init(const Reference<FloorManager>& floorManager, float startXPos, float normalizedStartProgress, float normalizedEndProgress, float startScale, float endScale)
{
	m_floorManager = floorManager;
	m_poolHandler = gameObject()->getComponent<PooledGameObject>();
	assert(m_floorManager && m_poolHandler);
	m_startXPos = startXPos;
	m_normalizedStartProgress = normalizedStartProgress;
	m_normalizedEndProgress = normalizedEndProgress;
	m_startScale = startScale;
	m_endScale = endScale;
	m_normalizedStartYPos = m_floorManager->getNormalizedYPos(m_normalizedStartProgress);
}

void FloorObjectMover::restart()
{
	assert(m_floorManager);
	m_fullMotionDuration = m_floorManager->getFullMotionDuration();
	m_startTime = Time::time();
	adjustScale(m_normalizedStartProgress);
	adjustPosition(m_normalizedStartProgress);
	gameObject()->getComponent<Sprite>()->setActive(true);
}


void FloorObjectMover::update()
{
	auto t = gameObject()->transform.get();
	// Calculate start time correcting for the normalizedStartProgress
	float elapsedTime = Time::time() - m_startTime + m_fullMotionDuration * m_normalizedStartProgress;
	float normalizedCurrentProgress = elapsedTime / m_fullMotionDuration;
	// Destroy gameObject if motion is finished
	if (normalizedCurrentProgress > m_normalizedEndProgress)
	{
		m_poolHandler->returnToPool();
	}

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
