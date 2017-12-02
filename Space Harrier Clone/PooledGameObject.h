#ifndef H_POOLED_GAME_OBJECT
#define H_POOLED_GAME_OBJECT

#include "Engine/Behaviour.h"


class PooledGameObject :
	public Behaviour
{
	friend class GameObjectPool;

public:
	void returnToPool();

private:
	GameObjectPool* m_pool = nullptr;
};


#endif // !H_POOLED_GAME_OBJECT
