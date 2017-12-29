#include "BulletBouncer.h"

#include "Engine/API.h"
#include "Engine/Collider.h"
#include "Engine/GameObject.h"
#include "PlayerShot.h"


void BulletBouncer::awake()
{
	m_sfxBounce = Audio::LoadSFX("assets/audio/sfx/SFX - Bullet_Bounce.wav");
}


void BulletBouncer::onTriggerEnter(Reference<Collider>& other)
{
	Reference<PlayerShot> playerShot = other->gameObject()->getComponent<PlayerShot>();
	if (playerShot)
	{
		playerShot->bounceOut();
		Audio::PlaySFX(m_sfxBounce);
	}
}
