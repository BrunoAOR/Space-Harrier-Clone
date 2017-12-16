#ifndef H_ROCK_PREFAB
#define H_ROCK_PREFAB

#include "Engine/Prefab.h"


class RockPrefab :
	public Prefab
{
public:
	// Inherited via Prefab
	virtual void configureGameObject(Reference<GameObject>& gameObject) const override;
};


#endif // !H_ROCK_PREFAB
