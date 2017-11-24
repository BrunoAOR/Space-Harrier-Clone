#ifndef H_CIRCLE_COLLIDER
#define H_CIRCLE_COLLIDER

#include "Collider.h"


class CircleCollider :
	public Collider
{
public:
	CircleCollider();
	~CircleCollider();

	float radius;
};


#endif // !H_CIRCLE_COLLIDER
