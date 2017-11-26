#ifndef H_TIME_LOGGER
#define H_TIME_LOGGER

#include "Engine/Behaviour.h"
#include <deque>


class TimeLogger :
	public Behaviour
{
public:
	// Inherited via Behaviour
	virtual void start() override;
	virtual void update() override;

private:
	std::deque<float> m_latestFPS;
	int m_logInterval;
	int m_elapsedInterval;
};


#endif // !H_TIME_LOGGER
