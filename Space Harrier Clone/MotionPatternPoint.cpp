#include "MotionPatternPoint.h"

#include <assert.h>


MotionPatternPoint::MotionPatternPoint()
{}


MotionPatternPoint::MotionPatternPoint(float normTimeMS, float x, float y, float normDepth)
	: normalizedTime(normTimeMS), spritePosition(Vector2(x, y)), normalizedDepth(normDepth)
{
	assert(normalizedTime >= 0 && normalizedTime <= 1 && normalizedDepth >= 0 && normalizedDepth <= 1);
}


MotionPatternPoint::MotionPatternPoint(float normTimeMS, float x, float y, float normDepth, int triggerID, bool shouldFire, std::string animationName, bool shouldAnimationLoop, int fps)
	: normalizedTime(normTimeMS), spritePosition(Vector2(x, y)), normalizedDepth(normDepth), action{ triggerID, shouldFire, animationName, shouldAnimationLoop, fps }
{
	assert(normalizedTime >= 0 && normalizedTime <= 1 && normalizedDepth >= 0 && normalizedDepth <= 1 && action.triggerId >= 0);
}