#ifndef H_BOSS_1_PREFAB
#define H_BOSS_1_PREFAB

#include "Engine/Prefab.h"


class Boss1Prefab :
	public Prefab
{
public:
	// Inherited via Prefab
	virtual void configureGameObject(Reference<GameObject>& gameObject) const override;
};


#endif // !H_BOSS_1_PREFAB
