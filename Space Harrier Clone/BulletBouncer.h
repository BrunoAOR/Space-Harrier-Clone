#ifndef H_BULLET_BOUNCER
#define H_BULLET_BOUNCER

#include "Engine/Behaviour.h"
#include "Engine/Reference.h"
class Collider;


class BulletBouncer :
	public Behaviour
{
public:
	virtual void onTriggerEnter(Reference<Collider>& other) override;
};


#endif // !H_BULLET_BOUNCER
