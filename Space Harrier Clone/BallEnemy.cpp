#include "BallEnemy.h"

#include <assert.h>
#include "Engine/GameObject.h"
#include "Engine/SpriteSheet.h"
#include "ExplosiveObject.h"
#include "BulletBouncer.h"


void BallEnemy::init(int lifeTimeMS, const MotionPattern & motionPattern, const Reference<FloorManager>& floorManager, const Reference<Transform>& playerTransform, GameObjectPool * enemyShotPool, const SFX & sfxEnemyShot)
{
	Enemy::init(lifeTimeMS, motionPattern, floorManager, playerTransform, enemyShotPool, sfxEnemyShot);

	if (!m_explosiveObject)
	{
		m_explosiveObject = gameObject()->getComponent<ExplosiveObject>();
	}
	if (!m_bulletBouncer)
	{
		m_bulletBouncer = gameObject()->getComponent<BulletBouncer>();
	}
	assert(m_explosiveObject && m_bulletBouncer);

	m_shootable = false;
	bool success = m_spriteSheet->selectAnimation("open", 0);
	m_explosiveObject->setActive(false);
	m_bulletBouncer->setActive(true);
	assert(success);
}


void BallEnemy::update()
{
	Enemy::update();
	std::string currentAnimationName = m_spriteSheet->getCurrentAnimationName();
	bool isAnimationPlaying = m_spriteSheet->isPlaying();
	bool isAnimationFinished = m_spriteSheet->isFinished();

	// Use buffered state to avoid unnecessary calls to the setActive functions of the explosiveObject and bulletBouncer
	bool wasShootable = m_shootable;
	m_shootable = currentAnimationName == "open" && isAnimationPlaying && isAnimationFinished;

	if (m_shootable != wasShootable)
	{
		m_explosiveObject->setActive(m_shootable);
		m_bulletBouncer->setActive(!m_shootable);
	}
}
