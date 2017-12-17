#ifndef H_COLLISION_CALLBACK_FORWARDER
#define H_COLLISION_CALLBACK_FORWARDER

#include "Engine/Behaviour.h"
#include "Engine/Reference.h"
class Collider;
class Behaviour;
struct CollisionInfo;


class CollisionCallbackForwarder :
	public Behaviour
{
public:
	virtual void onCollision(CollisionInfo& info) override;
	virtual void onTriggerEnter(Reference<Collider>& other) override;
	virtual void onTriggerStay(Reference<Collider>& other) override;
	virtual void onTriggerExit(Reference<Collider>& other) override;

	Reference<Behaviour> target;	
};


#endif // !H_COLLISION_CALLBACK_FORWARDER
