#ifndef H_SMALL_BUSH_OREFAB
#define H_SMALL_BUSH_OREFAB

#include "Engine/Prefab.h"


class SmallBushPrefab :
	public Prefab
{
public:
	// Inherited via Prefab
	virtual void configureGameObject(Reference<GameObject>& gameObject) const override;
};


#endif // !H_SMALL_BUSH_OREFAB
