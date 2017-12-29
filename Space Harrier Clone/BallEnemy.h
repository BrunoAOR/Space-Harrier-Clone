#ifndef H_BALL_ENEMY
#define H_BALL_ENEMY

#include "Enemy.h"
class ExplosiveObject;
class BulletBouncer;

class BallEnemy :
	public Enemy
{
public:
	virtual void init(int lifeTimeMS, const MotionPattern& motionPattern, const Reference<FloorManager>& floorManager, const Reference<Transform>& playerTransform, GameObjectPool* enemyShotPool, const SFX& sfxEnemyShot) override;
	virtual void update() override;

private:
	bool m_shootable;
	Reference<ExplosiveObject> m_explosiveObject;
	Reference<BulletBouncer> m_bulletBouncer;
};


#endif // !H_BALL_ENEMY
