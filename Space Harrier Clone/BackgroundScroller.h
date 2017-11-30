#ifndef H_BACKGROUND_SCROLLER
#define H_BACKGROUND_SCROLLER

#include <string>
#include "Engine/Behaviour.h"
#include "Engine/Reference.h"
#include "Engine/Vector2.h"
class FloorManager;
class GameObject;


class BackgroundScroller :
	public Behaviour
{
public:
	void init(const Reference<FloorManager>& floorManager, const std::string& texturePath, float speedModifier, int zIndex);
	virtual void update() override;

private:
	Reference<FloorManager> m_floorManager;
	int m_spriteWidth = 0;
	Reference<GameObject> m_bg1;
	Reference<GameObject> m_bg2;
	Vector2 m_position;

	float m_backgroundSpeedModifier = 0;
};


#endif // !H_BACKGROUND_SCROLLER
