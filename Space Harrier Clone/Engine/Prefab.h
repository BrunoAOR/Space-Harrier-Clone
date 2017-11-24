#ifndef H_PREFAB
#define H_PREFAB

template<typename T>
class Reference;
class GameObject;

class Prefab
{
public:
	virtual ~Prefab() = 0 {};

protected:
	virtual Reference<GameObject> configureGameObject() = 0;
};


#endif // !H_PREFAB
