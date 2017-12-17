#ifndef H_EXPLOSION_PREFAB
#define H_EXPLOSION_PREFAB

#include "Engine/Prefab.h"


class ExplosionPrefab :
	public Prefab
{
public:
	// Inherited via Prefab
	virtual void configureGameObject(Reference<GameObject>& gameObject) const override;
};


#endif // !H_EXPLOSION_PREFAB
