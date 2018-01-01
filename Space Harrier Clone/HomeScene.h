#ifndef H_HOME_SCENE
#define H_HOME_SCENE

#include "Engine/Scene.h"


class HomeScene :
	public Scene
{
public:
	// Inherited via Scene
	virtual bool load() override;
	virtual void unload() override;
};


#endif // !H_HOME_SCENE
