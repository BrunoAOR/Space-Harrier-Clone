#include "BehavioursManager.h"

#include "Behaviour.h"
#include "ComponentType.h"
#include "GameObject.h"


BehavioursManager::BehavioursManager()
{
}


BehavioursManager::~BehavioursManager()
{
}


ComponentType BehavioursManager::managedComponentType() const
{
	return ComponentType::BEHAVIOUR;
}


void BehavioursManager::update()
{
	// Note: refreshComponents ensures that all Reference in m_components are valid, so they can be safely used
	refreshComponents();
	for (Reference<Component>& componentRef : m_components)
	{
		Behaviour* behaviourPtr = static_cast<Behaviour*>(componentRef.get());
		// Actual update
		if (!behaviourPtr->m_isAwake)
		{
			behaviourPtr->awake();
			behaviourPtr->m_isAwake = true;
		}
		else if (behaviourPtr->gameObject()->isActive())
		{
			if (!behaviourPtr->m_started) {
				behaviourPtr->start();
				behaviourPtr->m_started = true;
			}
			else
			{
				behaviourPtr->update();
			}
		}
	}
}


bool BehavioursManager::init()
{
	return true;
}


void BehavioursManager::close()
{
}


bool BehavioursManager::initializeComponent(Reference<Component>& component)
{
	return true;
}
