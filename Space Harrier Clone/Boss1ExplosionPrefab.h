#ifndef H_BOSS_1_EXPLOSION_PREFAB
#define H_BOSS_1_EXPLOSION_PREFAB

#include "Engine/Prefab.h"


class Boss1ExplosionPrefab :
	public Prefab
{
public:
	// Inherited via Prefab
	virtual void configureGameObject(Reference<GameObject>& gameObject) const override;
};


#endif // !H_BOSS_1_EXPLOSION_PREFAB
