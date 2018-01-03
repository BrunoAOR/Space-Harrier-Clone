#ifndef H_ENEMY_SHOT
#define H_ENEMY_SHOT

#include "Engine/Behaviour.h"
#include "MessengerEventListener.h"
#include "Engine/Reference.h"
#include "Engine/Vector2.h"
class FloorManager;
class SpriteSheet;
class Collider;
class PooledGameObject;


class EnemyShot :
	public Behaviour, public MessengerEventListener
{
public:
	void init(const Reference<FloorManager>& floorManager, const Vector2& startPos, float normalizedStartDepth, const Vector2& targetPos, float normalizedTargetDepth);
	virtual void onDestroy() override;
	virtual void awake() override;
	virtual void update() override;
	virtual void onTriggerEnter(Reference<Collider>& other) override;

	// Inherited via MessengerEventListener
	virtual void eventsCallback(MessengerEventType eventType) override;

private:
	Reference<FloorManager> m_floorManager;
	Reference<SpriteSheet> m_spriteSheet;
	Reference<Collider> m_collider;
	Reference<PooledGameObject> m_poolHandler;
	
	Vector2 m_startPos;
	Vector2 m_targetPos;
	float m_normalizedStartProgress;
	int m_fullMotionDuration;
	int m_elapsedTime;

	bool m_shouldFreezeInPlace = false;
};


#endif // !H_ENEMY_SHOT
