#include "TimeController.h"

#include "Time.h"
#include "SDL2/include/SDL_timer.h"


TimeController::TimeController()
{
}


TimeController::~TimeController()
{
}


Uint32 TimeController::time() const
{
	return m_frameStartTime;
}


Uint32 TimeController::deltaTime() const
{
	return m_deltaTime;
}


void TimeController::updateTime()
{
	unsigned int currentTicks = SDL_GetTicks();
	m_deltaTime = currentTicks - m_frameStartTime;
	m_frameStartTime = currentTicks;
}
