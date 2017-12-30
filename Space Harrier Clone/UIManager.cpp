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

void UIManager::awake()
{
	// m_topLabel
	{
		auto go = GameObject::createNew();
		assert(go);
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
		go->transform->setWorldPosition(Vector2((float)SCREEN_WIDTH - 16, (float)SCREEN_HEIGHT - 16));
		m_scoreText = go->addComponent<TextRenderer>();
		assert(m_scoreText);

		m_scoreText->setRenderLayer("UI");
		m_scoreText->setZIndex(1);

		bool success = m_scoreText->loadFont(getFont("smallGreen"));
		assert(success);
		m_scoreText->setAllPivots(Vector2(1, 1));
		m_scoreText->setText("");
	}

	// m_lifesValue
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setWorldPosition(Vector2(24, 8));
		m_lifesText = go->addComponent<TextRenderer>();
		assert(m_lifesText);

		m_lifesText->setRenderLayer("UI");

		bool success = m_lifesText->loadFont(getFont("lifeIcons"));
		assert(success);
		m_lifesText->setAllPivots(Vector2(0, 0));
		m_lifesText->setText("");
	}

	// m_stageLabel;
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setWorldPosition(Vector2((float)SCREEN_WIDTH - 56, 8));
		m_stageLabel = go->addComponent<TextRenderer>();
		assert(m_scoreLabel);

		m_scoreLabel->setRenderLayer("UI");

		bool success = m_stageLabel->loadFont(getFont("smallGray"));
		assert(success);
		m_stageLabel->setAllPivots(Vector2(1, 0));
		m_stageLabel->setText("STAGE");
	}

	// m_stageValue
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setWorldPosition(Vector2((float)SCREEN_WIDTH - 32, 8));
		m_stageText = go->addComponent<TextRenderer>();
		assert(m_stageText);

		m_stageText->setRenderLayer("UI");
		m_stageText->setZIndex(1);

		bool success = m_stageText->loadFont(getFont("smallGray"));
		assert(success);
		m_stageText->setAllPivots(Vector2(1, 0));
		m_stageText->setText("");
	}
}


void UIManager::start()
{
	m_pointsPerStep = 10;
	m_pointsStepsPerSecond = 15;
	m_elapsedTime = 0;
	m_pointsTimeLimit = 1000.0f / 15;

	m_currentTopScore = 1000000;
	m_currentScore = 0;
	m_currentLives = 5;
	m_currentStage = 1;
	updateTopScoreText();
	updateScoreText();
	updateLivesText();
	updateStageText();
}


void UIManager::update()
{
	if (m_elapsedTime >= m_pointsTimeLimit)
	{
		m_elapsedTime -= m_pointsTimeLimit;
		m_currentScore += m_pointsPerStep;
		updateScoreText();
	}

	m_elapsedTime += Time::deltaTime();

	if (Input::getKeyDown(SDL_SCANCODE_KP_PLUS))
	{
		setTopScore(getTopScore() + 1000000);
		setLivesCount(getLivesCount() + 1);
		setStageNumber(getStageNumber() + 1);
	}
	if (Input::getKeyDown(SDL_SCANCODE_KP_MINUS))
	{
		setTopScore(getTopScore() - 100000);
		setLivesCount(getLivesCount() - 1);
		setStageNumber(getStageNumber() - 1);
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


int UIManager::getLivesCount() const
{
	return m_currentLives;
}


void UIManager::setLivesCount(int livesCount)
{
	if (livesCount < 0)
	{
		OutputLog("WARNING: Attempting to set the UI lives count to a negative value (%i). The lives count will be set to zero.", livesCount);
		livesCount = 0;
	}
	m_currentLives = livesCount;
	updateLivesText();
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
	m_scoreText->setText(std::to_string(m_currentScore));
}


void UIManager::updateLivesText()
{
	std::string livesText = "";
	int livesToShow = m_currentLives % 100;
	
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
