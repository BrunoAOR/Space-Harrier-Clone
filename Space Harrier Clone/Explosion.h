#ifndef H_EXPLOSION
#define H_EXPLOSION

#include "Engine/Behaviour.h"
#include "Engine/Reference.h"
class SpriteSheet;
class FloorManager;
class FloorObjectMover;


class Explosion :
	public Behaviour
{
public:
	void init(const Reference<FloorManager>& floorManager, float startXPos, float normalizedStartProgress, float normalizedEndProgress, float startScale, float endScale, bool shouldLoopAnimation = false);

private:
	Reference<FloorObjectMover> m_floorObjectMover;
	Reference<SpriteSheet> m_spriteSheet;
};


#endif // !H_EXPLOSION
