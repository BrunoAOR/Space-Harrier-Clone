#ifndef H_FLOOR_OBJECT_MOVER
#define H_FLOOR_OBJECT_MOVER

#include "Engine/Behaviour.h"
#include "Engine/Reference.h"
class FloorManager;
class PooledGameObject;
class Collider;
enum class FloorObjectType;


class FloorObjectMover :
	public Behaviour
{
public:
	void init(const Reference<FloorManager>& floorManager, float startXPos, float normalizedStartProgress, float normalizedEndProgress, float startScale, float endScale);
	FloorObjectType getType() const;
	void setType(FloorObjectType type);

	virtual void update() override;
	virtual void onTriggerEnter(Reference<Collider>& other) override;

	
private:
	void adjustScale(float normalizedCurrentProgress);
	void adjustPosition(float normalizedCurrentProgress);
	
	Reference<FloorManager> m_floorManager;
	Reference<PooledGameObject> m_poolHandler;
	Reference<Collider> m_collider;

	FloorObjectType m_floorObjectType;

	float m_startXPos = 0;
	float m_normalizedStartProgress = 0;
	float m_normalizedEndProgress = 0;
	float m_normalizedStartYPos = 0;
	float m_startScale = 0;
	float m_endScale = 0;

	int m_fullMotionDuration = 0;
	float m_elapsedTime = 0;
	float m_xPosSpeedOffset = 0;
};


#endif // !H_FLOOR_OBJECT_MOVER
