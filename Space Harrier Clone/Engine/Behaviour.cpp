#include "Behaviour.h"

#include "ComponentType.h"
#include "Collider.h"
#include "CollisionInfo.h"


Behaviour::Behaviour()
{
	m_type = ComponentType::BEHAVIOUR;
	m_isAwake = false;
	m_started = false;
}


Behaviour::~Behaviour()
{
}


void Behaviour::awake()
{
}


void Behaviour::start()
{
}


void Behaviour::update()
{
}


void Behaviour::onCollision(CollisionInfo info)
{
}


void Behaviour::onTriggerEnter(Reference<Collider> other)
{
}


void Behaviour::onTriggerStay(Reference<Collider> other)
{
}


void Behaviour::onTriggerExit(Reference<Collider> other)
{
}
