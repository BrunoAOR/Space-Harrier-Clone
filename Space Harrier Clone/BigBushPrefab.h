#ifndef H_BIG_BUSH_PREFAB
#define H_BIG_BUSH_PREFAB

#include "Engine/Prefab.h"


class BigBushPrefab :
	public Prefab
{
public:
	// Inherited via Prefab
	virtual void configureGameObject(Reference<GameObject>& gameObject) const override;
};


#endif // !H_BIG_BUSH_PREFAB
