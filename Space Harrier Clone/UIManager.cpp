#include "UIManager.h"

#include <assert.h>
#include "Engine/globals.h"
#include "Engine/gameConfig.h"
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Engine/Sprite.h"
#include "Engine/TextRenderer.h"
#include "Engine/Font.h"
#include "Engine/API.h"
#include "Messenger.h"
#include "MessengerEventType.h"


void UIManager::onDestroy()
{
	Messenger::removeListener(this, MessengerEventType::PLAYER_LOSE_LIFE);
	Messenger::removeListener(this, MessengerEventType::PLAYER_DEAD);
	Messenger::removeListener(this, MessengerEventType::FLOOR_MOTION_STOPPED);
	Messenger::removeListener(this, MessengerEventType::FLOOR_MOTION_RESUMED);
	Messenger::removeListener(this, MessengerEventType::POINTS_5000);
	Messenger::removeListener(this, MessengerEventType::POINTS_10000);
	Messenger::removeListener(this, MessengerEventType::POINTS_100000);
}


void UIManager::awake()
{
	m_uiGO = GameObject::createNew();
	assert(m_uiGO);
	m_uiGO->transform->setParent(gameObject()->transform, false);

	// m_topLabel
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setParent(m_uiGO->transform);
		go->transform->setWorldPosition(Vector2(22, (float)SCREEN_HEIGHT - 14));
		m_topLabel = go->addComponent<Sprite>();
		assert(m_topLabel);

		m_topLabel->setRenderLayer("UI");
		m_topLabel->loadImage("assets/sprites/UI.png");
		m_topLabel->setAllPivots(Vector2(0, 1));
		m_topLabel->setClipRect(SDL_Rect{ 16, 104, 30, 12 });
	}

	// m_topValue
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setParent(m_uiGO->transform);
		go->transform->setWorldPosition(Vector2(120, (float)SCREEN_HEIGHT - 16));
		m_topScoreText = go->addComponent<TextRenderer>();
		assert(m_topScoreText);

		m_topScoreText->setRenderLayer("UI");
		m_topScoreText->setZIndex(1);

		bool success = m_topScoreText->loadFont(getFont("smallPink"));
		assert(success);
		m_topScoreText->setAllPivots(Vector2(1, 1));
		m_topScoreText->setText("");
	}

	// m_scoreLabel
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setParent(m_uiGO->transform);
		go->transform->setWorldPosition(Vector2((float)SCREEN_WIDTH - 82, (float)SCREEN_HEIGHT - 14));
		m_scoreLabel = go->addComponent<Sprite>();
		assert(m_scoreLabel);

		m_scoreLabel->setRenderLayer("UI");
		m_scoreLabel->loadImage("assets/sprites/UI.png");
		m_scoreLabel->setAllPivots(Vector2(1, 1));
		m_scoreLabel->setClipRect(SDL_Rect{ 46, 104, 48, 12 });
	}

	// m_scoreValue
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setParent(m_uiGO->transform);
		go->transform->setWorldPosition(Vector2((float)SCREEN_WIDTH - 16, (float)SCREEN_HEIGHT - 16));
		m_scoreText = go->addComponent<TextRenderer>();
		assert(m_scoreText);

		m_scoreText->setRenderLayer("UI");
		m_scoreText->setZIndex(1);

		bool success = m_scoreText->loadFont(getFont("smallGreen"));
		assert(success);
		m_scoreText->setAllPivots(Vector2(1, 1));
	}

	// m_lifesValue
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setParent(m_uiGO->transform);
		go->transform->setWorldPosition(Vector2(24, 8));
		m_lifesText = go->addComponent<TextRenderer>();
		assert(m_lifesText);

		m_lifesText->setRenderLayer("UI");

		bool success = m_lifesText->loadFont(getFont("lifeIcons"));
		assert(success);
		m_lifesText->setAllPivots(Vector2(0, 0));
	}

	// m_stageLabel;
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setParent(m_uiGO->transform);
		go->transform->setWorldPosition(Vector2((float)SCREEN_WIDTH - 56, 8));
		m_stageLabel = go->addComponent<TextRenderer>();
		assert(m_stageLabel);

		m_stageLabel->setRenderLayer("UI");
		m_stageLabel->setZIndex(1);

		bool success = m_stageLabel->loadFont(getFont("smallGray"));
		assert(success);
		m_stageLabel->setAllPivots(Vector2(1, 0));
		m_stageLabel->setText("STAGE");
	}

	// m_stageValue
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setParent(m_uiGO->transform);
		go->transform->setWorldPosition(Vector2((float)SCREEN_WIDTH - 32, 8));
		m_stageText = go->addComponent<TextRenderer>();
		assert(m_stageText);

		m_stageText->setRenderLayer("UI");
		m_stageText->setZIndex(1);

		bool success = m_stageText->loadFont(getFont("smallGray"));
		assert(success);
		m_stageText->setAllPivots(Vector2(1, 0));
	}

	// m_stageNumberLabel
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setParent(m_uiGO->transform);
		go->transform->setWorldPosition(Vector2(SCREEN_WIDTH / 2.0f, (float)SCREEN_HEIGHT - 80));
		m_stageNumberLabel = go->addComponent<TextRenderer>();
		assert(m_stageNumberLabel);

		m_stageNumberLabel->setRenderLayer("UI");
		m_stageNumberLabel->setZIndex(1);

		bool success = m_stageNumberLabel->loadFont(getFont("bigGray"));
		assert(success);
		m_stageNumberLabel->setAllPivots(Vector2(0.5f, 1));
		m_stageNumberLabel->setText("STAGE 1");
	}

	// m_stageNameLabel
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setParent(m_uiGO->transform);
		go->transform->setWorldPosition(Vector2(SCREEN_WIDTH / 2.0f, (float)SCREEN_HEIGHT - 104));
		m_stageNameLabel = go->addComponent<TextRenderer>();
		assert(m_stageNameLabel);

		m_stageNameLabel->setRenderLayer("UI");
		m_stageNameLabel->setZIndex(1);

		bool success = m_stageNameLabel->loadFont(getFont("bigGray"));
		assert(success);
		m_stageNameLabel->setAllPivots(Vector2(0.5f, 1));
		m_stageNameLabel->setText("MOOT");
	}

	// m_reviveLabel
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setParent(m_uiGO->transform);
		go->transform->setWorldPosition(Vector2(SCREEN_WIDTH / 2.0f, (float)SCREEN_HEIGHT - 80));
		m_postReviveLabel = go->addComponent<TextRenderer>();
		assert(m_postReviveLabel);

		m_postReviveLabel->setRenderLayer("UI");
		m_postReviveLabel->setZIndex(1);

		bool success = m_postReviveLabel->loadFont(getFont("smallGreen"));
		assert(success);
		m_postReviveLabel->setAllPivots(Vector2(0.5f, 1));
		m_postReviveLabel->setText("        READY ?\n\nMANY MORE BATTLE SCENES\n\nWILL SOON BE AVAILABLE !");

		m_postReviveLabel->setActive(false);
	}

	// m_insertCoinsLabel
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setParent(m_uiGO->transform);
		go->transform->setWorldPosition(Vector2(SCREEN_WIDTH / 2.0f, (float)SCREEN_HEIGHT - 88));
		m_insertCoinsLabel = go->addComponent<TextRenderer>();
		assert(m_insertCoinsLabel);

		m_insertCoinsLabel->setRenderLayer("UI");
		m_insertCoinsLabel->setZIndex(1);

		bool success = m_insertCoinsLabel->loadFont(getFont("smallPink"));
		assert(success);
		m_insertCoinsLabel->setAllPivots(Vector2(0.5f, 1));
		m_insertCoinsLabel->setText("    CONTINUE PLAY\n\n    INSERT COINS\n\nWITHIN 10 COUNT DOWN");

		m_insertCoinsLabel->setActive(false);
	}

	// m_insertCoinsCountdownText
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setParent(m_uiGO->transform);
		go->transform->setWorldPosition(Vector2((float)SCREEN_WIDTH - 152 , (float)SCREEN_HEIGHT - 136));
		m_insertCoinsCountdownText = go->addComponent<TextRenderer>();
		assert(m_insertCoinsCountdownText);

		m_insertCoinsCountdownText->setRenderLayer("UI");
		m_insertCoinsCountdownText->setZIndex(1);

		bool success = m_insertCoinsCountdownText->loadFont(getFont("bigPink"));
		assert(success);
		m_insertCoinsCountdownText->setAllPivots(Vector2(1, 1));
		m_insertCoinsCountdownText->setText("10");

		m_insertCoinsCountdownText->setActive(false);
	}

	// m_postCoinsStartLabel
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setParent(m_uiGO->transform);
		go->transform->setWorldPosition(Vector2(SCREEN_WIDTH / 2.0f, (float)SCREEN_HEIGHT - 72));
		m_postCoinsStartLabel = go->addComponent<TextRenderer>();
		assert(m_postCoinsStartLabel);

		m_postCoinsStartLabel->setRenderLayer("UI");
		m_postCoinsStartLabel->setZIndex(1);

		bool success = m_postCoinsStartLabel->loadFont(getFont("smallGreen"));
		assert(success);
		m_postCoinsStartLabel->setAllPivots(Vector2(0.5f, 1));
		m_postCoinsStartLabel->setText("PUSH START BUTTON ");

		m_postCoinsStartLabel->setActive(false);
	}

	m_sfxCoin = Audio::LoadSFX("assets/audio/sfx/SFX - Coin.wav");
}


void UIManager::start()
{
	Messenger::addListener(this, MessengerEventType::PLAYER_LOSE_LIFE);
	Messenger::addListener(this, MessengerEventType::PLAYER_DEAD);
	Messenger::addListener(this, MessengerEventType::FLOOR_MOTION_STOPPED);
	Messenger::addListener(this, MessengerEventType::FLOOR_MOTION_RESUMED);
	Messenger::addListener(this, MessengerEventType::POINTS_5000);
	Messenger::addListener(this, MessengerEventType::POINTS_10000);
	Messenger::addListener(this, MessengerEventType::POINTS_100000);

	m_pointsPerStep = 10;
	m_pointsStepsPerSecond = 15;
	m_shouldAddPoints = true;
	m_pointsElapsedTime = 0;
	m_pointsTimeLimit = 1000.0f / 15;

	m_totalElapsedTime = 0;
	m_hidePostReviveLabelTime = -1;
	m_hideStageInfoTime = 4000;
	m_nextCountDownDropTime = -1;
	m_currentCountDownNumber = 10;

	m_currentTopScore = 1000000;
	m_currentScore = 0;
	m_currentStage = 1;
	updateTopScoreText();
	updateScoreText();
	updateLivesText();
	updateStageText();
}


void UIManager::update()
{
	if (!m_isActive)
	{
		return;
	}

	// Handle input (coins)
	if (Input::getKeyDown(SDL_SCANCODE_Q))
	{
		Audio::PlaySFX(m_sfxCoin);
		player_lives += LIVES_PER_COIN;
		updateLivesText();
		if (m_showingInsertCointsPrompt)
		{
			m_postCoinsStartLabel->setActive(true);
		}
	}

	if (m_showingInsertCointsPrompt && player_lives > 0 && Input::getKeyDown(SDL_SCANCODE_LCTRL))
	{
		finishInsertCoinsPrompt();
	}

	// Points adding
	if (m_pointsElapsedTime >= m_pointsTimeLimit)
	{
		m_pointsElapsedTime -= m_pointsTimeLimit;
		m_currentScore += m_pointsPerStep;
		updateScoreText();
	}

	if (m_shouldAddPoints)
	{
		m_pointsElapsedTime += Time::deltaTime();
	}

	// Handling messages
	
	// Stage info
	if (m_hideStageInfoTime != -1 && m_totalElapsedTime >= m_hideStageInfoTime)
	{
		m_hideStageInfoTime = -1;
		m_stageNameLabel->setActive(false);
		m_stageNumberLabel->setActive(false);
	}

	// Post revive
	if (m_hidePostReviveLabelTime != -1 && m_totalElapsedTime >= m_hidePostReviveLabelTime)
	{
		m_hidePostReviveLabelTime = -1;
		m_postReviveLabel->setActive(false);
	}

	// Insert coins prompt countdown
	if (m_nextCountDownDropTime != -1 && m_totalElapsedTime >= m_nextCountDownDropTime)
	{
		if (m_currentCountDownNumber > 0)
		{
			m_insertCoinsCountdownText->setText(std::to_string(--m_currentCountDownNumber));
			m_nextCountDownDropTime = m_totalElapsedTime + 1000;
		}
		else
		{
			// So, either player loses or coins have been inserted
			finishInsertCoinsPrompt();
		}
	}

	m_totalElapsedTime += Time::deltaTime();
}


void UIManager::eventsCallback(MessengerEventType eventType)
{
	switch (eventType)
	{
	case MessengerEventType::PLAYER_LOSE_LIFE:
		updateLivesText();
		break;
	case MessengerEventType::PLAYER_DEAD:
		startInsertCoinsPrompt();
		break;
	case MessengerEventType::FLOOR_MOTION_STOPPED:
		m_shouldAddPoints = false;
		break;
	case MessengerEventType::FLOOR_MOTION_RESUMED:
		m_shouldAddPoints = true;
		showPostReviveMessage();
		break;
	case MessengerEventType::POINTS_5000:
		addPoints(5000);
		break;
	case MessengerEventType::POINTS_10000:
		addPoints(10000);
		break;
	case MessengerEventType::POINTS_100000:
		addPoints(100000);
		break;
	default:
		break;
	}	
}


int UIManager::getTopScore() const
{
	return m_currentTopScore;
}


void UIManager::setTopScore(int topScore)
{
	if (topScore < 0)
	{
		OutputLog("WARNING: Attempting to set the UI top score to a negative value (%i). The top score will be set to zero.", topScore);
		topScore = 0;
	}
	m_currentTopScore = topScore;
	updateTopScoreText();
}


int UIManager::getStageNumber() const
{
	return m_currentStage;
}


void UIManager::setStageNumber(int stageNumber)
{
	if (stageNumber < 1)
	{
		OutputLog("WARNING: Attempting to set the UI stage number to a negative value (%i). The stage number will be set to one.", stageNumber);
		stageNumber = 1;
	}
	m_currentStage = stageNumber;
	updateStageText();
}


void UIManager::updateTopScoreText()
{
	m_topScoreText->setText(std::to_string(m_currentTopScore));
}


void UIManager::updateScoreText()
{
	if (m_currentScore > m_currentTopScore)	
	{
		m_currentTopScore = m_currentScore;
		m_topScoreText->setText(std::to_string(m_currentTopScore));
	}
	m_scoreText->setText(std::to_string(m_currentScore));
}


void UIManager::updateLivesText()
{
	if (player_lives < 0)
	{
		OutputLog("WARNING: Attempting to set the UI lives count to a negative value (%i). The lives count will be set to zero.", player_lives);
		player_lives = 0;
	}

	std::string livesText = "";
	int livesToShow = (player_lives % 100) - 1;
	
	int smallIcons = livesToShow % 10;
	int largeIcons = livesToShow / 10;

	for (int i = 0; i < largeIcons; ++i)
	{
		livesText += "L";
	}
	for (int i = 0; i < smallIcons; ++i)
	{
		livesText += "s";
	}

	m_lifesText->setText(livesText);
}


void UIManager::updateStageText()
{
	m_stageText->setText(std::to_string(m_currentStage));
}


void UIManager::addPoints(int pointsToAdd)
{
	m_currentScore += pointsToAdd;
	updateScoreText();
}


void UIManager::showPostReviveMessage()
{
	m_postReviveLabel->setActive(true);
	m_hidePostReviveLabelTime = m_totalElapsedTime + 2000;
}


void UIManager::startInsertCoinsPrompt()
{
	m_currentCountDownNumber = 10;
	m_showingInsertCointsPrompt = true;
	m_insertCoinsLabel->setActive(true);
	m_insertCoinsCountdownText->setActive(true);
	m_insertCoinsCountdownText->setText(std::to_string(m_currentCountDownNumber));
	m_nextCountDownDropTime = m_totalElapsedTime + 1000;
}


void UIManager::finishInsertCoinsPrompt()
{
	m_showingInsertCointsPrompt = false;
	m_nextCountDownDropTime = -1;
	m_insertCoinsLabel->setActive(false);
	m_insertCoinsCountdownText->setActive(false);
	m_postCoinsStartLabel->setActive(false);
	if (player_lives > 0)
	{
		Messenger::broadcastEvent(MessengerEventType::PLAYER_REVIVED);
	}
	else
	{
		handleGameOver();
	}
}


void UIManager::handleGameOver()
{
	m_uiGO->setActive(false);
	m_isActive = false;
	Audio::StopMusic();

	OutputLog("GAME OVER");
	Messenger::broadcastEvent(MessengerEventType::GAME_OVER);
	Messenger::broadcastEvent(MessengerEventType::CHANGE_SCENE);
}
