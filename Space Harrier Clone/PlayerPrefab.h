#ifndef H_PLAYER_PREFAB
#define H_PLAYER_PREFAB

#include "Engine/Prefab.h"


class PlayerPrefab :
	public Prefab
{
public:
	// Inherited via Prefab
	virtual void configureGameObject(Reference<GameObject>& gameObject) const override;
};


#endif // !H_PLAYER_PREFAB
