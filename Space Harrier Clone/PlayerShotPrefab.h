#ifndef H_PLAYER_SHOT_PREFAB
#define H_PLAYER_SHOT_PREFAB

#include "Engine/Prefab.h"


class PlayerShotPrefab :
	public Prefab
{
public:
	// Inherited via Prefab
	virtual void configureGameObject(Reference<GameObject>& gameObject) const override;
};


#endif // !H_PLAYER_SHOT_PREFAB
