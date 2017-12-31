#ifndef H_ENEMY_BALL
#define H_ENEMY_BALL

#include "Enemy.h"
#include "Engine/Reference.h"
class ExplosiveObject;
class BulletBouncer;
class Collider;

class EnemyBall :
	public Enemy
{
public:
	virtual void init(int lifeTimeMS, const MotionPattern& motionPattern, const Reference<FloorManager>& floorManager, const Reference<Transform>& playerTransform, GameObjectPool* enemyShotPool, const SFX& sfxEnemyShot) override;
	virtual void update() override;
	virtual void onTriggerEnter(Reference<Collider>& other) override;

private:
	bool m_shootable;
	Reference<ExplosiveObject> m_explosiveObject;
	Reference<BulletBouncer> m_bulletBouncer;
};


#endif // !H_ENEMY_BALL
