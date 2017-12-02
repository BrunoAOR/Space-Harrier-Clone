#ifndef H_PREFAB
#define H_PREFAB

template<typename T>
class Reference;
class GameObject;


class Prefab
{
	friend class PrefabFactory;

public:
	virtual ~Prefab() = 0 {};
	virtual void configureGameObject(Reference<GameObject>& gameObject) const = 0;

protected:
	Prefab() {}
};


#endif // !H_PREFAB
