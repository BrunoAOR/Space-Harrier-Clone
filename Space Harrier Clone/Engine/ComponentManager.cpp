#include "ComponentManager.h"

#include <algorithm>
#include "EngineUtils.h"
#include "Component.h"


ComponentManager::ComponentManager()
{
}


ComponentManager::~ComponentManager()
{
}


bool ComponentManager::subscribeComponent(Reference<Component>& component)
{
	// If component is not already in the components-to-subscribe list, add it
	if (managedComponentType() == component->m_type && EngineUtils::indexOf(m_componentsToSubscribe, component) == -1)
	{
		m_componentsToSubscribe.push_back(component);
		initializeComponent(component);
		return true;
	}
	return false;
}


bool ComponentManager::unsubscribeComponent(Reference<Component>& component)
{
	// If component is not already in the components-to-unsubscribe list, add it
	if (EngineUtils::indexOf(m_componentsToSubscribe, component) == -1)
	{
		m_componentsToUnsubscribe.push_back(component);
		return true;
	}
	return false;
}


void ComponentManager::close()
{
	
	
}


void ComponentManager::refreshComponents()
{
	removeEmptyReferences();

	// Unsubscribe components
	for (Reference<Component>& component : m_componentsToUnsubscribe)
	{
		doUnsubscribe(component);
	}
	m_componentsToUnsubscribe.clear();

	// Subscribe components
	for (Reference<Component>& component : m_componentsToSubscribe)
	{
		doSubscribe(component);
	}
	m_componentsToSubscribe.clear();
}


void ComponentManager::removeEmptyReferences()
{
	m_components.erase(std::remove_if(m_components.begin(), m_components.end(), [](Reference<Component>& component) -> bool {return !component; }), m_components.end());
}


void ComponentManager::doSubscribe(const Reference<Component>& component)
{
	// If component is not already in the components list, add it
	if (EngineUtils::indexOf(m_components, component) == -1)
	{
		m_components.push_back(component);
	}
}


void ComponentManager::doUnsubscribe(const Reference<Component>& component)
{
	// If component is in the components list, then remove it
	int index = EngineUtils::indexOf(m_components, component);
	if (index != -1)
	{
		m_components.erase(m_components.begin() + index);
	}
}


ComponentType ComponentManager::getComponentType(const Reference<Component>& component) const
{
	return component->m_type;
}
