#ifndef H_COMPONENTS_MANAGER
#define H_COMPONENTS_MANAGER

#include <vector>
#include "Component.h"
#include "ReferenceOwner.h"
class GameObject;
class ComponentManager;


class ComponentsManager final
{
public:
	ComponentsManager();
	~ComponentsManager();
	
	bool init();
	void close();

	void update() const;

	template<typename T>
	ReferenceOwner<T> createNew(Reference<GameObject>& goRef) const;

private:
	bool sendToManager(Reference<Component> component) const;

	std::vector<ComponentManager*> m_componentManagers;
};


template<typename T>
ReferenceOwner<T> ComponentsManager::createNew(Reference<GameObject>& goRef) const
{
	if (!std::is_base_of<Component, T>::value || std::is_abstract<T>::value)
	{
		return ReferenceOwner<T>();
	}
	else
	{
		// Special case: A GameObject may only contain 1 Transform (added after GameObject instantiation
		if (typeid(T) == typeid(Transform) && goRef->transform)
		{
			return ReferenceOwner<T>();
		}
		else
		{
			auto component = ReferenceOwner<T>(new T());
			component->m_gameObject = goRef;
			component->m_self = component;

			if (typeid(T) != typeid(Transform) && !sendToManager(component.getStaticCastedReference<Component>()))
			{
				component.deleteReferences();
			}
			return component;
		}
	}
}


#endif // !H_COMPONENTS_MANAGER
