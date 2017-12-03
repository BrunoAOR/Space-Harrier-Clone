#include "CircleCollider.h"

#include "ColliderType.h"
#include "GameObject.h"
#include "Transform.h"


CircleCollider::CircleCollider() : radius(0)
{
	m_colliderType = ColliderType::CIRCLE;
}


CircleCollider::~CircleCollider()
{
}


float CircleCollider::getLocalScaledRadius() const
{
	Vector2 localScale = gameObject()->transform->getLocalScale();
	float minScaleFactor = fminf(localScale.x, localScale.y);
	return radius * minScaleFactor;
}


float CircleCollider::getWorldScaledRadius() const
{
	Vector2 worldScale = gameObject()->transform->getWorldScale();
	float minScaleFactor = fminf(worldScale.x, worldScale.y);
	return radius * minScaleFactor;
}
