#include "MotionPatternPoint.h"

#include <assert.h>


MotionPatternPoint::MotionPatternPoint()
{}


MotionPatternPoint::MotionPatternPoint(int timeMS, float x, float y, float normDepth)
	: time(timeMS), spritePosition(Vector2(x, y)), normalizedDepth(normDepth)
{
	assert(time >= 0 && normalizedDepth >= 0 && normalizedDepth <= 1);
}


MotionPatternPoint::MotionPatternPoint(int timeMS, float x, float y, float normDepth, int triggerID, bool shouldFire, std::string animationName, bool shouldAnimationLoop, float fps)
	: time(timeMS), spritePosition(Vector2(x, y)), normalizedDepth(normDepth), action{ triggerID, shouldFire, animationName, shouldAnimationLoop, fps }
{
	assert(time >= 0 && normalizedDepth >= 0 && normalizedDepth <= 1 && action.triggerId >= 0);
}