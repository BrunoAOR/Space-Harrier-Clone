#ifndef H_GAME_OBJECTS_MANAGER
#define H_GAME_OBJECTS_MANAGER

#include <vector>
#include "ReferenceOwner.h"
class GameObject;
class Transform;


class GameObjectsManager final
{
public:
	GameObjectsManager();
	~GameObjectsManager();

	void update();
	void addGameObject(ReferenceOwner<GameObject>& gameObject);
	void destroyGameObject(Reference<GameObject>& gameObject);
	void destroyAllGameObjects();
	
private:
	void refreshGameObjects();
	void doAddGameObject(ReferenceOwner<GameObject>& gameObject);
	void doDestroyGameObject(Reference<GameObject>& gameObject);
	void doDestroyChildren(Transform* transform);

	std::vector<ReferenceOwner<GameObject>> m_gameObjects;
	std::vector<ReferenceOwner<GameObject>> m_gosToAdd;
	std::vector<Reference<GameObject>> m_gosToDestroy;
};


#endif // !H_GAME_OBJECTS_MANAGER
