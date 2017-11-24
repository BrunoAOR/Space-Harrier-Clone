#ifndef H_COMPONENT_MANAGER
#define H_COMPONENT_MANAGER

#include <vector>
#include "ReferenceOwner.h"
class Component;
enum class ComponentType;


class ComponentManager
{
public:
	ComponentManager();
	virtual ~ComponentManager();

	virtual bool subscribeComponent(Reference<Component>& component);
	virtual bool unsubscribeComponent(Reference<Component>& component);
	
	virtual ComponentType managedComponentType() const = 0;
	virtual void update() = 0;
	virtual bool init() = 0;
	virtual void close() = 0;
	virtual bool initializeComponent(Reference<Component>& component) = 0;

protected:
	void refreshComponents();
	void removeEmptyReferences();
	void doSubscribe(const Reference<Component>& component);
	void doUnsubscribe(const Reference<Component>& component);
	ComponentType getComponentType(const Reference<Component>& component) const;

	std::vector<Reference<Component>> m_components;
	std::vector<Reference<Component>> m_componentsToSubscribe;
	std::vector<Reference<Component>> m_componentsToUnsubscribe;
};


#endif // !H_COMPONENT_MANAGER
