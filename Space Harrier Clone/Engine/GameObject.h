#ifndef H_GAME_OBJECT
#define H_GAME_OBJECT

#include <string>
#include <vector>
#include <typeinfo>
#include "globals.h"
#include "Engine.h"
#include "ReferenceOwner.h"
#include "ComponentsManager.h"
#include "Transform.h"


class GameObject final
{
	friend class GameObjectsManager;

public:
	~GameObject();

	// Components related
	template<typename T>
	Reference<T> addComponent();
	void removeComponent(const Reference<Component>& component);
	template<typename T>
	Reference<T> getComponent() const;
	template<typename T>
	std::vector<Reference<T>> getComponents() const;
	template<typename T>
	Reference<T> getComponentInChildren() const;
	template<typename T>
	std::vector<Reference<T>> getComponentsInChildren() const;
	template<typename T>
	Reference<T> getComponentInParent() const;
	template<typename T>
	std::vector<Reference<T>> getComponentsInParent() const;

	// On/Off switch
	void setActive(bool activeState);
	bool isActive() const;

	// Creation and destruction related
	static Reference<GameObject> createNew();
	static void destroy(Reference<GameObject>& gameObject);

	Reference<Transform> transform;

	// TESTING FIELDS START
	int m_id;
	// TESTING FIELDS END

private:
	// TESTING FIELDS START
	static int s_alive;
	static int s_nextId;
	// TESTING FIELDS END

	GameObject();

	void doAddComponent(ReferenceOwner<Component>& component);
	void doRemoveComponent(Reference<Component>& component);
	void refreshComponents();

	bool m_isActive;
	bool m_isInCreation;
	Reference<GameObject> m_self;

	// Components related
	std::vector<ReferenceOwner<Component>> m_components;
	std::vector<ReferenceOwner<Component>> m_componentsToAdd;
	std::vector<Reference<Component>> m_componentsToRemove;
};


template<typename T>
Reference<T> GameObject::addComponent()
{
	ReferenceOwner<T> component = engine->componentsManager->createNew<T>(m_self);
	if (component)
	{
		Reference<T> componentRef = component.getReference();
		if (m_isInCreation)
		{
			m_components.push_back(std::move(component));
		}
		else
		{
			m_componentsToAdd.push_back(std::move(component));
		}
		return componentRef;
	}
	else
	{
		OutputLog("WARNING: Can't attach selected class of type %s as a component!", typeid(T).name());
		return Reference<T>();
	}
	
}


template<typename T>
Reference<T> GameObject::getComponent() const
{
	if (!std::is_base_of<Component, T>::value)
	{
		OutputLog("WARNING: Selected class of type %s is not a valid Component!", typeid(T).name());
	}
	else
	{
		for (const ReferenceOwner<Component>& component : m_components)
		{
			if (component.is_castable_as<T>())
			{
				return component.getStaticCastedReference<T>();
			}
		}
	}
	return Reference<T>();
}


template<typename T>
std::vector<Reference<T>> GameObject::getComponents() const
{
	std::vector<Reference<T>> referencesVector;
	if (!std::is_base_of<Component, T>::value)
	{
		OutputLog("WARNING: Selected class of type %s is not a valid component!", typeid(T).name());
	}
	else
	{
		for (const ReferenceOwner<Component>& component : m_components)
		{
			if (component.is_castable_as<T>())
			{
				referencesVector.push_back(component.getStaticCastedReference<T>());
			}
		}
	}
	return referencesVector;
}


template<typename T>
Reference<T> GameObject::getComponentInChildren() const
{
	if (!std::is_base_of<Component, T>::value)
	{
		OutputLog("WARNING: Selected class of type %s is not a valid Component!", typeid(T).name());
	}
	else
	{
		for (const ReferenceOwner<Component>& component : m_components)
		{
			if (component.is_castable_as<T>())
			{
				return component.getStaticCastedReference<T>();
			}
		}

		for (const Reference<Transform>& childTransformRef : transform->getChildren())
		{
			Reference<T> foundComponent = childTransformRef->gameObject()->getComponentInChildren<T>();
			if (foundComponent)
			{
				return foundComponent;
			}
		}
	}
	return Reference<T>();
}


template<typename T>
std::vector<Reference<T>> GameObject::getComponentsInChildren() const
{
	std::vector<Reference<T>> referencesVector;
	if (!std::is_base_of<Component, T>::value)
	{
		OutputLog("WARNING: Selected class of type %s is not a valid component!", typeid(T).name());
	}
	else
	{
		for (const ReferenceOwner<Component>& component : m_components)
		{
			if (component.is_castable_as<T>())
			{
				referencesVector.push_back(component.getStaticCastedReference<T>());
			}
		}

		for (const Reference<Transform>& childTransformRef : transform->getChildren())
		{
			std::vector<Reference<T>> foundComponents = childTransformRef->gameObject()->getComponentsInChildren<T>();
			if (foundComponents.size() > 0)
			{
				referencesVector.insert(referencesVector.end(), foundComponents.begin(), foundComponents.end());
			}
		}
	}
	return referencesVector;
}


template<typename T>
Reference<T> GameObject::getComponentInParent() const
{
	if (!std::is_base_of<Component, T>::value)
	{
		OutputLog("WARNING: Selected class of type %s is not a valid Component!", typeid(T).name());
	}
	else
	{
		for (const ReferenceOwner<Component>& component : m_components)
		{
			if (component.is_castable_as<T>())
			{
				return component.getStaticCastedReference<T>();
			}
		}
		
		const Reference<Transform>& parentTransform = transform->getParent();
		if (parentTransform)
		{
			Reference<T> foundComponent = parentTransform->gameObject()->getComponentInParent<T>();
			if (foundComponent)
			{
				return foundComponent;
			}
		}
	}
	return Reference<T>();
}


template<typename T>
 std::vector<Reference<T>> GameObject::getComponentsInParent() const
{
	 std::vector<Reference<T>> referencesVector;
	 if (!std::is_base_of<Component, T>::value)
	 {
		 OutputLog("WARNING: Selected class of type %s is not a valid component!", typeid(T).name());
	 }
	 else
	 {
		 for (const ReferenceOwner<Component>& component : m_components)
		 {
			 if (component.is_castable_as<T>())
			 {
				 referencesVector.push_back(component.getStaticCastedReference<T>());
			 }
		 }

		 const Reference<Transform>& parentTransform = transform->getParent();
		 if (parentTransform)
		 {
			 std::vector<Reference<T>> foundComponents = parentTransform->gameObject()->getComponentsInParent<T>();
			 if (foundComponents.size() > 0)
			 {
				 referencesVector.insert(referencesVector.end(), foundComponents.begin(), foundComponents.end());
			 }
		 }
	 }
	 return referencesVector;
}


#endif // !H_GAME_OBJECT
