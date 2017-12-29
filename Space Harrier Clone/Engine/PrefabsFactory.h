#ifndef H_PREFABS_FACTORY
#define H_PREFABS_FACTORY

#include <map>
#include <string>
#include "globals.h"
#include "ReferenceOwner.h"
class GameObject;
class Prefab;


class PrefabsFactory final
{
public:
	PrefabsFactory();
	~PrefabsFactory();

	template<typename T>
	bool addPrefab(const std::string& id);
	Reference<Prefab> getPrefab(const std::string& id) const;
	Reference<GameObject> instantiate(const Reference<Prefab>& prefab);

private:
	std::map<std::string, ReferenceOwner<Prefab>> m_prefabs;
};


template<typename T>
bool PrefabsFactory::addPrefab(const std::string& id)
{
	// Success flag
	bool success = true;

	if (!std::is_base_of<Prefab, T>::value || std::is_same<Prefab, T>::value)
	{
		success = false;
		OutputLog("ERROR: Can't add selected class of type %s as a prefab!", typeid(T).name());
	}
	else
	{
		if (m_prefabs.count(id) == 1)
		{
			success = false;
			OutputLog("ERROR: The selected id (%s) is already in use!", id.c_str());
		}
		else
		{
			m_prefabs[id] = ReferenceOwner<Prefab>(new T());
		}
	}

	return success;
}


#endif // !H_PREFABS_FACTORY
