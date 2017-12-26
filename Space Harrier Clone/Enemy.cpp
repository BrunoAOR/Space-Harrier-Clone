#include "Enemy.h"

#include <assert.h>
#include "Engine/GameObject.h"
#include "Engine/SpriteSheet.h"
#include "Engine/API.h"
#include "Engine/Collider.h"
#include "Engine/Transform.h"
#include "MotionPatternPoint.h"
#include "PooledGameObject.h"
#include "FloorManager.h"
#include "Explosion.h"
#include "GameObjectPool.h"
#include "EnemyShot.h"


void Enemy::init(int lifeTimeMS, const MotionPattern& motionPattern, const Reference<FloorManager>& floorManager, const Reference<Transform>& playerTransform, GameObjectPool* enemyShotPool, const SFX& sfxEnemyShot)
{
	if (!m_collider)
	{
		m_collider = gameObject()->getComponentInChildren<Collider>();
	}

	m_motionPattern = motionPattern;
	m_floorManager = floorManager;
	m_playerTransform = playerTransform;
	m_enemyShotPool = enemyShotPool;
	m_sfxEnemyShot = sfxEnemyShot;

	if (!m_spriteSheet)
	{
		m_spriteSheet = gameObject()->getComponentInChildren<SpriteSheet>();
	}
	if (!m_characterGo)
	{
		m_characterGo = gameObject()->getComponentInChildren<Collider>()->gameObject();
	}
	if (!m_shadowGo)
	{
		m_shadowGo = gameObject()->getComponentInChildren<Sprite>()->gameObject();
	}
	if (!m_poolHandler)
	{
		m_poolHandler = gameObject()->getComponent<PooledGameObject>();
	}
	m_lifeTimeMS = lifeTimeMS;

	assert(m_motionPattern.isValid() && m_floorManager && m_playerTransform && m_enemyShotPool && m_sfxEnemyShot && m_spriteSheet && m_characterGo && m_shadowGo && m_poolHandler && m_lifeTimeMS > 0);

	m_elapsedTime = 0;
	if (m_collider)
	{
		m_collider->zIndex = 0;
	}
	m_spriteSheet->setZIndex(0);
}


void Enemy::update()
{
	float normalizedTime = ((float)m_elapsedTime) / m_lifeTimeMS;
	if (normalizedTime > 1)
	{
		m_poolHandler->returnToPool();
		OutputLog("Sending enemy to pool");
		return;
	}

	MotionPatternPoint mpp = m_motionPattern.getMotionPatternPoint(normalizedTime);
	
	// Perform action, if required
	if (mpp.action.triggerId != m_lastTriggeredActionId)
	{
		// So, trigger the action
		m_lastTriggeredActionId = mpp.action.triggerId;
		if (mpp.action.fire)
		{
			shoot(mpp);
		}
		if (mpp.action.animationName != "")
		{
			m_spriteSheet->playAnimation(mpp.action.animationName, mpp.action.animationLoop);
		}
	}

	// Move characterGo (based on spritePosition.y)
	if (normalizedTime > 0.5f && m_characterGo->transform->getLocalPosition().y < mpp.spritePosition.y)
	{
		int i = 0;
	}
	m_characterGo->transform->setLocalPosition(Vector2(0, mpp.spritePosition.y));
	
	// Move gameObject yPos (based on spritePosition.x and depth)
	float depthY = m_floorManager->getCurrentFloorHeight() * mpp.normalizedDepth;
	gameObject()->transform->setLocalPosition(Vector2( mpp.spritePosition.x, depthY));

	// Scale children based on normalizedDepth (the parent can't be scaled because the height of the characterGo MUST be independent of scale)
	float scale = (1 - mpp.normalizedDepth) + 0.1f;
	m_characterGo->transform->setLocalScale(Vector2(scale, scale));
	m_shadowGo->transform->setLocalScale(Vector2(scale, scale));

	// Update z-indexes
	int zIndex = (int)((1 - mpp.normalizedDepth) * 100);
	if (m_collider)
	{
		m_collider->zIndex = zIndex;
	}
	m_spriteSheet->setZIndex(zIndex);

	if (!m_floorManager->freezeAtBottom)
	{
		m_elapsedTime += Time::deltaTime();
	}
}


void Enemy::setupExplosion(Reference<Explosion>& explosion)
{
	float normalizedDepth = m_motionPattern.getMotionPatternPoint(((float)m_elapsedTime) / m_lifeTimeMS).normalizedDepth;
	float normalizedCurrentProgress = 1 - normalizedDepth;
	float currentScale = normalizedCurrentProgress;
	explosion->init(m_floorManager, gameObject()->transform->getLocalPosition().x, normalizedCurrentProgress, 0.95f, currentScale, 1);
}

void Enemy::shoot(MotionPatternPoint mpp)
{
	auto shotGo = m_enemyShotPool->getGameObject();
	if (shotGo)
	{
		shotGo->setActive(true);
		Reference<EnemyShot> shot = shotGo->getComponent<EnemyShot>();
		assert(shot);
		Vector2 currPos = m_characterGo->transform->getWorldPosition();
		// The shot is lifted to the center of the enemy (consider scale)
		currPos.y += m_characterGo->transform->getLocalScale().y * m_spriteSheet->getCurrentAnimationFrameHeight() / 2.0f;

		Vector2 targetPos = m_playerTransform->getWorldPosition();
		// The target is lifted to the approximate center of the character
		targetPos.y += 30;
		OutputLog("enemPos: %f, %f shifts to y: %f | scaleY: %f", currPos.x, m_characterGo->transform->getWorldPosition().y, currPos.y, gameObject()->transform->getLocalScale().y);
		OutputLog("targetPos: %f, %f shifts to y: %f", targetPos.x, m_playerTransform->getWorldPosition().y, targetPos.y);
		shot->init(m_floorManager, currPos, mpp.normalizedDepth, targetPos, 0.95f);
		Audio::PlaySFX(m_sfxEnemyShot);
	}
}
