#ifndef H_TRANSFORM
#define H_TRANSFORM

#include "Component.h"
#include <vector>
#include "Reference.h"
#include "Vector2.h"


class Transform final :
	public Component
{
	friend class GameObjectsManager;

public:
	Transform();

	// Position
	Vector2 getLocalPosition() const;
	Vector2 getWorldPosition() const;
	void setLocalPosition(const Vector2& position);
	void setWorldPosition(const Vector2& position);

	// Rotation
	float getLocalRotation() const;
	float getWorldRotation() const;
	void setLocalRotation(float rotation);
	void setWorldRotation(float rotation);

	// Scale
	Vector2 getLocalScale() const;
	Vector2 getWorldScale() const;
	void setLocalScale(const Vector2& scale);
	void setWorldScale(const Vector2& scale);

	// Helper methods
	Vector2 localToWorldPosition(const Vector2& localPosition) const;
	Vector2 worldToLocalPosition(const Vector2& worldPosition) const;
	float localToWorldRotation(float localRotation) const;
	float worldToLocalRotation(float worldRotation) const;
	Vector2 localToWorldScale(const Vector2& localScale) const;
	Vector2 worldToLocalScale(const Vector2& worldScale) const;

	// Hierarchy related
	const Reference<Transform>& getParent() const;
	Reference<Transform>& getParent();
	std::vector<Reference<Transform>> getChildren() const;
	bool setParent(Reference<Transform>& parent, bool keepWorldPosition = true);
	void removeParent();

private:
	bool addChild(Transform* childTransform);
	bool removeChild(Transform* childTransform);
	bool isTransformInChildrenHierarchy(Transform* transform) const;

	void updateLocalFields();
	void updateWorldFields();
	void updateChildrenWorldFields() const;

	// Hiding inherited members from Component
	void setActive(bool activeState);
	bool isActive();

	Vector2 m_localPosition;
	float m_localRotation;
	Vector2 m_localScale;

	Vector2 m_worldPosition;
	float m_worldRotation;
	Vector2 m_worldScale;

	// Hierarchy related
	Transform* m_parentTransform = nullptr;
	Reference<Transform> m_parentRef;
	std::vector<Transform*> m_children;
	std::vector<Reference<Transform>> m_childrenRef;
};


#endif // !H_TRANSFORM
