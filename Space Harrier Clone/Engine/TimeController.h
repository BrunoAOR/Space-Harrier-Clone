#ifndef H_TIME_CONTROLLER
#define H_TIME_CONTROLLER

#include "SDL2/include/SDL_stdinc.h"


class TimeController final
{
public:
	TimeController();
	~TimeController();
	Uint32 time() const;
	Uint32 deltaTime() const;

	void updateTime();

private:
	Uint32 m_frameStartTime = 0;
	Uint32 m_deltaTime = 0;
};


#endif // !H_TIME_CONTROLLER
