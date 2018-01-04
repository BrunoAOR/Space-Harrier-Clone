#ifndef H_SCENE_FADER_PREFAB
#define H_SCENE_FADER_PREFAB

#include "Engine/Prefab.h"


class SceneFaderPrefab :
	public Prefab
{
public:
	// Inherited via Prefab
	virtual void configureGameObject(Reference<GameObject>& gameObject) const override;
};


#endif // !H_SCENE_FADER_PREFAB
