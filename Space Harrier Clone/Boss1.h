#ifndef H_BOSS_1
#define H_BOSS_1

#include "Engine/Behaviour.h"
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
	public Behaviour
{
public:
	virtual void onDestroy();
	void init(const Reference<FloorManager>& floorManager, const Reference<Transform>& playerTransform, SFX explosionSFX);
	virtual void awake() override;
	virtual void start() override;
	virtual void update() override;
	virtual void onTriggerEnter(Reference<Collider>& other);


private:
	void faceDirection(bool toFront, bool forceUpdate = false);
	void die();

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
	
	float m_xPos;
	float m_yPos;
	float m_absoluteDepth;
	int m_zIndex;
	Vector2 m_scale;

	// Position information
	Vector2 m_currentPosition;
	float m_normalizedDepth;
	int m_sideFlipFactor;

	Boss1ChainConfig m_chainConfig;
	int m_deathElapsedTime = -1;
};


#endif // !H_BOSS_1
