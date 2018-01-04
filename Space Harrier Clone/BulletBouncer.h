#ifndef H_BULLET_BOUNCER
#define H_BULLET_BOUNCER

#include "Engine/Behaviour.h"
#include "Engine/Reference.h"
#include "Engine/SFX.h"
class Collider;


class BulletBouncer :
	public Behaviour
{
public:
	virtual void onDestroy() override;
	virtual void awake() override;
	virtual void onTriggerEnter(Reference<Collider>& other) override;

private:
	SFX m_sfxBounce;
};


#endif // !H_BULLET_BOUNCER
