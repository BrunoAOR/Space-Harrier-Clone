#include "CollidersManager.h"

#include <cmath>
#include "gameConfig.h"
#include "ComponentType.h"
#include "EngineUtils.h"
#include "Vector2.h"
#include "GameObject.h"
#include "Transform.h"
#include "CollisionInfo.h"
#include "ColliderType.h"
#include "CircleCollider.h"
#include "RectangleCollider.h"


CollidersManager::CollidersManager()
{
}


CollidersManager::~CollidersManager()
{
}


ComponentType CollidersManager::managedComponentType() const
{
	return ComponentType::COLLIDER;
}


void CollidersManager::update()
{
	// Note: refreshComponents ensures that all Reference in m_components are valid, so they can be safely used
	refreshComponents();
	// Ensure we have at least 2 components to handle (needed to avoid the for-loops to attempt to access out of range)
	if (m_components.size() < 2)
	{
		return;
	}
	for (unsigned int i = 0; i < m_components.size() - 1; ++i)
	{
		Reference<Component>& componentRef1 = m_components[i];
		Collider* collider1 = static_cast<Collider*>(componentRef1.get());
		if (collider1->isActive())
		{
			for (unsigned int j = i + 1; j < m_components.size(); ++j)
			{
				Reference<Component>& componentRef2 = m_components[j];
				Collider* collider2 = static_cast<Collider*>(componentRef2.get());

				if (collider2->isActive() && collider1 != collider2 && shouldCalculateCollision(collider1, collider2))
				{
					// Actual collider on collider check
					bool shouldResolve = shouldResolveCollision(collider1, collider2);
					if (checkAndResolveCollision(collider1, collider2, shouldResolve))
					{
						informCollision(componentRef1.static_reference_cast<Collider>(), componentRef2.static_reference_cast<Collider>());
					}
				}
			}
		}
	}

	// Refresh the triggerCollisionCache to call any onTriggerExit methods required
	m_triggerCollisionCache.refresh();
}


bool CollidersManager::init()
{
	// Success flag
	bool success = true;

	m_collisionSystemSetup = collisionSystemSetup();
	if (m_collisionSystemSetup.zIndexCollisionRange < 0)
	{
		m_collisionSystemSetup.zIndexCollisionRange = 0;
		OutputLog("WARNING: The zIndexCollisionRange was set to a negative number. The value has been set to zero!");
	}

	int layersCount = m_collisionSystemSetup.layersNames.size();
	// Add the "default" layer to the list
	m_collisionSystemSetup.layersNames.push_back("default");

	if (m_collisionSystemSetup.collisionMatrix.size() != layersCount)
	{
		OutputLog("ERROR: The amount of lines collision matr ix is not the same as the amount of names defined in the layersNames vector!");
		success = false;
	}

	for (unsigned int i = 0; i < m_collisionSystemSetup.collisionMatrix.size(); ++i)
	{
		std::vector<bool>& matrixLine = m_collisionSystemSetup.collisionMatrix.at(i);
		if (matrixLine.size() != layersCount)
		{
			OutputLog("ERROR: The amount of bool values in the collision matrix for line %i is not the same as the amount of names defined in the layersNames vector!", i);
			success = false;
		}

		// Add one "true" value at the end for the collision with the default layer
		matrixLine.push_back(true);

		// Populate the namesToIndexMap
		std::string layerName = m_collisionSystemSetup.layersNames[i];
		m_collisionSystemSetup.namesToIndexMap[layerName] = i;
	}

	// Add one extra matrixLine for the default layer (all values set to true). The amount of values is layersCount + 1, because layersCount didn't include the "default" layer
	m_collisionSystemSetup.collisionMatrix.push_back(std::vector<bool>(layersCount + 1, true));
	m_collisionSystemSetup.namesToIndexMap["default"] = layersCount;

	return success;
}


void CollidersManager::close()
{
}


bool CollidersManager::initializeComponent(Reference<Component>& component)
{
	Collider* collider = static_cast<Collider*>(component.get());
	collider->m_collidersManager = this;
	return true;
}


bool CollidersManager::shouldCalculateCollision(const Collider* coll1, const Collider* coll2) const
{
	int coll1Index = getCollisionLayerIndex(coll1->m_collisionLayer);
	int coll2Index = getCollisionLayerIndex(coll2->m_collisionLayer);
	int zIndexDifference = abs(coll1->zIndex - coll2->zIndex);

	// Both indexes should be different from -1 since any layerName change is verified before being executed so there's no need for checks
	if (m_collisionSystemSetup.collisionMatrix[coll1Index][coll2Index])
	{
		// Same layer
		if (coll1Index == coll2Index)
		{
			if (m_collisionSystemSetup.useZIndexWithinLayer)
			{
				if (zIndexDifference <= m_collisionSystemSetup.zIndexCollisionRange)
				{
					return true;
				}
			}
			else
			{
				return true;
			}
		}
		// Different layers
		else
		{
			if (m_collisionSystemSetup.useZIndexAmongLayers)
			{
				if (zIndexDifference <= m_collisionSystemSetup.zIndexCollisionRange)
				{
					return true;
				}
			}
			else
			{
				return true;
			}
		}
	}

	return false;
}


bool CollidersManager::shouldResolveCollision(const Collider* coll1, const Collider* coll2) const
{
	return !(coll1->isTrigger || coll2->isTrigger);
}


bool CollidersManager::checkAndResolveCollision(Collider* coll1, Collider* coll2, bool shouldResolve) const
{
	if (coll1->isStatic && coll2->isStatic)
	{
		return false;
	}

	bool collisionOccured = false;
	
	if (coll1->m_colliderType == ColliderType::CIRCLE)
	{
		auto castedColl1 = static_cast<CircleCollider*>(coll1);

		if (coll2->m_colliderType == ColliderType::CIRCLE)
		{
			auto castedColl2 = static_cast<CircleCollider*>(coll2);
			collisionOccured = checkAndResolveCollision(castedColl1, castedColl2, shouldResolve);
		}
		else if (coll2->m_colliderType == ColliderType::RECTANGLE)
		{
			auto castedColl2 = static_cast<RectangleCollider*>(coll2);
			collisionOccured = checkAndResolveCollision(castedColl1, castedColl2, shouldResolve);
		}
	}
	else if (coll1->m_colliderType == ColliderType::RECTANGLE)
	{
		auto castedColl1 = static_cast<RectangleCollider*>(coll1);

		if (coll2->m_colliderType == ColliderType::CIRCLE)
		{
			auto castedColl2 = static_cast<CircleCollider*>(coll2);
			collisionOccured = checkAndResolveCollision(castedColl1, castedColl2, shouldResolve);
		}
		else if (coll2->m_colliderType == ColliderType::RECTANGLE)
		{
			auto castedColl2 = static_cast<RectangleCollider*>(coll2);
			collisionOccured = checkAndResolveCollision(castedColl1, castedColl2, shouldResolve);
		}
	}
	return collisionOccured;
}


bool CollidersManager::checkAndResolveCollision(CircleCollider* circColl1, CircleCollider* circColl2, bool shouldResolve) const
{
	Vector2 pos1 = circColl1->getWorldPosition();

	Vector2 pos2 = circColl2->getWorldPosition();

	float penetrationDistance = circColl1->getWorldScaledRadius() + circColl2->getWorldScaledRadius() - Vector2::distance(pos1, pos2);

	if (penetrationDistance > m_minPenetration)
	{
		if (shouldResolve)
		{
			resolveCollision(circColl1, pos1, circColl2, pos2, penetrationDistance);
		}
		return true;
	}

	return false;
}


bool CollidersManager::checkAndResolveCollision(RectangleCollider* rectColl1, RectangleCollider* rectColl2, bool shouldResolve) const
{
	// First, we get the normals from the rectColls.
	// Only the first 2 normals are needed for each rect, since the other two are the same but in opposite direction
	// Special case: if the rotation of both rectangle is the same, then only the first 2 normals of either rectColl are required
	std::vector<Vector2> selectedNormals;
	if (rectColl1->getWorldRotation() == rectColl2->getWorldRotation())
	{
		auto r1Normals = rectColl1->getOuterNormals();
		selectedNormals = { r1Normals[0], r1Normals[1]};
	}
	else
	{
		auto r1Normals = rectColl1->getOuterNormals();
		auto r2Normals = rectColl2->getOuterNormals();
		selectedNormals = { r1Normals[0], r1Normals[1], r2Normals[0], r2Normals[1] };
	}

	// Now we need iterate through the selectedNormals projecting the rects' corners onto the normal and recording the smallest overlap found
	// 1. Get the corners for both rects
	auto r1Corners = rectColl1->getWorldCorners();
	auto r2Corners = rectColl2->getWorldCorners();

	// 2. Create variables to store the smallest overlap vector and direction (stored separate to easily compare the length)
	float minOverlapLength = std::numeric_limits<float>::max();
	Vector2 minOverlapDirection;

	// 3. Now we iterate
	for (unsigned int i = 0; i < selectedNormals.size(); ++i)
	{
		// 1. Get the Normal unit vector
		Vector2 normalUnitVector = selectedNormals[i].normalized();

		// 2. Find the min and max corner projections for r1 and r2
		// For r1
		float r1Min = std::numeric_limits<float>::max();
		float r1Max = std::numeric_limits<float>::lowest();
		// For r2
		float r2Min = std::numeric_limits<float>::max();
		float r2Max = std::numeric_limits<float>::lowest();

		for (int c = 0; c < 4; ++c)
		{
			// r1
			float currentR1Projection = Vector2::dot(r1Corners[c], normalUnitVector);
			
			if (currentR1Projection < r1Min)
			{
				r1Min = currentR1Projection;
			}
			if (currentR1Projection > r1Max)
			{
				r1Max = currentR1Projection;
			}

			// r2
			float currentR2Projection = Vector2::dot(r2Corners[c], normalUnitVector);

			if (currentR2Projection < r2Min)
			{
				r2Min = currentR2Projection;
			}
			if (currentR2Projection > r2Max)
			{
				r2Max = currentR2Projection;
			}
		}

		// 3. Determine if there is an overlap. If there isn't, early exit and return false
		float penetrationDistance = -EngineUtils::getRangesSeparationDistance(r1Min, r1Max, r2Min, r2Max);
		if (penetrationDistance <= m_minPenetration)
		{
			// So, no overlap in this axis
			return false;
		}
		// So, there is overlap in this axis. Compare with cached minOverlap (turn projectionSeparation into a possitive value
		else if (penetrationDistance < minOverlapLength)
		{
			minOverlapLength = penetrationDistance;
			minOverlapDirection = normalUnitVector;
		}
		// And now we continue with the next test axis (next normal)
	}

	// If we got here, we have a minOverlapLength and Direction that can be used to resolve the collision
	if (shouldResolve)
	{
		resolveCollision(rectColl1, rectColl2, minOverlapLength * minOverlapDirection);
	}
	return true;
}


bool CollidersManager::checkAndResolveCollision(CircleCollider* circColl, RectangleCollider* rectColl, bool shouldResolve) const
{
	// To solve this collision with rotated rectangles, we'll temporarily place the circle as a child of the rectangle.
	// In this way, the rectColl will be axis aligned in the reference system for the circle
	// So locally, the rectangle would be possitioned at its offset and the circle would be positioned at its localPoisiton + offset

	// Store the circ's previous parent and then change to the rect
	Transform* circTransform = circColl->gameObject()->transform.get();
	auto originalCircParent = circTransform->getParent();
	circTransform->setParent(rectColl->gameObject()->transform);

	// circColl (Note that getLocalPosition takes into consideration the circle collider's offset
	Vector2 localCircPos = circColl->getLocalPosition();

	// rectColl: Get the unscaledoffset because the calculations are being performed in the rectGO coordinate space
	Vector2 localRectPos = rectColl->offset;

	Vector2 closestPointFromPointToRect = EngineUtils::closestPointOnOrientedRectFromPoint(localRectPos, rectColl->size, localCircPos);

	float penetrationDistance = 0;
	Vector2 penetrationVector;
	// Use the unscaled rectGO size  and the localScaled circColl radius because the calculations are being performed in the rectGO coordinate space
	if (EngineUtils::isPointInRect(localRectPos, rectColl->size, localCircPos))
	{
		penetrationVector = closestPointFromPointToRect - localCircPos;
		penetrationDistance = circColl->getLocalScaledRadius() + penetrationVector.getLength();
	}
	else
	{
		penetrationVector = localCircPos - closestPointFromPointToRect;
		penetrationDistance = circColl->getLocalScaledRadius() - penetrationVector.getLength();
	}
	penetrationVector.normalize();
	penetrationVector *= penetrationDistance;
	
	// Now that all calculations are finished, readjust the penetrationVector for world space (rotation)
	float worldRotOfRectSystem = circTransform->localToWorldRotation(0);
	penetrationVector.rotateCCWDegrees(worldRotOfRectSystem);
	// and return the circ's parent to its original parent
	circTransform->setParent(originalCircParent);

	if (penetrationDistance > m_minPenetration)
	{
		if (shouldResolve)
		{
			resolveCollision(circColl, rectColl, penetrationVector);
		}
		return true;
	}

	return false;
}


bool CollidersManager::checkAndResolveCollision(RectangleCollider* rectColl, CircleCollider* circColl, bool shouldResolve) const
{
	return checkAndResolveCollision(circColl, rectColl, shouldResolve);
}


void CollidersManager::resolveCollision(CircleCollider* circColl1, const Vector2& pos1, CircleCollider* circColl2, const Vector2& pos2, float penetrationDistance) const
{
	// First, get the vector to move circColl1 away from circColl2
	Vector2 moveVector = (pos1 - pos2).normalized() * penetrationDistance;

	// Fix for complete overlap (just push along y axis)
	if (moveVector.x == 0 && moveVector.y == 0) {
		moveVector.y = penetrationDistance;
	}

	// Now, define which rectColl has to move (see isStatic) and move it
	if (!circColl1->isStatic && circColl2->isStatic)
	{
		// Only circColl1's gameObject is pushed
		Vector2 targetPos = pos1 + moveVector - circColl1->offset;
		circColl1->gameObject()->transform->setWorldPosition(targetPos);
	}
	else if (circColl1->isStatic && !circColl2->isStatic)
	{
		// Only circColl2's gameObject is pushed
		moveVector = -moveVector;	// Invert the vector to clear rectColl2 away from rectColl1
		Vector2 targetPos = pos2 + moveVector - circColl2->offset;
		circColl2->gameObject()->transform->setWorldPosition(targetPos);
	}
	else {	// So neither circColl1, nor circColl2 are static (both can't be static because this function would have never been called
		// Both  circColl1's gameObject and circColl1's gameObject are pushed
		
		// Move circColl1 away
		Vector2 targetPos1 = pos1 + moveVector / 2 - circColl1->offset;
		circColl1->gameObject()->transform->setWorldPosition(targetPos1);
		// Move circColl2 away
		Vector2 targetPos2 = pos2 + -moveVector / 2 - circColl2->offset;
		circColl2->gameObject()->transform->setWorldPosition(targetPos2);
	}
}


void CollidersManager::resolveCollision(RectangleCollider* rectColl1, RectangleCollider* rectColl2, Vector2& penetrationVector) const
{
	Vector2 pos1 = rectColl1->getWorldPosition();
	Vector2 pos2 = rectColl2->getWorldPosition();

	// Ensure penetrationVector is aligned so that r1 is pulled away from r2
	if (Vector2::dot(pos1 - pos2, penetrationVector) < 0)
	{
		// So they point in 'opposite' direction (angle between them is over 90 degrees)
		penetrationVector *= -1;
	}

	// Now, define which rectColl has to move (see isStatic) and move only in the shortest direction
	if (!rectColl1->isStatic && rectColl2->isStatic)
	{
		// Only rectColl1's gameObject is pushed
		Vector2 targetPos = pos1 + penetrationVector - rectColl1->offset;
		rectColl1->gameObject()->transform->setWorldPosition(targetPos);
	}
	else if (rectColl1->isStatic && !rectColl2->isStatic)
	{
		// Only rectColl2's gameObject is pushed
		// Invert the vector to clear rectColl2 away from rectColl1
		Vector2 targetPos = pos2 + -penetrationVector - rectColl2->offset;
		rectColl2->gameObject()->transform->setWorldPosition(targetPos);
	}
	else {	// So neither rectColl1, nor rectColl2 are static (both can't be static because this function would have never been called
		// Both  rectColl1's gameObject and rectColl1's gameObject are pushed

		// Move rectColl1 away
		Vector2 targetPos1 = pos1 + penetrationVector / 2 - rectColl1->offset;
		rectColl1->gameObject()->transform->setWorldPosition(targetPos1);
		// Move rectColl2 away
		Vector2 targetPos2 = pos2 + -penetrationVector / 2 - rectColl2->offset;
		rectColl2->gameObject()->transform->setWorldPosition(targetPos2);
	}

}


void CollidersManager::resolveCollision(CircleCollider* circColl, RectangleCollider* rectColl, const Vector2& penetrationVector) const
{
	Vector2 circPos = circColl->getWorldPosition();
	Vector2 rectPos = rectColl->getWorldPosition();

	// Define which collider has to move (see isStatic) and move using the penetrationVector
	if (!circColl->isStatic && rectColl->isStatic)
	{
		// Only circColl's gameObject is pushed
		Vector2 targetPos = circPos + penetrationVector - circColl->offset;
		circColl->gameObject()->transform->setWorldPosition(targetPos);
	}
	else if (circColl->isStatic && !rectColl->isStatic)
	{
		// Only rectColl's gameObject is pushed
		Vector2 targetPos = rectPos + -penetrationVector - rectColl->offset;
		rectColl->gameObject()->transform->setWorldPosition(targetPos);
	}
	else {	// So neither circColl, nor rectColl are static (both can't be static because this function would have never been called
			// Both  circColl's gameObject and rectColl's gameObject are pushed

			// Move rectColl1 away
		Vector2 targetPos1 = circPos + penetrationVector / 2 - circColl->offset;
		circColl->gameObject()->transform->setWorldPosition(targetPos1);
		// Move rectColl2 away
		Vector2 targetPos2 = rectPos + -penetrationVector / 2 - rectColl->offset;
		rectColl->gameObject()->transform->setWorldPosition(targetPos2);
	}

}


void CollidersManager::informCollision(Reference<Collider>& coll1, Reference<Collider>& coll2)
{
	// If non of the colliders are triggers, then the onCollision method should be called
	if (!coll1->isTrigger && !coll2->isTrigger)
	{
		Reference<GameObject>& go1 = coll1->gameObject();
		Reference<GameObject>& go2 = coll2->gameObject();
		// Info about coll2 that will be sent to coll1
		{
			CollisionInfo infoForColl1;
			infoForColl1.otherCollider = coll2;
			infoForColl1.otherGameObject = go2;
			coll1->onCollision(infoForColl1);
		}
		// Info about coll1 that will be sent to coll2
		{
			CollisionInfo infoForColl2;
			infoForColl2.otherCollider = coll1;
			infoForColl2.otherGameObject = go1;
			coll2->onCollision(infoForColl2);
		}
	}
	// If either of the colliders (or both) are triggers, then the onTrigger family of methods should be called
	else
	{
		CollidersPair pair = std::make_pair(coll1, coll2);
		if (m_triggerCollisionCache.cache(pair))
		{
			// If the pair is new, call OnTriggerEnter
			coll1->onTriggerEnter(coll2);
			coll2->onTriggerEnter(coll1);
		}
		else
		{
			// So the pair was already in the cache
			coll1->onTriggerStay(coll2);
			coll2->onTriggerStay(coll1);
		}
	}
	
}


int CollidersManager::getCollisionLayerIndex(const std::string & layerName) const
{
	if (m_collisionSystemSetup.namesToIndexMap.count(layerName) == 0)
	{
		return -1;
	}
	else
	{
		return m_collisionSystemSetup.namesToIndexMap.at(layerName);
	}
}
