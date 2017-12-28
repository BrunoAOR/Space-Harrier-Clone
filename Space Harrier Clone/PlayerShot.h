#ifndef H_PLAYER_SHOT
#define H_PLAYER_SHOT

#include "Engine/Behaviour.h"
#include "Engine/Reference.h"
class FloorManager;
class Vector2;
class SpriteSheet;
class Collider;
class PooledGameObject;


class PlayerShot :
	public Behaviour
{
public:
	void init(const Reference<FloorManager>& floorManager, Vector2 startPos);
	virtual void update() override;
	virtual void onTriggerEnter(Reference<Collider>& other) override;

private:
	Reference<FloorManager> m_floorManager;
	Reference<SpriteSheet> m_spriteSheet;
	Reference<Collider> m_collider;
	Reference<PooledGameObject> m_poolHandler;
	float m_startScale;
	float m_endScale;
	int m_shotDuration;
	float m_elapsedTime;
};


#endif // !H_PLAYER_SHOT