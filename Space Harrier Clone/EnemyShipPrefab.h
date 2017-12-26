#ifndef H_ENEMY_SHIP_PREFAB
#define H_ENEMY_SHIP_PREFAB

#include "Engine/Prefab.h"


class EnemyShipPrefab :
	public Prefab
{
public:
	// Inherited via Prefab
	virtual void configureGameObject(Reference<GameObject>& gameObject) const override;
};


#endif // !H_ENEMY_SHIP_PREFAB
