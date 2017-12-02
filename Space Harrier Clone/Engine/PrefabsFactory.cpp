#include "PrefabsFactory.h"

#include "Reference.h"
#include "GameObject.h"
#include "Prefab.h"


PrefabsFactory::PrefabsFactory()
{
}


PrefabsFactory::~PrefabsFactory()
{
}


Reference<Prefab> PrefabsFactory::getPrefab(const std::string & id) const
{
	if (m_prefabs.count(id) == 0)
	{
		OutputLog("WARNING: There is no registered Prefab with an id of %s!", id.c_str());
		return Reference<Prefab>();
	}
	else
	{
		return m_prefabs.at(id).getReference();
	}
}


Reference<GameObject> PrefabsFactory::instantiate(const Reference<Prefab>& prefab)
{
	if (prefab) {
		Reference<GameObject> go = GameObject::createNew();
		prefab->configureGameObject(go);
		return go;
	}
	else
	{
		return Reference<GameObject>();
	}
}

