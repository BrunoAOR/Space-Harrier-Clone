#include "ExplosiveObject.h"

#include "Engine/Collider.h"
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Engine/API.h"
#include "GameObjectPool.h"
#include "PooledGameObject.h"
#include "PlayerShot.h"
#include "Explosion.h"
#include "FloorObjectMover.h"



void ExplosiveObject::init(GameObjectPool * explosionPool, SFX explosionSFX)
{
	m_explosionPool = explosionPool;
	m_sfxExplosion = explosionSFX;
}


void ExplosiveObject::start()
{
	if (!m_poolHandler)
	{
		m_poolHandler = gameObject()->getComponent<PooledGameObject>();
	}
	
	if (!m_floorObjectMover)
	{
		m_floorObjectMover = gameObject()->getComponent<FloorObjectMover>();
	}
}


void ExplosiveObject::onTriggerEnter(Reference<Collider>& other)
{
	if (other->gameObject()->getComponent<PlayerShot>())
	{
		Reference<Transform>& parent = gameObject()->transform->getParent();
		if (m_explosionPool)
		{
			auto explosionGO = m_explosionPool->getGameObject();
			if (explosionGO)
			{
				explosionGO->transform->setParent(parent);
				explosionGO->transform->setWorldPosition(gameObject()->transform->getWorldPosition());
				auto explosion = explosionGO->getComponent<Explosion>();
				if (explosion && m_floorObjectMover)
				{
					m_floorObjectMover->setupExplosion(explosion);
				}
			}
			explosionGO->setActive(true);
			Audio::PlaySFX(m_sfxExplosion);
		}

		OutputLog("BOOM!");
		m_poolHandler->returnToPool();
	}
}
