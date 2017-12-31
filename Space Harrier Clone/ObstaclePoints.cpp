#include "ObstaclePoints.h"

#include "Engine/GameObject.h"
#include "Engine/Collider.h"
#include "PlayerShot.h"
#include "Messenger.h"
#include "MessengerEventType.h"


void ObstaclePoints::onTriggerEnter(Reference<Collider>& other)
{
	if (other->gameObject()->getComponent<PlayerShot>())
	{
		if (bigPointsBonus)
		{
			Messenger::broadcastEvent(MessengerEventType::POINTS_10000);
		}
		else
		{
			Messenger::broadcastEvent(MessengerEventType::POINTS_5000);
		}
	}
}
