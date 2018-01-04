#include "Boss1.h"

#include <assert.h>
#include <math.h>
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Engine/API.h"
#include "Engine/Collider.h"
#include "Engine/Sprite.h"
#include "gameData.h"
#include "Utils.h"
#include "FloorManager.h"
#include "GameObjectPool.h"
#include "PlayerShot.h"
#include "Boss1ChainLink.h"
#include "Explosion.h"
#include "EnemyShot.h"
#include "MessengerEventType.h"
#include "Messenger.h"


void Boss1::onDestroy()
{
	Messenger::removeListener(this, MessengerEventType::PLAYER_DEAD);
	Messenger::removeListener(this, MessengerEventType::PLAYER_REVIVED);
	Messenger::removeListener(this, MessengerEventType::FLOOR_MOTION_STOPPED);
	Messenger::removeListener(this, MessengerEventType::FLOOR_MOTION_RESUMED);

	Audio::unloadSFX(m_sfxBossShot);

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

	assert(m_nextLink);
	m_nextLink->init(m_floorManager, m_playerTransform, gameObject()->transform->getParent(), m_sfxExplosion, m_chainConfig, m_chainConfig.chainDelay, 0);

	m_scale.x = m_scale.y = 0;
	gameObject()->transform->setLocalScale(m_scale);
	gameObject()->setActive(true);
}


void Boss1::awake()
{
	Messenger::addListener(this, MessengerEventType::PLAYER_DEAD);
	Messenger::addListener(this, MessengerEventType::PLAYER_REVIVED);
	Messenger::addListener(this, MessengerEventType::FLOOR_MOTION_STOPPED);
	Messenger::addListener(this, MessengerEventType::FLOOR_MOTION_RESUMED);

	Reference<Prefab> chainLinkPrefab = Prefabs::getPrefab("Boss1ChainLinkPrefab");
	assert(chainLinkPrefab);
	m_chainConfig = getBoss1ChainConfig();

	Reference<Boss1ChainLink> previousChainLink;

	for (int i = 1; i < m_chainConfig.chainLength; ++i)
	{
		auto go = Prefabs::instantiate(chainLinkPrefab);
		assert(go);

		go->transform->setParent(gameObject()->transform);
		auto chainLink = go->getComponent<Boss1ChainLink>();
		assert(chainLink);
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
		previousChainLink = chainLink;
	}

	m_sfxBossShot = Audio::loadSFX("assets/audio/sfx/SFX - BossShot.wav");
	m_collider = gameObject()->getComponentInChildren<Collider>();
	m_headSprite = m_collider->gameObject()->getComponent<Sprite>();
	m_shadowSprite = gameObject()->getComponent<Sprite>();
	assert(m_sfxBossShot && m_collider && m_headSprite && m_shadowSprite);

	m_shotsPool = new GameObjectPool(Prefabs::getPrefab("Boss1ShotPrefab"), 6);

	m_currentSpritesSet = 0;

	faceDirection(true);

	gameObject()->setActive(false);
}


void Boss1::start()
{
	m_elapsedTime = 0;
	m_spriteSetsCount = 7;

	m_sideFlipFactor = 1;
	m_nextShotIndex = 0;
	m_lastCycleTime = -1;
}


void Boss1::update()
{
	if (m_playerDead)
	{
		return;
	}

	if (m_deathElapsedTime != -1)
	{
		die();
		return;
	}

	int cycleElapsedTime = m_elapsedTime % m_chainConfig.depthCycleTimeMS;
	float u = (float)cycleElapsedTime / m_chainConfig.depthCycleTimeMS;

	// Shooting
	shoot(cycleElapsedTime);

	// DEPTH
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
	m_currentnormalizedDepth = m_floorManager->getNormalizedYPos(currentNormalizedProgress);
	m_absoluteDepth = m_currentnormalizedDepth * m_floorManager->getCurrentFloorHeight();

	// Set Scale
	m_scale.x = m_scale.y = 1 - m_currentnormalizedDepth;
	gameObject()->transform->setLocalScale(m_scale);
	
	// Set z-indexes (There's no need to update the shadow's zIndex)
	m_zIndex = (int)((1 - m_currentnormalizedDepth) * 100);
	m_headSprite->setZIndex(m_zIndex);
	m_collider->zIndex = m_zIndex;

	// POSITION

	// Left-Right
	float xHalfRange = 0.5f * (m_chainConfig.maxXAxisDistance - m_chainConfig.minXAxisDistance);
	m_xPos = 0.5f * (m_chainConfig.minXAxisDistance + m_chainConfig.maxXAxisDistance) + xHalfRange * sinf(u * (5.5f * (float)M_PI));
	m_xPos *= (1 - m_currentnormalizedDepth);	// xPos must be scaled, because it is applied to the parent GameObject
	
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
	// Account for scale
	float maxXDifferenceInFrame = gameObject()->transform->getLocalScale().x * m_chainConfig.maxXDifferencePerSecond * Time::deltaTime() / 1000.0f;

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


void Boss1::eventsCallback(MessengerEventType eventType)
{
	if (eventType == MessengerEventType::PLAYER_DEAD)
	{
		m_playerDead = true;
		if (m_nextLink)
		{
			m_nextLink->setPlayerDead(true);
		}
	}
	else if (eventType == MessengerEventType::PLAYER_REVIVED)
	{
		m_playerDead = false;
		if (m_nextLink)
		{
			m_nextLink->setPlayerDead(false);
		}
	}
	else if (eventType == MessengerEventType::FLOOR_MOTION_STOPPED)
	{
		m_playerDowned = true;
		
	}
	else if (eventType == MessengerEventType::FLOOR_MOTION_RESUMED)
	{
		m_playerDowned = false;
		
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


void Boss1::shoot(int cycleTime)
{
	if (cycleTime < m_lastCycleTime)
	{
		m_cycleShotsDone = false;
	}

	float nextTime = m_chainConfig.depthCycleTimeMS * m_chainConfig.normalizedCycleShootingTimes[m_nextShotIndex];

	if (!m_cycleShotsDone && cycleTime >= nextTime)
	{
		++m_nextShotIndex;
		if (m_nextShotIndex >= (int)m_chainConfig.normalizedCycleShootingTimes.size())
		{
			m_cycleShotsDone = true;
			m_nextShotIndex = 0;
		}


		if (!m_playerDowned)
		{
			auto shotGo = m_shotsPool->getGameObject();
			assert(shotGo);
			{
				shotGo->setActive(true);
				Reference<EnemyShot> shot = shotGo->getComponent<EnemyShot>();
				assert(shot);
				Vector2 currPos = m_headSprite->gameObject()->transform->getWorldPosition();
				// The shot is lifted to the mouth of the dragon head (consider scale)
				currPos.y += m_headSprite->gameObject()->transform->getLocalScale().y * 15.0f;

				Vector2 targetPos = m_playerTransform->getWorldPosition();
				// The target is lifted to the approximate center of the character
				targetPos.y += 30;

				// Pseudo-random shot spread (time-based)
				float xNormSpread = 2 * (Time::time() % 25) / 25.0f - 1;
				float yNormSpread = 2 * (Time::time() % 100) / 100.0f - 1;

				targetPos.x += m_chainConfig.shotsSpreadDistance * xNormSpread;
				targetPos.y += m_chainConfig.shotsSpreadDistance * yNormSpread;

				shot->init(m_floorManager, currPos, m_currentnormalizedDepth, targetPos, 0.95f);
				Audio::playSFX(m_sfxBossShot);
			}
		}
	}
	m_lastCycleTime = cycleTime;
}


void Boss1::die()
{
	if (m_elapsedTime >= m_deathElapsedTime)
	{
		Messenger::broadcastEvent(MessengerEventType::POINTS_100000);
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
		Audio::playSFX(m_sfxExplosion);
		GameObject::destroy(gameObject());
	}
	else
	{
		m_elapsedTime += Time::deltaTime();
	}
}
