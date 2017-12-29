#ifndef H_MOTION_PATTERN_POINT
#define H_MOTION_PATTERN_POINT

#include <string>
#include "Engine/Vector2.h"


struct MotionPatternPoint
{
public:
	MotionPatternPoint();
	MotionPatternPoint(float normTimeMS, float x, float y, float normDepth);
	MotionPatternPoint(float normTimeMS, float x, float y, float normDepth, int triggerID, bool shouldFire, std::string animationName = "", bool shouldAnimationLoop = false, int fps = 5);

	float normalizedTime;
	Vector2 spritePosition;
	float normalizedDepth;
	struct {
		int triggerId = -1;
		bool fire = false;
		std::string animationName = "";
		bool animationLoop = false;
		int animationFps = 5;
	} action;
};


#endif // !H_MOTION_PATTERN_POINT
