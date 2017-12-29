#ifndef H_ENEMY
#define H_ENEMY

#include "Engine/Behaviour.h"
#include "Engine/Reference.h"
#include "Engine/SFX.h"
#include "MotionPattern.h"
class Transform;
class Collider;
class SpriteSheet;
class GameObject;
class FloorManager;
class PooledGameObject;
class Explosion;
class GameObjectPool;


class Enemy :
	public Behaviour
{
public:
	virtual void init(int lifeTimeMS, const MotionPattern& motionPattern, const Reference<FloorManager>& floorManager, const Reference<Transform>& playerTransform, GameObjectPool* enemyShotPool, const SFX& sfxEnemyShot);
	virtual void update() override;

	void setupExplosion(Reference<Explosion>& explosion);

protected:
	void shoot(MotionPatternPoint mpp);

	Reference<Collider> m_collider;

	MotionPattern m_motionPattern;
	Reference<FloorManager> m_floorManager;
	Reference<Transform> m_playerTransform;
	Reference<SpriteSheet> m_spriteSheet;
	Reference<GameObject> m_characterGo;
	Reference<GameObject> m_shadowGo;
	Reference<PooledGameObject> m_poolHandler;
	GameObjectPool* m_enemyShotPool = nullptr;
	SFX m_sfxEnemyShot;

	int m_lifeTimeMS;
	int m_elapsedTime;
	int m_lastTriggeredActionId = -1;
};


#endif // !H_ENEMY
