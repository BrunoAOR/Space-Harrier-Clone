#include "TimeLogger.h"

#include "Engine/API.h"
#include "Engine/globals.h"

void TimeLogger::start()
{
	m_logInterval = 500;
	m_elapsedInterval = 0;
}

void TimeLogger::update()
{
	int elapsedTime = Time::deltaTime();
	m_elapsedInterval += elapsedTime;
	if (elapsedTime == 0)
	{
		elapsedTime = 1;
	}

	float fps = 1000.0f / elapsedTime;
	m_latestFPS.push_back(fps);
	if (m_latestFPS.size() > 25)
	{
		m_latestFPS.pop_front();
	}

	if (m_elapsedInterval > m_logInterval)
	{
		m_elapsedInterval -= m_logInterval;

		float averageFPS = 0;
		for (float fps : m_latestFPS)
		{
			averageFPS += fps;
		}
		averageFPS /= m_latestFPS.size();
		OutputLog("FPS: %i", (int)averageFPS);
	}
}
