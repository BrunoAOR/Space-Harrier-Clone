#include "Explosion.h"

#include "Engine/GameObject.h"
#include "Engine/SpriteSheet.h"
#include "FloorObjectMover.h"


void Explosion::init(const Reference<FloorManager>& floorManager, float startXPos, float normalizedStartProgress, float normalizedEndProgress, float startScale, float endScale, bool shouldLoopAnimation)
{
	if (!m_floorObjectMover)
	{
		m_floorObjectMover = gameObject()->getComponent<FloorObjectMover>();
	}
	if (!m_spriteSheet)
	{
		m_spriteSheet = gameObject()->getComponent<SpriteSheet>();
	}
	assert(m_floorObjectMover && m_spriteSheet);
	m_floorObjectMover->init(floorManager, startXPos, normalizedStartProgress, normalizedEndProgress, startScale, endScale);
	
	m_spriteSheet->playAnimation("explosion", 8.0f, shouldLoopAnimation);
}
