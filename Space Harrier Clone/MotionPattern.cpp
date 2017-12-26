#include "MotionPattern.h"

#include <algorithm>
#include <assert.h>


MotionPattern::MotionPattern()
{
}


MotionPattern::MotionPattern(const std::vector<MotionPatternPoint>& motionPoints)
{
	m_motionPoints = motionPoints;
	assert(m_motionPoints.size() > 0);
	std::sort(m_motionPoints.begin(), m_motionPoints.end(), [](MotionPatternPoint mpp1, MotionPatternPoint mpp2) -> bool { return mpp1.normalizedTime < mpp2.normalizedTime; });
	bool valid = true;
	bool sameTime;
	bool sameId;
	for (unsigned int i = 1; i < m_motionPoints.size(); ++i)
	{
		sameTime = m_motionPoints[i - 1].normalizedTime == m_motionPoints[i].normalizedTime;
		sameId = m_motionPoints[i - 1].action.triggerId != -1 && m_motionPoints[i - 1].action.triggerId == m_motionPoints[i].action.triggerId;
		if (sameTime || sameId)
		{
			valid = false;
			break;
		}
	}
	assert(valid);
}

MotionPatternPoint MotionPattern::getMotionPatternPoint(float normalizedTime)
{
	MotionPatternPoint startMpp;
	MotionPatternPoint endMpp;
	bool hasStart = false;
	bool hasEnd = false;

	for (MotionPatternPoint& someMpp : m_motionPoints)
	{
		if (normalizedTime > someMpp.normalizedTime)
		{
			startMpp = someMpp;
			hasStart = true;
		}
		if (normalizedTime <= someMpp.normalizedTime)
		{
			endMpp = someMpp;
			hasEnd = true;
			break;
		}
	}

	// There are 3 possible cases:
	// Note: The case where both a start and an end haven't been found is non-existent, because m_motionPoints is guaranteed to have at least 1 element.
	
	// Case 1. Only a start was found (the last/ mpp)
	if (!hasEnd)
	{
		return startMpp;
	}

	// Case 2. Only an end was found (the firs mpp)
	if (!hasStart)
	{
		return endMpp;
	}

	// Case 3. A start and an end was found, so we have to interpolate between the two
	MotionPatternPoint resultMpp;
	// The action information of the startMpp is kept
	resultMpp.action = startMpp.action;
	resultMpp.normalizedTime = normalizedTime;
	// u is the progress within the startMpp and endMpp normalizedTime
	float u = (normalizedTime - startMpp.normalizedTime) / (endMpp.normalizedTime - startMpp.normalizedTime);
	resultMpp.normalizedDepth = (1 - u) * startMpp.normalizedDepth + u * endMpp.normalizedDepth;
	resultMpp.spritePosition.x = (1 - u) * startMpp.spritePosition.x + u * endMpp.spritePosition.x;
	resultMpp.spritePosition.y = (1 - u) * startMpp.spritePosition.y + u * endMpp.spritePosition.y;
	return resultMpp;
}

bool MotionPattern::isValid() const
{
	return m_motionPoints.size() > 0;
}
