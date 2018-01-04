#include "SceneFader.h"

#include "Engine/GameObject.h"
#include "Engine/gameConfig.h"
#include "Engine/API.h"
#include "EngineExt/RectangleRenderer.h"
#include "Messenger.h"
#include "MessengerEventType.h"


void SceneFader::onDestroy()
{
	Messenger::removeListener(this, MessengerEventType::CHANGE_SCENE);
}

void SceneFader::init(int targetSceneIndex, SDL_Color targetColor, int fadeTimeMS, int fadeInDelayMS, int fadeOutDelayMS, bool shouldFadeIn)
{
	m_rectRenderer = gameObject()->getComponent<RectangleRenderer>();
	assert(m_rectRenderer);
	m_rectRenderer->setRenderLayer("UI");
	m_rectRenderer->setZIndex(100);
	m_rectRenderer->setAllPivots(Vector2(0, 0));

	m_fadeInDelayMS = fadeInDelayMS >= 0 ? fadeInDelayMS : 0;
	m_fadeOutDelayMS = fadeOutDelayMS >= 0 ? fadeOutDelayMS : 0;
	m_rectRenderer->rect = SDL_Rect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	m_targetSceneIndex = targetSceneIndex;
	m_fadeElapsedTime = 0;
	m_fadeTimeMS = fadeTimeMS >= 0 ? fadeTimeMS : 0;
	m_defaultAlpha = targetColor.a;
	m_rectRenderer->color = targetColor;
	m_rectRenderer->color.a = 0;
	m_isFadingIn = false;
	m_isFadingOut = false;

	if (shouldFadeIn)
	{
		m_rectRenderer->color.a = m_defaultAlpha;
		m_isFadingIn = true;
	}
}

void SceneFader::awake()
{
	Messenger::addListener(this, MessengerEventType::CHANGE_SCENE);
	assert(m_rectRenderer);
}


void SceneFader::update()
{
	if (!m_isFadingOut && !m_isFadingIn)
	{
		return;
	}

	int fadeDelay = m_isFadingIn ? m_fadeInDelayMS : m_fadeOutDelayMS;
	float u = m_fadeTimeMS > 0 ? (float) (m_fadeElapsedTime - fadeDelay) / m_fadeTimeMS : 1;
	// u will be <0 while waiting for the fade delay
	if (u > 0)
	{
		u = u > 1 ? 1 : u;

		int currentAlpha;
		if (m_isFadingIn)
		{
			currentAlpha = (int)((1 - u) * m_defaultAlpha);
		}
		else
		{
			currentAlpha = (int)(u * m_defaultAlpha);

		}
		m_rectRenderer->color.a = currentAlpha;

		if (u == 1)
		{
			if (m_isFadingOut)
			{
				m_isFadingOut = false;
				Scenes::loadScene(m_targetSceneIndex);
			}
			else
			{
				m_isFadingIn = false;
			}
		}
	}
	m_fadeElapsedTime += Time::deltaTime();
}



void SceneFader::eventsCallback(MessengerEventType eventType)
{
	if (eventType == MessengerEventType::CHANGE_SCENE)
	{
		fadeOutToScene();
	}
}


void SceneFader::fadeOutToScene()
{
	if (!m_isFadingOut && !m_isFadingIn)
	{
		m_rectRenderer->color.a = 0;
		m_isFadingOut = true;
		m_fadeElapsedTime = 0;
	}
}
