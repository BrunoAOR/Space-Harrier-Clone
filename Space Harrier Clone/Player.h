#ifndef H_PLAYER
#define H_PLAYER

#include <vector>
#include "Engine/Behaviour.h"
#include "Engine/Reference.h"
#include "Engine/Vector2.h"
#include "Engine/SFX.h"
#include "Engine/Music.h"
#include "TimedAnimation.h"
#include "MessengerEventListener.h"
class GameObject;
class Transform;
class SpriteSheet;
class FloorManager;
class FloorObjectMover;
class Collider;
class GameObjectPool;
struct AnimationSection;
enum class ObjectEffectType;


class Player :
	public Behaviour, public MessengerEventListener
{
public:
	virtual void onDestroy() override;

	void init(const Reference<GameObject>& characterGo, const Reference<GameObject>& shadowGo);
	virtual void start() override;
	virtual void update() override;
	virtual void onTriggerEnter(Reference<Collider>& other) override;

	// Inherited via MessengerEventListener
	virtual void eventsCallback(MessengerEventType eventType) override;

	bool isAnimatingDeath() const;
	Reference<Transform> getCharacterTransform() const;
	Reference<FloorManager> floorManager;

private:
	enum class PlayerState
	{
		STOP,
		MOVE,
		SHORT_TRIP,
		LONG_TRIP,
		DIE,
		POST_DIE
	};

	// MOVE related functions
	void handleInput(float& normalizedRequestedX, float& normalizedRequestedY) const;
	void move(float normalizedRequestedX, float normalizedRequestedY, bool horizontalOnly = false, bool verticalOnly = false);
	void moveAnimationUpdate();

	// TRIP related functions
	void tripUpdate();

	// DIE related functions
	void dieUpdate();
	void postDieUpdate();
	void revive();

	// Collision handling
	void handleStateChangingCollision(ObjectEffectType oet);

	// Shooting
	void shoot() const;
	GameObjectPool* m_shotsPool = nullptr;

	bool m_isDead;

	bool m_isAnimatingDeath = false;

	Reference<GameObject> m_shadowGo;
	Reference<GameObject> m_characterGo;
	Reference<SpriteSheet> m_spriteSheet;
	TimedAnimation* m_dieAnimation = nullptr;
	int m_postDieElapsedTime = INT_MIN;

	std::string m_currentAnimation = "";
	float m_motionSpeed = 0;
	Vector2 m_currentNormalizedPosition;
	
	PlayerState m_state;

	// x-coordinates-related fields
	float m_minX = 0;
	float m_midX = 0;
	float m_maxX = 0;
	float m_xTarget = 0;

	// y-coordinates-related fields
	float m_minY = 0;
	float m_midY = 0;
	float m_maxY = 0;
	float m_yTarget = 0;

	SFX m_sfxTrip;
	SFX m_sfxDie;
	SFX m_sfxPostDie;
	SFX m_sfxShot;
};


#endif // !H_PLAYER
