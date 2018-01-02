#ifndef H_BEHAVIOUR
#define H_BEHAVIOUR

#include "Component.h"
#include "Reference.h"
class Collider;
struct CollisionInfo;


class Behaviour :
	public Component
{
	friend class BehavioursManager;

public:	
	Behaviour();
	virtual ~Behaviour() = 0;

	// Defining methods for behaviours to implement
	// Lifecycle related
	virtual void awake();
	virtual void start();
	virtual void update();
	virtual void onDestroy();
	// Collisions related
	virtual void onCollision(CollisionInfo& info);
	virtual void onTriggerEnter(Reference<Collider>& other);
	virtual void onTriggerStay(Reference<Collider>& other);
	virtual void onTriggerExit(Reference<Collider>& other);

private:
	bool m_isAwake;
	bool m_started;
};


#endif // !H_BEHAVIOUR
