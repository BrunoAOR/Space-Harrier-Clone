#ifndef H_PLAYER_SHOT
#define H_PLAYER_SHOT

#include "Engine/Behaviour.h"
#include "Engine/Reference.h"
class Vector2;
class SpriteSheet;
class PooledGameObject;
class Collider;
class FloorManager;


class PlayerShot :
	public Behaviour
{
public:
	void init(const Vector2& startPos, const Reference<FloorManager>& floorManager);
	virtual void update() override;
	virtual void onTriggerEnter(Reference<Collider>& other) override;

private:
	Reference<SpriteSheet> m_spriteSheet;
	Reference<PooledGameObject> m_poolHandler;
	Reference<Collider> m_collider;
	Reference<FloorManager> m_floorManager;
	float m_startScale;
	float m_endScale;
	int m_shotDuration;
	float m_elapsedTime;
};


#endif // !H_PLAYER_SHOT
