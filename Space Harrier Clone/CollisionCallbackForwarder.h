#ifndef H_COLLISION_CALLBACK_FORWARDER
#define H_COLLISION_CALLBACK_FORWARDER

#include <vector>
#include "Engine/Behaviour.h"
#include "Engine/Reference.h"
class Collider;
class Behaviour;
struct CollisionInfo;


class CollisionCallbackForwarder :
	public Behaviour
{
public:
	void addTarget(const Reference<Behaviour>& newTarget);

	virtual void onCollision(CollisionInfo& info) override;
	virtual void onTriggerEnter(Reference<Collider>& other) override;
	virtual void onTriggerStay(Reference<Collider>& other) override;
	virtual void onTriggerExit(Reference<Collider>& other) override;

private:
	std::vector<Reference<Behaviour>> m_targets;	
};


#endif // !H_COLLISION_CALLBACK_FORWARDER
