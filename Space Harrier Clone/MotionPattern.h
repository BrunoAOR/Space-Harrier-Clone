#ifndef H_MOTION_PATTERN
#define H_MOTION_PATTERN

#include <vector>
#include "MotionPatternPoint.h"


class MotionPattern
{
public:
	MotionPattern();
	MotionPattern(const std::vector<MotionPatternPoint>& motionPoints);
	MotionPatternPoint getMotionPatternPoint(float normalizedTime);
	bool isValid() const;

private:
	std::vector<MotionPatternPoint> m_motionPoints;
};


#endif // !H_MOTION_PATTERN
