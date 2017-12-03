#ifndef H_PLAYER_COLLISION_CONTROLLER
#define H_PLAYER_COLLISION_CONTROLLER

#include "Engine/Behaviour.h"
#include "Engine/Reference.h"
class Collider;
class Player;


class PlayerCollisionController :
	public Behaviour
{
public:
	virtual void start() override;
	virtual void onTriggerEnter(Reference<Collider>& other) override;

private:
	Reference<Player> m_player;
};


#endif // !H_PLAYER_COLLISION_CONTROLLER
