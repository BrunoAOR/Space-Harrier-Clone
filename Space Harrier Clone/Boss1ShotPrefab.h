#ifndef H_BOSS_1_SHOT_PREFAB
#define H_BOSS_1_SHOT_PREFAB

#include "Engine/Prefab.h"


class Boss1ShotPrefab :
	public Prefab
{
public:
	// Inherited via Prefab
	virtual void configureGameObject(Reference<GameObject>& gameObject) const override;
};


#endif // !H_BOSS_1_SHOT_PREFAB
