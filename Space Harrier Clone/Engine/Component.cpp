#include "Component.h"

#include "globals.h"
#include "ComponentType.h"
#include "GameObject.h"


// TESTING START
int Component::s_alive = 0;
int Component::s_nextId = 0;
// TESTING END

Component::Component()
	: m_isActive(true), m_type(ComponentType::UNDEFINED)
{
	// TESTING START
	m_id = s_nextId++;
	//OutputLog("DEBUG: Component constructed -id: %i  ||  Alive: %i", m_id, ++s_alive);
	// TESTING END
}


Component::~Component()
{
	// TESTING START
	//OutputLog("DEBUG: Component  destructed -id: %i  ||  Alive: %i", m_id, --s_alive);
	// TESTING END
}


const Reference<GameObject>& Component::gameObject() const
{
	return m_gameObject;
}


Reference<GameObject>& Component::gameObject()
{
	return m_gameObject;
}


void Component::setActive(bool activeState)
{
	m_isActive = activeState;
}


bool Component::isActive() const
{
	return m_isActive && gameObject()->isActive();
}
