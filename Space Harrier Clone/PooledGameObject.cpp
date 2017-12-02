#include "PooledGameObject.h"

#include "Engine/GameObject.h"
#include "GameObjectPool.h"


void PooledGameObject::returnToPool()
{
	if (m_pool)
	{
		m_pool->returnGameObject(gameObject());
	}
	else
	{
		GameObject::destroy(gameObject());
	}
}
