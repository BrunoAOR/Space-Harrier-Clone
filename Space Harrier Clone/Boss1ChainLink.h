#ifndef H_BOSS_1_CHAIN_LINK
#define H_BOSS_1_CHAIN_LINK

#include <deque>
#include "Engine/Behaviour.h"
#include "Engine/Reference.h"
#include "Engine/Vector2.h"
#include "Engine/SFX.h"
#include "Boss1ChainConfig.h"
class Transform;
class Collider;
class Sprite;
class FloorManager;


class Boss1ChainLink :
	public Behaviour
{
public:
	void init(const Reference<FloorManager>& floorManager, const Reference<Transform>& playerTransform, Reference<Transform>& parentTransform, const SFX& explosionSFX, const Boss1ChainConfig& chainConfig, int motionDelayMS, int previousLinkMotionDelayMS);
	virtual void awake() override;
	virtual void start() override;
	virtual void update() override;

	void updateSpriteSet(int spriteSet);
	void setNextLink(const Reference<Boss1ChainLink>& nextLink);
	void setAsTail(bool isTail = true);
	void requestElapsedTimeSideFlip(int elapsedTimeForFlip);
	void requestElapsedTimeDeath(int elapsedTimeForDeath);
	void setPlayerDead(bool playerDead);

private:
	void updateSideFlipFactor();
	void die();

	Reference<FloorManager> m_floorManager;
	Reference<Transform> m_playerTransform;
	SFX m_sfxExplosion;

	bool m_playerDead;

	Reference<Collider> m_collider;
	Reference<Sprite> m_shadowSprite;
	Reference<Sprite> m_chainLinkSprite;
	
	Reference<Boss1ChainLink> m_nextLink;

	int m_elapsedTime;
	int m_deathElapsedTime = -1;

	float m_xPos;
	float m_yPos;
	float m_absoluteDepth;
	int m_zIndex;
	Vector2 m_scale;

	int m_sideFlipFactor;
	std::deque<int> m_sideFlipTimes;

	Boss1ChainConfig m_chainConfig;

	bool m_isTail;
};


#endif // !H_BOSS_1_CHAIN_LINK
