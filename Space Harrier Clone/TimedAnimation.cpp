#include "TimedAnimation.h"

#include <assert.h>
#include "Engine/API.h"
#include "Engine/SpriteSheet.h"
#include "AnimationSection.h"


TimedAnimation::TimedAnimation(const std::vector<AnimationSection>& animationSections, const Reference<SpriteSheet>& spriteSheet)
{
	m_animationSections = animationSections;
	m_spriteSheet = spriteSheet;
	assert(m_animationSections.size() >= 2 && m_spriteSheet);
}


void TimedAnimation::start(float baseYPosition)
{
	m_baseY = baseYPosition;
	m_sectionElapsedTime = -1;
	m_animationSectionIndex = 0;
	m_isFinished = false;
}


void TimedAnimation::update(float& yMovablePosition)
{
	if (m_isFinished)
	{
		return;
	}

	AnimationSection currentAnimationSection = m_animationSections.at(m_animationSectionIndex);
	if (m_sectionElapsedTime == -1)
	{
		m_sectionElapsedTime = 0;
		assert(currentAnimationSection.spriteIndex >= 0 && currentAnimationSection.spriteIndex < m_spriteSheet->getCurrentAnimationFrameCount());
		m_spriteSheet->selectFrame(currentAnimationSection.spriteIndex);
	}
	else
	{
		m_sectionElapsedTime += Time::deltaTime();
	}
	
	float adjustedDuration = getSectionAdjustedDurationMS(currentAnimationSection, m_baseY);
	if (m_sectionElapsedTime >= adjustedDuration)
	{
		m_sectionElapsedTime -= adjustedDuration;
		++m_animationSectionIndex;
		
		if (m_animationSectionIndex > (int)m_animationSections.size() - 1)
		{
			m_isFinished = true;
			return;
		}
		assert(currentAnimationSection.spriteIndex >= 0 && currentAnimationSection.spriteIndex < m_spriteSheet->getCurrentAnimationFrameCount());
		currentAnimationSection = m_animationSections.at(m_animationSectionIndex);
		m_spriteSheet->selectFrame(currentAnimationSection.spriteIndex);
	}

	// Interpolate yPos
	float startY = currentAnimationSection.startY;
	if (!currentAnimationSection.startAbsoluteY)
	{
		startY += m_baseY;
	}
	float endY = currentAnimationSection.endY;
	if (!currentAnimationSection.endAbsoluteY)
	{
		endY += m_baseY;
	}
	float duration = getSectionAdjustedDurationMS(currentAnimationSection, m_baseY);
	float u = m_sectionElapsedTime / duration;
	u = u > 1 ? 1 : u;
	
	float yPos = startY * (1 - u) + endY * u;
	yMovablePosition = yPos;
}


bool TimedAnimation::isFinished() const
{
	return m_isFinished;
}

float TimedAnimation::getSectionAdjustedDurationMS(const AnimationSection & animationSection, float baseY)
{
	float startY = animationSection.startY;
	if (!animationSection.startAbsoluteY)
	{
		startY += m_baseY;
	}
	float endY = animationSection.endY;
	if (!animationSection.endAbsoluteY)
	{
		endY += m_baseY;
	}
	float duration = (float)animationSection.durationMS;
	if (animationSection.startAbsoluteY && !animationSection.endAbsoluteY || !animationSection.startAbsoluteY && animationSection.endAbsoluteY)
	{
		float yOriginalDifference = animationSection.endY - animationSection.startY;
		float yNewDifference = endY - startY;
		duration *= yNewDifference / yOriginalDifference;
	}
	return duration;
}
