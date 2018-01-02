#ifndef H_BOSS_1_CHAIN_LINK_PREFAB
#define H_BOSS_1_CHAIN_LINK_PREFAB

#include "Engine/Prefab.h"


class Boss1ChainLinkPrefab :
	public Prefab
{
public:
	// Inherited via Prefab
	virtual void configureGameObject(Reference<GameObject>& gameObject) const override;
};


#endif // !H_BOSS_1_CHAIN_LINK_PREFAB
