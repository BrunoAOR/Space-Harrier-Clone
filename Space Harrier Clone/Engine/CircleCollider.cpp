#include "CircleCollider.h"

#include "ColliderType.h"

CircleCollider::CircleCollider() : radius(0)
{
	m_colliderType = ColliderType::CIRCLE;
}


CircleCollider::~CircleCollider()
{
}
