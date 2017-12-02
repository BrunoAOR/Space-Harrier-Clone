#include "GameObject.h"

#include "globals.h"
#include "Engine.h"
#include "EngineUtils.h"
#include "Transform.h"
#include "SceneManager.h"
#include "GameObjectsManager.h"
#include "Transform.h"


// TESTING START
int GameObject::s_alive = 0;
int GameObject::s_nextId = 0;
// TESTING END

GameObject::GameObject()
{
	// TESTING START
	m_id = s_nextId++;
	//OutputLog("GO constructed -id: %i  ||  Alive: %i", m_id, ++s_alive);
	// TESTING END

	m_isActive = true;
	m_isInCreation = true;
}


GameObject::~GameObject()
{
	refreshComponents();

	// TESTING START
	//OutputLog("GO  destructed -id: %i  ||  Alive: %i", m_id, --s_alive);
	// TESTING END
}


void GameObject::refreshComponents()
{
	// Remove components
	for (Reference<Component>& component : m_componentsToRemove)
	{
		doRemoveComponent(component);
	}
	m_componentsToRemove.clear();

	// Add new components
	for (ReferenceOwner<Component>& component : m_componentsToAdd)
	{
		doAddComponent(component);
	}
	m_componentsToAdd.clear();
}


void GameObject::removeComponent(const Reference<Component>& component)
{
	int componentIndex = EngineUtils::indexOf(m_components, component);
	int willBeRemovedIndex = EngineUtils::indexOf(m_componentsToRemove, component);
	if (componentIndex != -1 && willBeRemovedIndex == -1)
	{
		// So the component is contained in the list of components and not in the list of the components that WILL be deleted
		m_componentsToRemove.push_back(component);
	}
}


void GameObject::doAddComponent(ReferenceOwner<Component>& component)
{
	// No need to check for components's presence in m_components since this funciton gets called with newly instantiated components only
	m_components.push_back(std::move(component));
}


void GameObject::doRemoveComponent(Reference<Component>& component)
{
	// Remove from the vector and delete
	int componentIndex = EngineUtils::indexOf(m_components, component);
	if (componentIndex != -1)
	{
		m_components.erase(m_components.begin() + componentIndex);
	}
}


void GameObject::setActive(bool activeState)
{
	m_isActive = activeState;
}


bool GameObject::isActive() const
{
	const Reference<Transform>& parent = transform->getParent();
	if (parent)
	{
		return m_isActive && parent->gameObject()->isActive();
	}
	return m_isActive;
}


Reference<GameObject> GameObject::createNew()
{
	if (engine->sceneManager->hasActiveScene())
	{
		ReferenceOwner<GameObject> go(new GameObject());
		Reference<GameObject> goRef = go.getReference();
		go->m_self = goRef;
		// Add and setup transform
		go->transform = go->addComponent<Transform>();
		
		// Push ownership to the gameObjectsManager
		engine->gameObjectsManager->addGameObject(std::move(go));
		return goRef;
	}
	return Reference<GameObject>();
}


void GameObject::destroy(Reference<GameObject>& gameObject)
{
	engine->gameObjectsManager->destroyGameObject(gameObject);
}
