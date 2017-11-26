#ifndef H_GAME_SCENE
#define H_GAME_SCENE

#include "Engine/Scene.h"


class GameScene :
	public Scene
{
public:
	// Inherited via Scene
	virtual bool load() override;
	virtual void unload() override;
};


#endif // !H_GAME_SCENE
