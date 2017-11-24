#include "Collider.h"

#include "GameObject.h"
#include "Transform.h"
#include "Behaviour.h"
#include "ComponentType.h"
#include "CollisionInfo.h"


Collider::Collider() : offset(0, 0), isStatic(false), isTrigger(false)
{
	m_type = ComponentType::COLLIDER;
}


Collider::~Collider()
{
}


Vector2 Collider::getLocalPosition() const
{
	auto transform = gameObject()->transform;
	Vector2 localPos = transform->getLocalPosition() + offset;
	return localPos;
}


Vector2 Collider::getWorldPosition() const
{
	auto transform = gameObject()->transform;
	Vector2 worldPos = transform->getLocalPosition() + offset;
	worldPos = transform->localToWorldPosition(worldPos);
	return worldPos;
}


float Collider::getWorldRotation() const
{
	return gameObject()->transform->getWorldRotation();
}


void Collider::onCollision(CollisionInfo info) const
{
	auto behaviours = gameObject()->getComponents<Behaviour>();
	for (auto behaviourRef : behaviours)
	{
		if (behaviourRef)
		{
			behaviourRef->onCollision(info);
		}
	}
}


void Collider::onTriggerEnter(Reference<Collider> other) const
{
	auto behaviours = gameObject()->getComponents<Behaviour>();
	for (auto behaviourRef : behaviours)
	{
		if (behaviourRef)
		{
			behaviourRef->onTriggerEnter(other);
		}
	}
}


void Collider::onTriggerStay(Reference<Collider> other) const
{
	auto behaviours = gameObject()->getComponents<Behaviour>();
	for (auto behaviourRef : behaviours)
	{
		if (behaviourRef)
		{
			behaviourRef->onTriggerStay(other);
		}
	}
}


void Collider::onTriggerExit(Reference<Collider> other) const
{
	auto behaviours = gameObject()->getComponents<Behaviour>();
	for (auto behaviourRef : behaviours)
	{
		if (behaviourRef)
		{
			behaviourRef->onTriggerExit(other);
		}
	}
}
