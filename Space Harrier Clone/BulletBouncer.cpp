#include "BulletBouncer.h"

#include "Engine/Collider.h"
#include "Engine/GameObject.h"
#include "PlayerShot.h"


void BulletBouncer::onTriggerEnter(Reference<Collider>& other)
{
	Reference<PlayerShot> playerShot = other->gameObject()->getComponent<PlayerShot>();
	if (playerShot)
	{
		playerShot->bounceOut();
	}
}
