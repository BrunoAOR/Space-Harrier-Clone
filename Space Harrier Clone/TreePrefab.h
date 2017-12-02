#ifndef H_TREE_PREFAB
#define H_TREE_PREFAB

#include "Engine/Prefab.h"


class TreePrefab :
	public Prefab
{
public:
	// Inherited via Prefab
	virtual void configureGameObject(Reference<GameObject>& gameObject) const override;
};


#endif // !H_TREE_PREFAB
