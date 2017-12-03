#ifndef H_COLLIDER
#define H_COLLIDER

#include <string>
#include "Component.h"
#include "Reference.h"
#include "Vector2.h"
class CollidersManager;
struct CollisionInfo;
enum class ColliderType;


class Collider :
	public Component
{
	friend class CollidersManager;

public:
	Collider();
	virtual ~Collider() = 0;

	Vector2 getLocalScaledOffset() const;
	Vector2 getWorldScaledOffset() const;

	Vector2 getLocalPosition() const;
	Vector2 getWorldPosition() const;
	float getWorldRotation() const;

	std::string getCollisionLayer();
	bool setCollisionLayer(const std::string& newLayerName);

	// Callbacks to reroute to Behaviours
	void onCollision(CollisionInfo& info) const;
	void onTriggerEnter(Reference<Collider>& other) const;
	void onTriggerStay(Reference<Collider>& other) const;
	void onTriggerExit(Reference<Collider>& other) const;

	Vector2 offset;
	bool isStatic;
	bool isTrigger;
	int zIndex;

protected:
	ColliderType m_colliderType;

private:
	std::string m_collisionLayer;
	CollidersManager* m_collidersManager = nullptr;
};


#endif // !H_COLLIDER
