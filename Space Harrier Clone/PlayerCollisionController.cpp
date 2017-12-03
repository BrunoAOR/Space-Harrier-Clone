#include "PlayerCollisionController.h"

#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Player.h"


void PlayerCollisionController::start()
{
	m_player = gameObject()->transform->getParent()->gameObject()->getComponent<Player>();
	assert(m_player);
}


void PlayerCollisionController::onTriggerEnter(Reference<Collider>& other)
{
	m_player->onTriggerEnter(other);
}
