#ifndef H_EXPLOSIVE_OBJECT
#define H_EXPLOSIVE_OBJECT

#include "Engine/Behaviour.h"
#include "Engine/Reference.h"
#include "Engine/SFX.h"
class Collider;
class GameObjectPool;
class PooledGameObject;
class FloorObjectMover;
class Enemy;


class ExplosiveObject :
	public Behaviour
{
public:
	void init(GameObjectPool* explosionPool, SFX explosionSFX);
	virtual void start() override;
	virtual void onTriggerEnter(Reference<Collider>& other) override;

private:
	// m_explosionPool is used to spawn explosions when this GameObject gets hit by the player
	GameObjectPool* m_explosionPool = nullptr;
	SFX m_sfxExplosion;

	// m_poolHandler is used to return this GameObject to the pool
	Reference<PooledGameObject> m_poolHandler;

	Reference<FloorObjectMover> m_floorObjectMover;
	Reference<Enemy> m_enemy;
};


#endif // !H_EXPLOSIVE_OBJECT
