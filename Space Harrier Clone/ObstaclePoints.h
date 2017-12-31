#ifndef H_OBSTACLE_POINTS
#define H_OBSTACLE_POINTS

#include "Engine/Behaviour.h"
#include "Engine/Reference.h"
class Collider;


class ObstaclePoints :
	public Behaviour
{
public:
	virtual void onTriggerEnter(Reference<Collider>& other) override;

	bool bigPointsBonus;
};


#endif // !H_OBSTACLE_POINTS
