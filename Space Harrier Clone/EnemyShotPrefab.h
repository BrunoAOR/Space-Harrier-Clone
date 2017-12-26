#ifndef H_ENEMY_SHOT_PREFAB
#define H_ENEMY_SHOT_PREFAB

#include "Engine/Prefab.h"


class EnemyShotPrefab :
	public Prefab
{
public:
	// Inherited via Prefab
	virtual void configureGameObject(Reference<GameObject>& gameObject) const override;
};


#endif // !H_ENEMY_SHOT_PREFAB
