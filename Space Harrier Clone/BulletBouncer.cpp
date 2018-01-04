#include "BulletBouncer.h"

#include "Engine/API.h"
#include "Engine/Collider.h"
#include "Engine/GameObject.h"
#include "PlayerShot.h"


void BulletBouncer::onDestroy()
{
	Audio::unloadSFX(m_sfxBounce);
}


void BulletBouncer::awake()
{
	m_sfxBounce = Audio::loadSFX("assets/audio/sfx/SFX - Bullet_Bounce.wav");
}


void BulletBouncer::onTriggerEnter(Reference<Collider>& other)
{
	Reference<PlayerShot> playerShot = other->gameObject()->getComponent<PlayerShot>();
	if (playerShot)
	{
		playerShot->bounceOut();
		Audio::playSFX(m_sfxBounce);
	}
}
