#include "CollisionCallbackForwarder.h"


void CollisionCallbackForwarder::addTarget(const Reference<Behaviour>& newTarget)
{
	if (newTarget)
	{
		m_targets.push_back(newTarget);
	}
}


void CollisionCallbackForwarder::onCollision(CollisionInfo & info)
{
	for (Reference<Behaviour>& target : m_targets)
	{
		if (target && target->isActive())
		{
			target->onCollision(info);
		}
	}
}


void CollisionCallbackForwarder::onTriggerEnter(Reference<Collider>& other)
{
	for (Reference<Behaviour>& target : m_targets)
	{
		if (target && target->isActive())
		{
			target->onTriggerEnter(other);
		}
	}
}


void CollisionCallbackForwarder::onTriggerStay(Reference<Collider>& other)
{
	for (Reference<Behaviour>& target : m_targets)
	{
		if (target && target->isActive())
		{
			target->onTriggerStay(other);
		}
	}
}


void CollisionCallbackForwarder::onTriggerExit(Reference<Collider>& other)
{
	for (Reference<Behaviour>& target : m_targets)
	{
		if (target && target->isActive())
		{
			target->onTriggerExit(other);
		}
	}
}
