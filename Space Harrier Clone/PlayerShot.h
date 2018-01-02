#ifndef H_PLAYER_SHOT
#define H_PLAYER_SHOT

#include "Engine/Behaviour.h"
#include "Engine/Reference.h"
#include "Engine/Vector2.h"
class FloorManager;
class SpriteSheet;
class Collider;
class PooledGameObject;


class PlayerShot :
	public Behaviour
{
public:
	void init(const Reference<FloorManager>& floorManager, Vector2 startPos);
	virtual void update() override;
	void bounceOut();
	void destroy();

private:
	void fly();
	void bounce();

	Reference<FloorManager> m_floorManager;
	Reference<SpriteSheet> m_spriteSheet;
	Reference<Collider> m_collider;
	Reference<PooledGameObject> m_poolHandler;
	
	// fly
	float m_startScale;
	float m_endScale;
	int m_shotDuration;
	float m_elapsedTime;

	// bounce
	int m_bounceDuration;
	Vector2 m_bounceStart;
	Vector2 m_bounceTarget;
	float m_bounceClearanceDistance;
	bool m_bounced;
};


#endif // !H_PLAYER_SHOT
