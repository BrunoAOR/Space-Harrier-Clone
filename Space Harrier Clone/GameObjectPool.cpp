#include "GameObjectPool.h"

#include <assert.h>
#include "Engine/GameObject.h"
#include "Engine/API.h"
#include "PooledGameObject.h"


GameObjectPool::GameObjectPool(const Reference<Prefab>& prefab, int initialPoolSize)
{
	m_prefab = prefab;
	m_initialPoolSize = initialPoolSize >= 0 ? initialPoolSize : 0;
	assert(m_prefab);
	for (int i = 0; i < m_initialPoolSize; ++i)
	{
		createGameObject();
	}
}


GameObjectPool::~GameObjectPool()
{
	for (Reference<GameObject>& goRef : m_gameObjects)
	{
		GameObject::destroy(goRef);
	}
}


Reference<GameObject> GameObjectPool::getGameObject()
{
	if (m_availableGameObjects.empty())
	{
		createGameObject();
	}

	Reference<GameObject>& goRef = *(m_availableGameObjects.top());
	m_availableGameObjects.pop();
	return goRef;
}


bool GameObjectPool::returnGameObject(Reference<GameObject> gameObjectToReturn)
{
	gameObjectToReturn->setActive(false);
	for (Reference<GameObject>& goRef : m_gameObjects)
	{
		if (goRef == gameObjectToReturn)
		{
			m_availableGameObjects.push(&goRef);
			return true;
		}
	}
	return false;
}


void GameObjectPool::createGameObject()
{
	m_gameObjects.push_back(Prefabs::instantiate(m_prefab));
	Reference<PooledGameObject>& pgo = m_gameObjects.back()->addComponent<PooledGameObject>();
	pgo->gameObject()->setActive(false);
	pgo->m_pool = this;
	m_availableGameObjects.push(&(m_gameObjects.back()));
}
