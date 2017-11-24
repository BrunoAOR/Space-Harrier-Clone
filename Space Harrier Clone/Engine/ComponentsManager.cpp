#include "ComponentsManager.h"

#include "ComponentManager.h"
#include "BehavioursManager.h"
#include "CollidersManager.h"
#include "RenderersManager.h"


ComponentsManager::ComponentsManager()
{
}


ComponentsManager::~ComponentsManager()
{
}


bool ComponentsManager::sendToManager(Reference<Component> component) const
{
	for (auto compManager : m_componentManagers)
	{
		if (compManager->subscribeComponent(component))
		{
			return true;
		}
	}
	return false;
}


bool ComponentsManager::init()
{
	// Success flag
	bool success = true;

	m_componentManagers.push_back(new BehavioursManager());
	m_componentManagers.push_back(new CollidersManager());
	m_componentManagers.push_back(new RenderersManager());
	for (auto compManager : m_componentManagers)
	{
		success &= compManager->init();
	}
	return success;
}


void ComponentsManager::close()
{
	for (auto compManager : m_componentManagers)
	{
		compManager->close();
		delete compManager;
	}
	m_componentManagers.clear();
}


void ComponentsManager::update() const
{
	for (auto compManager : m_componentManagers)
	{
		compManager->update();
	}
}
