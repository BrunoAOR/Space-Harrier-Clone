#ifndef H_UI_MANAGER
#define H_UI_MANAGER

#include "Engine/Behaviour.h"
#include "MessengerEventListener.h"
#include "Engine/Reference.h"
class Sprite;
class TextRenderer;


class UIManager :
	public Behaviour,
	public MessengerEventListener
{
public:
	virtual ~UIManager();

	virtual void awake() override;
	virtual void start() override;
	virtual void update() override;

	// Inherited via MessengerEventListener
	virtual void eventsCallback(MessengerEventType eventType) override;

	int getTopScore() const;
	void setTopScore(int topScore);
	int getLivesCount() const;
	void setLivesCount(int livesCount);
	int getStageNumber() const;
	void setStageNumber(int stageNumber);

private:
	void updateTopScoreText();
	void updateScoreText();
	void updateLivesText();
	void updateStageText();

	void addPoints(int pointsToAdd);

	// Constant UI
	Reference<Sprite> m_topLabel;
	Reference<Sprite> m_scoreLabel;
	Reference<TextRenderer> m_stageLabel;

	// Changing UI
	Reference<TextRenderer> m_topScoreText;
	Reference<TextRenderer> m_scoreText;
	Reference<TextRenderer> m_lifesText;
	Reference<TextRenderer> m_stageText;

	int m_pointsPerStep;
	int m_pointsStepsPerSecond;
	bool m_shouldAddPoints;
	float m_elapsedTime;
	float m_pointsTimeLimit;

	int m_currentTopScore;
	int m_currentScore;
	int m_currentLives;
	int m_currentStage;
};


#endif // !H_UI_MANAGER
