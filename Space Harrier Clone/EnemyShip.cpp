#include "EnemyShip.h"

#include "Engine/GameObject.h"
#include "Engine/Collider.h"
#include "PlayerShot.h"
#include "Messenger.h"
#include "MessengerEventType.h"


void EnemyShip::onTriggerEnter(Reference<Collider>& other)
{
	if (other->gameObject()->getComponent<PlayerShot>())
	{
		Messenger::broadcastEvent(MessengerEventType::POINTS_10000);
	}
}
