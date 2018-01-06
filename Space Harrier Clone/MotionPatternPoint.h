#ifndef H_MOTION_PATTERN_POINT
#define H_MOTION_PATTERN_POINT

#include <string>
#include "Engine/Vector2.h"


struct MotionPatternPoint
{
public:
	MotionPatternPoint();
	MotionPatternPoint(int timeMS, float x, float y, float normDepth);
	MotionPatternPoint(int timeMS, float x, float y, float normDepth, int triggerID, bool shouldFire, std::string animationName = "", bool shouldAnimationLoop = false, float fps = 6);

	int time;
	Vector2 spritePosition;
	float normalizedDepth;
	struct {
		int triggerId = -1;
		bool fire = false;
		std::string animationName = "";
		bool animationLoop = false;
		float animationFps = 6;
	} action;
};


#endif // !H_MOTION_PATTERN_POINT
