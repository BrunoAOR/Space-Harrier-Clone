#ifndef H_BEHAVIOURS_MANAGER
#define H_BEHAVIOURS_MANAGER

#include "ComponentManager.h"
#include "Reference.h"
class Component;


class BehavioursManager final :
	public ComponentManager
{
	friend class ComponentsManager;

public:
	~BehavioursManager();

private:
	BehavioursManager();

	// Inherited via ComponentManager
	virtual ComponentType managedComponentType() const override;
	virtual void update() override;
	virtual bool init() override;
	virtual void close() override;
	virtual bool initializeComponent(Reference<Component>& component) override;
};


#endif // !H_BEHAVIOURS_MANAGER
