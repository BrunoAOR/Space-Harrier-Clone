#ifndef H_HOME_SCENE_MANAGER
#define H_HOME_SCENE_MANAGER

#include "Engine/Behaviour.h"
#include "Engine/Reference.h"
#include "Engine/Vector2.h"
#include "Engine/SFX.h"
class SpriteSheet;
class TextRenderer;


class HomeSceneManager :
	public Behaviour
{
public:
	virtual void onDestroy() override;
	virtual void awake() override;
	virtual void start() override;
	virtual void update() override;

private:
	virtual void togglePrompts(bool activeState);

	bool m_shouldHandleInput;

	Reference<SpriteSheet> m_gameTitle;
	Reference<SpriteSheet> m_mammoth;
	Reference<SpriteSheet> m_character;
	Reference<SpriteSheet> m_robotHighlights;
	Reference<SpriteSheet> m_robotEyes;
	Reference<SpriteSheet> m_robotShine;

	Reference<TextRenderer> m_insertCoinsPrompt;
	Reference<TextRenderer> m_pushStartPrompt;

	Reference<TextRenderer> m_livesValue;
	SFX m_sfxCoin;

	int m_maxAnimationFrames;
	float m_totalAnimationCycleTimeMS;

	float m_gameTitleScale;
	float m_gameTitleElapsedTime;
	
	bool m_robotShineInMotion;
	float m_robotShineElapsedTime;
	float m_animationSpeed;
	Vector2 m_robotShineStartPos;
	Vector2 m_robotShineEndPos;

	int m_playerLives;
	int m_promptsShowTime;
	int m_promptsHideTime;
	int m_promptsElapsedTime;
	bool m_promptsShowing;
};


#endif // !H_HOME_SCENE_MANAGER
