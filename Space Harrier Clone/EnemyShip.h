#ifndef H_SHIP_ENEMY
#define H_SHIP_ENEMY

#include "Enemy.h"
#include "Engine/Reference.h"
class Collider;


class EnemyShip :
	public Enemy
{
public:
	virtual void onTriggerEnter(Reference<Collider>& other) override;
};


#endif // !H_SHIP_ENEMY
