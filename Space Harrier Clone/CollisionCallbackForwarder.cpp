#include "CollisionCallbackForwarder.h"


void CollisionCallbackForwarder::onCollision(CollisionInfo & info)
{
	if (target)
	{
		target->onCollision(info);
	}
}


void CollisionCallbackForwarder::onTriggerEnter(Reference<Collider>& other)
{
	if (target)
	{
		target->onTriggerEnter(other);
	}
}


void CollisionCallbackForwarder::onTriggerStay(Reference<Collider>& other)
{
	if (target)
	{
		target->onTriggerStay(other);
	}
}


void CollisionCallbackForwarder::onTriggerExit(Reference<Collider>& other)
{
	if (target)
	{
		target->onTriggerExit(other);
	}
}
