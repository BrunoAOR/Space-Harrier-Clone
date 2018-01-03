#ifndef H_BOSS_1
#define H_BOSS_1

#include "Engine/Behaviour.h"
#include "MessengerEventListener.h"
#include "Engine/Reference.h"
#include "Engine/Vector2.h"
#include "Engine/SFX.h"
#include "Boss1ChainConfig.h"
class Transform;
class Collider;
class Sprite;
class FloorManager;
class GameObjectPool;
class Boss1ChainLink;


class Boss1 :
	public Behaviour, public MessengerEventListener
{
public:
	virtual void onDestroy();
	void init(const Reference<FloorManager>& floorManager, const Reference<Transform>& playerTransform, SFX explosionSFX);
	virtual void awake() override;
	virtual void start() override;
	virtual void update() override;
	virtual void onTriggerEnter(Reference<Collider>& other);

	// Inherited via MessengerEventListener
	virtual void eventsCallback(MessengerEventType eventType) override;

private:
	void faceDirection(bool toFront, bool forceUpdate = false);
	void shoot(int cycleTime);
	void die();

	bool m_playerDead;

	Reference<FloorManager> m_floorManager;
	Reference<Transform> m_playerTransform;
	SFX m_sfxExplosion;

	Reference<Boss1ChainLink> m_nextLink;
	int m_spriteSetsCount;
	SFX m_sfxBossShot;
	GameObjectPool* m_shotsPool = nullptr;
	Reference<Collider> m_collider;
	Reference<Sprite> m_shadowSprite;
	Reference<Sprite> m_headSprite;
	int m_currentSpritesSet;

	int m_elapsedTime;
	bool m_facingFront;

	// Shooting
	int m_nextShotIndex;
	bool m_cycleShotsDone;
	int m_lastCycleTime;
	
	// Position information
	float m_xPos;
	float m_yPos;
	float m_absoluteDepth;
	int m_zIndex;
	Vector2 m_scale;

	float m_currentnormalizedDepth;

	int m_sideFlipFactor;

	Boss1ChainConfig m_chainConfig;
	int m_deathElapsedTime = -1;
};


#endif // !H_BOSS_1
