#include "Boss1.h"

#include <assert.h>
#include <math.h>
#include "Engine/gameConfig.h"
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Engine/API.h"
#include "Engine/Collider.h"
#include "Engine/Sprite.h"
#include "Utils.h"
#include "FloorManager.h"
#include "GameObjectPool.h"
#include "PlayerShot.h"
#include "Boss1ChainLink.h"
#include "Explosion.h"


void Boss1::onDestroy()
{
	if (m_shotsPool != nullptr)
	{
		delete(m_shotsPool);
		m_shotsPool = nullptr;
	}
}


void Boss1::init(const Reference<FloorManager>& floorManager, const Reference<Transform>& playerTransform, SFX explosionSFX)
{
	m_floorManager = floorManager;
	m_playerTransform = playerTransform;
	m_sfxExplosion = explosionSFX;
	assert(m_floorManager && m_playerTransform && m_sfxExplosion);

	Reference<Prefab> chainLinkPrefab = Prefabs::getPrefab("Boss1ChainLinkPrefab");
	assert(chainLinkPrefab);

	m_chainConfig = getBoss1ChainConfig();

	Reference<Boss1ChainLink> previousChainLink;
	int delay = m_chainConfig.chainDelay;

	for (int i = 1; i < m_chainConfig.chainLength; ++i)
	{
		auto go = Prefabs::instantiate(chainLinkPrefab);
		assert(go);

		go->transform->setParent(gameObject()->transform->getParent());
		auto chainLink = go->getComponent<Boss1ChainLink>();
		assert(chainLink);
		delay += m_chainConfig.chainDelay;
		if (i == 1)
		{
			m_nextLink = chainLink;
		}
		else
		{
			previousChainLink->setNextLink(chainLink);
		}
		if (i == m_chainConfig.chainLength - 1)
		{
			chainLink->setAsTail();
		}
		chainLink->init(m_floorManager, m_playerTransform, m_sfxExplosion, m_chainConfig, delay);
		previousChainLink = chainLink;

	}

	m_scale.x = m_scale.y = 0;
	gameObject()->transform->setLocalScale(m_scale);

}


void Boss1::awake()
{
	m_sfxBossShot = Audio::LoadSFX("assets/audio/sfx/SFX - BossShot.wav");
	m_collider = gameObject()->getComponentInChildren<Collider>();
	m_headSprite = m_collider->gameObject()->getComponent<Sprite>();
	m_shadowSprite = gameObject()->getComponent<Sprite>();
	assert(m_sfxBossShot && m_collider && m_headSprite && m_shadowSprite);

	m_shotsPool = new GameObjectPool(Prefabs::getPrefab("Boss1ShotPrefab"), 6);

	m_currentSpritesSet = 0;

	faceDirection(true);

	gameObject()->setActive(true);
}


void Boss1::start()
{
	m_elapsedTime = 0;
	m_spriteSetsCount = 7;

	m_sideFlipFactor = 1;
}


void Boss1::update()
{
	if (m_deathElapsedTime != -1)
	{
		die();
		return;
	}

	int cycleElapsedTime = m_elapsedTime % m_chainConfig.depthCycleTimeMS;

	// DEPTH
	float u = (float)cycleElapsedTime / m_chainConfig.depthCycleTimeMS;
	float currentNormalizedProgress;
	// Moving towards the FRONT
	if (cycleElapsedTime < 0.5f * m_chainConfig.depthCycleTimeMS)
	{
		faceDirection(true);
		float halfCycleU = 2 * u;
		currentNormalizedProgress = (1 - halfCycleU) * m_chainConfig.minNormalizedProgress + halfCycleU * m_chainConfig.maxNormalizedProgress;

	}
	// Moving towards the BACK
	else
	{
		faceDirection(false);
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
	m_headSprite->setZIndex(m_zIndex);
	m_collider->zIndex = m_zIndex;

	// POSITION

	// Left-Right
	float xHalfRange = 0.5f * (m_chainConfig.maxXAxisDistance - m_chainConfig.minXAxisDistance);
	m_xPos = 0.5f * (m_chainConfig.minXAxisDistance + m_chainConfig.maxXAxisDistance) + xHalfRange * sinf(u * (5.5f * (float)M_PI));
	m_xPos *= (1 - currentnormalizedDepth);	// xPos must be scaled, because it is applied to the parent GameObject
	
	// Avoid the player side
	float playerNormXPos = (m_playerTransform->getWorldPosition().x - SCREEN_WIDTH / 2.0f) / SCREEN_WIDTH;
	int playerSide = playerNormXPos > 0.1f ? 1 : (playerNormXPos < -0.1f ? -1 : 0);
	
	int previousSideFlipFactor = m_sideFlipFactor;
	if (playerSide != 0)
	{
		m_sideFlipFactor = -playerSide;
	}
	if (m_sideFlipFactor != previousSideFlipFactor)
	{
		m_nextLink->requestElapsedTimeSideFlip(m_elapsedTime);
	}
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
	m_headSprite->gameObject()->transform->setLocalPosition(Vector2(0, m_yPos));

	m_elapsedTime += Time::deltaTime();
}


void Boss1::onTriggerEnter(Reference<Collider>& other)
{
	if (other->gameObject()->getComponent<PlayerShot>())
	{
		++m_currentSpritesSet;
		if (m_nextLink)
		{
			m_nextLink->updateSpriteSet(m_currentSpritesSet);
		}
		faceDirection(m_facingFront, true);
		if (m_currentSpritesSet == m_spriteSetsCount - 1)
		{
			// So, time to die
			m_deathElapsedTime = m_elapsedTime + m_chainConfig.deathDelay;
			if (m_nextLink)
			{
				m_nextLink->requestElapsedTimeDeath(m_deathElapsedTime);
			}
			m_collider->setActive(false);
		}
	}
}


void Boss1::faceDirection(bool toFront, bool forceUpdate)
{
	if (m_facingFront == toFront && !forceUpdate)
	{
		return;
	}
	m_facingFront = toFront;
	if (m_facingFront)
	{
		m_headSprite->setClipRect(SDL_Rect{ 5, 10 + m_currentSpritesSet * 110, 68, 109 });
	}
	else
	{
		m_headSprite->setClipRect(SDL_Rect{ 75, 10 + m_currentSpritesSet * 110, 70, 108 });
	}
}


void Boss1::die()
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
