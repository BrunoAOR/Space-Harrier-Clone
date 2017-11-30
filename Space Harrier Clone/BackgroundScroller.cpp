#include "BackgroundScroller.h"

#include <assert.h>
#include "Engine/API.h"
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "FloorManager.h"
#include "Utils.h"


void BackgroundScroller::init(const Reference<FloorManager>& floorManager, const std::string & texturePath, float speedModifier, int zIndex)
{
	m_floorManager = floorManager;
	m_backgroundSpeedModifier = speedModifier;

	bool success = true;

	gameObject()->transform->setWorldPosition(Vector2(0, 0));

	m_bg1 = GameObject::createNew();
	if (m_bg1)
	{
		m_bg1->transform->setParent(gameObject()->transform, false);
		m_bg1->transform->setLocalPosition(Vector2(0, 0));
		auto sprite = m_bg1->addComponent<Sprite>();
		if (sprite)
		{
			sprite->setAllPivots(Vector2(0, 0));
			sprite->setRenderLayer("Background");
			sprite->setZIndex(zIndex);
			success &= sprite->loadImage(texturePath);
			m_spriteWidth = sprite->getWidth();
		}
		else
		{
			success = false;
		}
	}
	else
	{
		success = false;
	}

	m_bg2 = GameObject::createNew();
	if (m_bg2)
	{
		m_bg2->transform->setParent(gameObject()->transform, false);
		m_bg2->transform->setLocalPosition(Vector2(0, 0));
		auto sprite = m_bg2->addComponent<Sprite>();
		if (sprite)
		{
			sprite->setAllPivots(Vector2(0, 0));
			sprite->setRenderLayer("Background");
			sprite->setZIndex(zIndex);
			success &= sprite->loadImage(texturePath);
		}
		else
		{
			success = false;
		}
	}
	else
	{
		success = false;
	}

	m_position = gameObject()->transform->getLocalPosition();
	assert(m_floorManager && success);
}


void BackgroundScroller::update()
{
	m_position.y = (float)(m_floorManager->getCurrentFloorHeight());

	float floorSpeed = m_floorManager->getCurrentHorizontalSpeed();
	float pixelDisplacement = floorSpeed * Time::deltaTime() * 0.001f * m_backgroundSpeedModifier;
	if (pixelDisplacement)
	{
		m_position.x += pixelDisplacement;
		if (m_position.x > m_spriteWidth)
		{
			m_position.x -= m_spriteWidth;
		}
		else if (m_position.x < -m_spriteWidth)
		{
			m_position.x += m_spriteWidth;
		}

		if (m_position.x >= 0)
		{
			m_bg2->transform->setLocalPosition(Vector2((float)-m_spriteWidth, 0));
		}
		else
		{
			m_bg2->transform->setLocalPosition(Vector2((float)m_spriteWidth, 0));
		}
	}
	gameObject()->transform->setLocalPosition(m_position);
}
