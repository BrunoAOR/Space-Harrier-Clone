#ifndef H_COLLIDER
#define H_COLLIDER

#include "Component.h"
#include "Reference.h"
#include "Vector2.h"
struct CollisionInfo;
enum class ColliderType;

class Collider :
	public Component
{
	friend class CollidersManager;

public:
	Collider();
	virtual ~Collider() = 0;

	Vector2 getLocalPosition() const;
	Vector2 getWorldPosition() const;
	float getWorldRotation() const;

	// Callbacks to reroute to Behaviours
	void onCollision(CollisionInfo info) const;
	void onTriggerEnter(Reference<Collider> other) const;
	void onTriggerStay(Reference<Collider> other) const;
	void onTriggerExit(Reference<Collider> other) const;

	Vector2 offset;
	bool isStatic;
	bool isTrigger;

protected:
	ColliderType m_colliderType;
};


#endif // !H_COLLIDER
