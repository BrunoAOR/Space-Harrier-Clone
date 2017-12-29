#ifndef H_ENEMY_BALL_PREFAB
#define H_ENEMY_BALL_PREFAB

#include "Engine/Prefab.h"


class EnemyBallPrefab :
	public Prefab
{
public:
	// Inherited via Prefab
	virtual void configureGameObject(Reference<GameObject>& gameObject) const override;
};


#endif // !H_ENEMY_BALL_PREFAB
