#ifndef H_GAME_SCENE_MUSIC_MANAGER
#define H_GAME_SCENE_MUSIC_MANAGER

#include "Engine/Behaviour.h"
#include "Engine/Music.h"
#include "Engine/SFX.h"
#include "MessengerEventListener.h"


class GameSceneMusicManager :
	public Behaviour, public MessengerEventListener
{
public:
	virtual void onDestroy() override;
	virtual void awake() override;
	virtual void start() override;

	// Inherited via MessengerEventListener
	virtual void eventsCallback(MessengerEventType eventType) override;

private:
	Music m_musicLevel;
	Music m_musicBoss;
	SFX m_sfxWelcome;
};


#endif // !H_GAME_SCENE_MUSIC_MANAGER
