#ifndef H_UI_MANAGER
#define H_UI_MANAGER

#include "Engine/Behaviour.h"
#include "MessengerEventListener.h"
#include "Engine/Reference.h"
#include "Engine/SFX.h"
class Sprite;
class TextRenderer;


class UIManager :
	public Behaviour,
	public MessengerEventListener
{
public:
	virtual void onDestroy() override;

	virtual void awake() override;
	virtual void start() override;
	virtual void update() override;

	// Inherited via MessengerEventListener
	virtual void eventsCallback(MessengerEventType eventType) override;

	int getTopScore() const;
	void setTopScore(int topScore);
	int getStageNumber() const;
	void setStageNumber(int stageNumber);

private:
	void updateTopScoreText();
	void updateScoreText();
	void updateLivesText();
	void updateStageText();

	void addPoints(int pointsToAdd);
	void showPostReviveMessage();
	void startInsertCoinsPrompt();
	void finishInsertCoinsPrompt();
	void handleGameOver();

	// Constant UI
	Reference<Sprite> m_topLabel;
	Reference<Sprite> m_scoreLabel;
	Reference<TextRenderer> m_stageLabel;
	Reference<TextRenderer> m_postReviveLabel;
	Reference<TextRenderer> m_stageNumberLabel;
	Reference<TextRenderer> m_stageNameLabel;
	Reference<TextRenderer> m_insertCoinsLabel;
	Reference<TextRenderer> m_postCoinsStartLabel;

	// Changing UI
	Reference<TextRenderer> m_topScoreText;
	Reference<TextRenderer> m_scoreText;
	Reference<TextRenderer> m_lifesText;
	Reference<TextRenderer> m_stageText;
	Reference<TextRenderer> m_insertCoinsCountdownText;

	// Points management
	int m_pointsPerStep;
	int m_pointsStepsPerSecond;
	bool m_shouldAddPoints;
	float m_pointsElapsedTime;
	float m_pointsTimeLimit;

	// Temporary message timers and info
	int m_totalElapsedTime;
	int m_hideStageInfoTime;
	int m_hidePostReviveLabelTime;
	int m_nextCountDownDropTime;
	int m_currentCountDownNumber;
	bool m_showingInsertCointsPrompt;

	SFX m_sfxCoin;

	int m_currentTopScore;
	int m_currentScore;
	int m_currentStage;
};


#endif // !H_UI_MANAGER
