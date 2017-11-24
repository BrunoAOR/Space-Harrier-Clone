#ifndef H_PREFABS_FACTORY
#define H_PREFABS_FACTORY

template<typename T>
class Reference;
class GameObject;
class Prefab;

class PrefabsFactory final
{
public:
	template<typename T>
	static Reference<GameObject> instantiate();

private:
	PrefabsFactory() {};
	~PrefabsFactory() {};
};


template<typename T>
Reference<GameObject> PrefabsFactory::instantiate()
{
	if (!std::is_base_of<Prefab, T>::value || std::is_abstract<T>::value)
	{
		return Reference<GameObject>();
	}
	else
	{
		return T().configureGameObject();
	}
}


#endif // !H_PREFABS_FACTORY
