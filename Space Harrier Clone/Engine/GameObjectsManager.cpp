#include "GameObjectsManager.h"

#include "EngineUtils.h"
#include "GameObject.h"
#include "Transform.h"
#include "Behaviour.h"


GameObjectsManager::GameObjectsManager()
{
}


GameObjectsManager::~GameObjectsManager()
{
}


void GameObjectsManager::update()
{
	refreshGameObjects();
}


void GameObjectsManager::addGameObject(ReferenceOwner<GameObject>& gameObject)
{
	// Check if the gameObject hasn't already been added to the list
	if (EngineUtils::indexOf(m_gosToAdd, gameObject) == -1) {
		m_gosToAdd.push_back(std::move(gameObject));
	}	
}


void GameObjectsManager::destroyGameObject(Reference<GameObject>& gameObject)
{
	// Check if the gameObject hasn't already been added to the list
	if (EngineUtils::indexOf(m_gosToDestroy, gameObject) == -1) {
		for (Reference<Behaviour>& behaviour : gameObject->getComponents<Behaviour>())
		{
			behaviour->onDestroy();
		}
		m_gosToDestroy.push_back(gameObject);
	}
}


void GameObjectsManager::destroyAllGameObjects()
{
	refreshGameObjects();
	for (ReferenceOwner<GameObject>& go : m_gameObjects)
	{
		destroyGameObject(go);
	}
	refreshGameObjects();
}


void GameObjectsManager::refreshGameObjects()
{
	// Delete GOs
	for (Reference<GameObject>& go : m_gosToDestroy)
	{
		doDestroyGameObject(go);
	}	
	m_gosToDestroy.clear();
	
	// Add new GOs
	for (ReferenceOwner<GameObject>& go : m_gosToAdd)
	{
		doAddGameObject(go);
	}
	m_gosToAdd.clear();

	// Refresh all GOs (this will finish initializing the newly added GOs
	for (ReferenceOwner<GameObject>& go : m_gameObjects)
	{
		go->refreshComponents();
	}	
}


void GameObjectsManager::doAddGameObject(ReferenceOwner<GameObject>& gameObject)
{
	if (EngineUtils::indexOf(m_gameObjects, gameObject) == -1) {
		// So the gameObject hasn't previously been added
		gameObject->m_isInCreation = false;
		m_gameObjects.push_back(std::move(gameObject));
	}
}


void GameObjectsManager::doDestroyGameObject(Reference<GameObject>& gameObject)
{
	if (gameObject)
	{
		int index = EngineUtils::indexOf(m_gameObjects, gameObject);
		if (index != -1) {
			// So, the gameObject is in the gameObjects vector
			// Remove from parent
			gameObject->transform->removeParent();
			// Destroy children first
			doDestroyChildren(gameObject->transform.get());
			// Now find the updated index, since destroying the children has modified the actual index
			int newIndex = EngineUtils::indexOf(m_gameObjects, gameObject);
			/*ReferenceOwner<GameObject> goOwner = std::move(m_gameObjects[newIndex]);
			goOwner.deleteReferences();*/
			m_gameObjects.erase(m_gameObjects.begin() + newIndex);
		}
	}
}


void GameObjectsManager::doDestroyChildren(Transform* parentTransform)
{
	for (Transform* childTransform : parentTransform->m_children)
	{
		doDestroyChildren(childTransform);
		int index = EngineUtils::indexOf(m_gameObjects, childTransform->gameObject());
		if (index != -1) {
			// So, the gameObject is in the gameObjects vector
			m_gameObjects.erase(m_gameObjects.begin() + index);
		}
	}

}
