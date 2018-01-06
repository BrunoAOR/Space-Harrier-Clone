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
	std::sort(m_motionPoints.begin(), m_motionPoints.end(), [](MotionPatternPoint mpp1, MotionPatternPoint mpp2) -> bool { return mpp1.time < mpp2.time; });
	bool valid = true;
	bool sameTime;
	bool sameId;
	for (unsigned int i = 1; i < m_motionPoints.size(); ++i)
	{
		sameTime = m_motionPoints[i - 1].time == m_motionPoints[i].time;
		sameId = m_motionPoints[i - 1].action.triggerId != -1 && m_motionPoints[i - 1].action.triggerId == m_motionPoints[i].action.triggerId;
		if (sameTime || sameId)
		{
			valid = false;
			break;
		}
	}
	assert(valid);
}

MotionPatternPoint MotionPattern::getMotionPatternPoint(int time)
{
	MotionPatternPoint startMpp;
	MotionPatternPoint endMpp;
	bool hasStart = false;
	bool hasEnd = false;

	for (MotionPatternPoint& someMpp : m_motionPoints)
	{
		if (time > someMpp.time)
		{
			startMpp = someMpp;
			hasStart = true;
		}
		if (time <= someMpp.time)
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
	resultMpp.time = time;
	// u is the progress within the startMpp and endMpp normalizedTime
	float u = (float)(time - startMpp.time) / (endMpp.time - startMpp.time);
	resultMpp.normalizedDepth = (1 - u) * startMpp.normalizedDepth + u * endMpp.normalizedDepth;
	resultMpp.spritePosition.x = (1 - u) * startMpp.spritePosition.x + u * endMpp.spritePosition.x;
	resultMpp.spritePosition.y = (1 - u) * startMpp.spritePosition.y + u * endMpp.spritePosition.y;
	return resultMpp;
}

int MotionPattern::getLifeTimeMS()
{
	return m_motionPoints[m_motionPoints.size() - 1].time;
}

bool MotionPattern::isValid() const
{
	return m_motionPoints.size() > 0;
}
