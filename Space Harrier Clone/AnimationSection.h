#ifndef H_ANIMATION_SECTION
#define H_ANIMATION_SECTION


struct AnimationSection
{
public:
	int spriteIndex;
	int durationMS;
	float startY;
	float endY;
	bool startAbsoluteY;
	bool endAbsoluteY;
};


#endif // !H_ANIMATION_SECTION
