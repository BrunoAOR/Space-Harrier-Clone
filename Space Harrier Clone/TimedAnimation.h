#ifndef H_TIMED_ANIMATION
#define H_TIMED_ANIMATION

#include <vector>
#include "Engine/Reference.h"
#include "AnimationSection.h"
class SpriteSheet;
class Vector2;


class TimedAnimation
{
public:
	TimedAnimation(const std::vector<AnimationSection>& animationSections, const Reference<SpriteSheet>& spriteSheet);
	
	void start(float baseYPosition);
	void update(float& yMovablePosition);
	bool isFinished() const;

private:
	float getSectionAdjustedDurationMS(const AnimationSection& animationSection, float baseY);

	std::vector<AnimationSection> m_animationSections;
	Reference<SpriteSheet> m_spriteSheet;
	float m_baseY;
	float m_sectionElapsedTime = -1;
	int m_animationSectionIndex = -1;
	bool m_isFinished = true;
};


#endif // !H_TIMED_ANIMATION
