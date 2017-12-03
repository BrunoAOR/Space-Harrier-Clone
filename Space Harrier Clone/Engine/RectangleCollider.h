#ifndef H_RECTANGLE_COLLIDER
#define H_RECTANGLE_COLLIDER

#include <vector>
#include "Collider.h"
#include "Vector2.h"


class RectangleCollider :
	public Collider
{
public:
	RectangleCollider();
	~RectangleCollider();

	Vector2 getLocalScaledSize() const;
	Vector2 getWorldScaledSize() const;

	std::vector<Vector2> getWorldCorners();
	std::vector<Vector2> getOuterNormals();

	Vector2 size;

private:
	void checkCacheValidity();

	Vector2 m_cachedWorldPosition;
	float m_cachedWorldRotation;
	Vector2 m_cachedWorldScale;
	std::vector<Vector2> m_worldCorners;
	std::vector<Vector2> m_outerNormals;
};


#endif // !H_RECTANGLE_COLLIDER
