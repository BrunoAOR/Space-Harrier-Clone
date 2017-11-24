#ifndef H_COLLISION_INFO
#define H_COLLISION_INFO

#include "Reference.h"
class GameObject;
class Collider;


struct CollisionInfo
{
	Reference<GameObject> otherGameObject;
	Reference<Collider> otherCollider;
};


#endif // !H_COLLISION_INFO
