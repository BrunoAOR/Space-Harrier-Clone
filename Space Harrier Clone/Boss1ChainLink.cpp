#include "Boss1ChainLink.h"

#include <assert.h>
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Engine/Collider.h"
#include "Engine/Sprite.h"
#include "Engine/API.h"
#include "Engine/gameConfig.h"
#include "FloorManager.h"
#include "Explosion.h"


void Boss1ChainLink::init(const Reference<FloorManager>& floorManager, const Reference<Transform>& playerTransform, const SFX& explosionSFX, const Boss1ChainConfig& chainConfig, int motionDelayMS)
{
	m_floorManager = floorManager;
	m_playerTransform = playerTransform;
	m_sfxExplosion = explosionSFX;
	assert(m_floorManager && m_playerTransform && m_sfxExplosion);
	m_chainConfig = chainConfig;
	m_elapsedTime -= motionDelayMS;
}


void Boss1ChainLink::awake()
{
	m_collider = gameObject()->getComponentInChildren<Collider>();
	m_chainLinkSprite = m_collider->gameObject()->getComponent<Sprite>();
	m_shadowSprite = gameObject()->getComponent<Sprite>();
	assert(m_collider && m_chainLinkSprite && m_shadowSprite);

	m_scale.x = m_scale.y = 0;
	gameObject()->transform->setLocalScale(m_scale);

	m_sideFlipFactor = 1;

	gameObject()->setActive(true);
}


void Boss1ChainLink::start()
{
	updateSpriteSet(0);
}


void Boss1ChainLink::update()
{
	if (m_deathElapsedTime != -1)
	{
		die();
		return;
	}

	if (m_elapsedTime < 0)
	{
		m_elapsedTime += Time::deltaTime();
		return;
	}

	int cycleElapsedTime = m_elapsedTime % m_chainConfig.depthCycleTimeMS;
	if (cycleElapsedTime >= m_chainConfig.depthCycleTimeMS)
	{
		cycleElapsedTime -= m_chainConfig.depthCycleTimeMS;
	}

	// DEPTH
	float u = (float)cycleElapsedTime / m_chainConfig.depthCycleTimeMS;
	float currentNormalizedProgress;
	// Moving towards the FRONT
	if (cycleElapsedTime < 0.5f * m_chainConfig.depthCycleTimeMS)
	{
		float halfCycleU = 2 * u;
		currentNormalizedProgress = (1 - halfCycleU) * m_chainConfig.minNormalizedProgress + halfCycleU * m_chainConfig.maxNormalizedProgress;

	}
	// Moving towards the BACK
	else
	{
		float halfCycleU = 2 * u;
		assert(halfCycleU >= 1);
		halfCycleU -= 1;
		currentNormalizedProgress = (1 - halfCycleU) * m_chainConfig.maxNormalizedProgress + halfCycleU * m_chainConfig.minNormalizedProgress;
	}
	float currentnormalizedDepth = m_floorManager->getNormalizedYPos(currentNormalizedProgress);
	m_absoluteDepth = currentnormalizedDepth * m_floorManager->getCurrentFloorHeight();

	// Set Scale
	m_scale.x = m_scale.y = 1 - currentnormalizedDepth;
	gameObject()->transform->setLocalScale(m_scale);

	// Set z-indexes (There's no need to update the shadow's zIndex)
	m_zIndex = (int)((1 - currentnormalizedDepth) * 100);
	m_chainLinkSprite->setZIndex(m_zIndex);
	m_collider->zIndex = m_zIndex;

	// POSITION

	// Left-Right
	float xHalfRange = 0.5f * (m_chainConfig.maxXAxisDistance - m_chainConfig.minXAxisDistance);
	m_xPos = 0.5f * (m_chainConfig.minXAxisDistance + m_chainConfig.maxXAxisDistance) + xHalfRange * sinf(u * (5.5f * (float)M_PI));
	m_xPos *= (1 - currentnormalizedDepth);	// xPos must be scaled, because it is applied to the parent GameObject

	// Avoid the player side	
	updateSideFlipFactor();
	m_xPos *= m_sideFlipFactor;

	// Avoid too big leaps
	float previousXPos = gameObject()->transform->getLocalPosition().x;

	float xPosDifference = m_xPos - previousXPos;
	float maxXDifferenceInFrame = m_chainConfig.maxXDifferencePerSecond * Time::deltaTime() / 1000.0f;

	if (fabs(xPosDifference) > maxXDifferenceInFrame)
	{
		m_xPos = previousXPos + maxXDifferenceInFrame * (fabs(xPosDifference) / xPosDifference);
	}

	// Up-down
	float yHalfRange = 0.5f * (m_chainConfig.maxYPos - m_chainConfig.minYPos);
	m_yPos = 0.5f * (m_chainConfig.minYPos + m_chainConfig.maxYPos) + yHalfRange * sinf(u * (5.5f * (float)M_PI));


	// Set Positions
	gameObject()->transform->setLocalPosition(Vector2(m_xPos, m_absoluteDepth));
	m_chainLinkSprite->gameObject()->transform->setLocalPosition(Vector2(0, m_yPos));

	m_elapsedTime += Time::deltaTime();
}


void Boss1ChainLink::updateSpriteSet(int spriteSet)
{
	if (!m_isTail)
	{
		m_chainLinkSprite->setClipRect(SDL_Rect{ 150, 10 + spriteSet * 110, 110, 73 });
	}
	else
	{
		m_chainLinkSprite->setClipRect(SDL_Rect{ 265, 10 + spriteSet * 110, 73,  76 });
	}
	if (m_nextLink)
	{
		m_nextLink->updateSpriteSet(spriteSet);
	}
}


void Boss1ChainLink::setNextLink(const Reference<Boss1ChainLink>& nextLink)
{
	m_nextLink = nextLink;
}


void Boss1ChainLink::setAsTail(bool isTail)
{
	m_isTail = true;
}


void Boss1ChainLink::requestElapsedTimeSideFlip(int elapsedTimeForFlip)
{
	m_sideFlipTimes.push_back(elapsedTimeForFlip);
	if (m_nextLink)
	{
		m_nextLink->requestElapsedTimeSideFlip(elapsedTimeForFlip);
	}
}


void Boss1ChainLink::requestElapsedTimeDeath(int elapsedTimeForDeath)
{
	m_deathElapsedTime = elapsedTimeForDeath;
	if (m_nextLink)
	{
		m_nextLink->requestElapsedTimeDeath(elapsedTimeForDeath);
	}
}


void Boss1ChainLink::updateSideFlipFactor()
{
	bool finished = false;
	while (!finished)
	{
		if (m_sideFlipTimes.size() > 0)
		{
			int flipTime = m_sideFlipTimes.front();
			if (flipTime <= m_elapsedTime)
			{
				m_sideFlipFactor *= -1;
				m_sideFlipTimes.pop_front();
			}
			else
			{
				finished = true;
			}
		}
		else
		{
			finished = true;
		}
	}
}

void Boss1ChainLink::die()
{
	if (m_elapsedTime >= m_deathElapsedTime)
	{
		// EXPLODE!
		Reference<Transform>& parent = gameObject()->transform->getParent();
		auto explosionGO = Prefabs::instantiate(Prefabs::getPrefab("Boss1ExplosionPrefab"));
		assert(explosionGO);

		explosionGO->transform->setParent(parent);
		explosionGO->transform->setWorldPosition(gameObject()->transform->getWorldPosition());
		auto explosion = explosionGO->getComponent<Explosion>();
		assert(explosion);
		explosion->init(m_floorManager, m_xPos, m_zIndex / 100.0f, 0.95f, m_scale.x, 0.95f, true);
		explosionGO->setActive(true);
		Audio::PlaySFX(m_sfxExplosion);
		GameObject::destroy(gameObject());
	}
	else
	{
		m_elapsedTime += Time::deltaTime();
	}
}
