#include "RectangleCollider.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include "GameObject.h"
#include "Transform.h"
#include "ColliderType.h"


RectangleCollider::RectangleCollider() : size(0, 0)
{
	m_colliderType = ColliderType::RECTANGLE;
}


RectangleCollider::~RectangleCollider()
{
}


std::vector<Vector2> RectangleCollider::getWorldCorners()
{
	// Check if the previously cached values are still valid
	// Note that checkCacheValidity will update the internal m_previousPosition and m_previousRotation if required
	// and will clear the m_worldCorners and m_outerNormals std::vectors
	checkCacheValidity();

	// If m_worldCorners is not empty, then the cache was still valid and we can returned the cache std::vector
	if (!m_worldCorners.empty())
	{
		return m_worldCorners;
	}

	// If it was empty, we recalculate the m_worldCorners

	// Now we create a std::vector to hold the unrotated centerToCorner vectors
	std::vector<Vector2> centerToCornerVectors =
	{
		Vector2(-size.x / 2, -size.y / 2),
		Vector2(-size.x / 2, +size.y / 2),
		Vector2(+size.x / 2, +size.y / 2),
		Vector2(+size.x / 2, -size.y / 2)
	};

	// Next, we iterate throught these centerToCorner vectors
	for (Vector2 centerToCornerVector : centerToCornerVectors)
	{
		// First, rotate it
		centerToCornerVector.rotateCCWDegrees(m_cachedRotation);
		// Next calculate the cornerVector and add to the cache std::vector
		m_worldCorners.push_back(m_cachedWorldPosition + centerToCornerVector);
	}

	return m_worldCorners;
}


std::vector<Vector2> RectangleCollider::getOuterNormals()
{
	// Check if the previously cached values are still valid
	// Note that checkCacheValidity will update the internal m_previousPosition and m_previousRotation if required
	// and will clear the m_worldCorners and m_outerNormals std::vectors
	checkCacheValidity();

	// If m_outerNormals is not empty, then the cache was still valid and we can returned the cache std::vector
	if (!m_outerNormals.empty())
	{
		return m_outerNormals;
	}

	// If it was empty, we recalculate the m_outerNormals

	// First, we get the worldCorners
	std::vector<Vector2> worldCorners = getWorldCorners();

	// Since our worldCorners are enumerated in a CW fashion, the outer corners are the left normals
	// So they can be obtained by rotating the vector from one corner to the next 90 degress in a CCW fashion

	// So, we iterate through the corners
	for (unsigned int i = 0; i < worldCorners.size(); ++i)
	{
		unsigned int iNext = (i + 1) % worldCorners.size();
		Vector2 cornerToCornerVector = worldCorners[iNext] - worldCorners[i];
		// The following theorem is applied (for CCW rotation):
		// x2 = x1 * cosf(theta) - y1 * sinf(theta)
		// y2 = x1 * sinf(theta) + y1 * cosf(theta)
		// But, since cosf(90) = 0 and sinf(90) = 1, it can be simplified as
		// x2 = -y1 and y2 = x1
		m_outerNormals.push_back(Vector2(-cornerToCornerVector.y, cornerToCornerVector.x));
	}

	return m_outerNormals;
}


void RectangleCollider::checkCacheValidity()
{
	auto transform = gameObject()->transform;
	Vector2 newPosition = transform->getWorldPosition();
	float newRotation = transform->getWorldRotation();
	if (m_cachedWorldPosition != newPosition || m_cachedRotation != newRotation)
	{
		m_cachedWorldPosition = newPosition;
		m_cachedRotation = newRotation;
		m_worldCorners.clear();
		m_outerNormals.clear();
	}
}
