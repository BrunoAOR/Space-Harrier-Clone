#ifndef H_RESOURCE_MANAGER
#define H_RESOURCE_MANAGER

#include <map>
#include <string>
#include "globals.h"

template<typename T>
class ResourcesManager
{
public:
	ResourcesManager(void(*deleter)(T*));
	~ResourcesManager();
	bool hasResource(const std::string& name) const;
	std::string getResourceName(T* resource);
	bool saveResource(const std::string& name, T* resource);
	T* getResource(const std::string& name);
	bool returnResource(T* resource, bool deleteIfUnused = true);

private:
	void(*m_deleter)(T*);
	std::map<std::string, T*> m_resources;
	std::map<std::string, int> m_usage;
};


template<typename T>
ResourcesManager<T>::ResourcesManager(void(*deleter)(T*))
{
	m_deleter = deleter;
}


template<typename T>
ResourcesManager<T>::~ResourcesManager()
{
	for (auto it = m_resources.begin(); it != m_resources.end(); ++it)
	{
		if (m_usage[it->first] != 0)
		{
			OutputLog("WARNING: The Resource loaded from %s was still being held by %i users after its deletion!", it->first.c_str(), m_usage[it->first]);
		}
		m_deleter(it->second);
	}
	m_resources.clear();
	m_usage.clear();
}


template<typename T>
bool ResourcesManager<T>::hasResource(const std::string& name) const
{
	return m_resources.count(name) == 1;;
}


template<typename T>
inline std::string ResourcesManager<T>::getResourceName(T * resource)
{
	for (auto it = m_resources.begin(); it != m_resources.end(); ++it)
	{
		if (it->second == resource)
		{
			return it->first;
		}
	}
	return "";
}


template<typename T>
bool ResourcesManager<T>::saveResource(const std::string& name, T* resource)
{
	if (m_resources.count(name) == 1)
	{
		return false;
	}
	else
	{
		m_resources[name] = resource;
		m_usage[name] = 1;
		return true;
	}
}


template<typename T>
T* ResourcesManager<T>::getResource(const std::string& name)
{
	if (m_resources.count(name) == 0)
	{
		return nullptr;
	}
	else
	{
		++m_usage[name];
		return m_resources[name];
	}
}


template<typename T>
bool ResourcesManager<T>::returnResource(T* resource, bool deleteIfUnused)
{
	for (auto it = m_resources.begin(); it != m_resources.end(); ++it)
	{
		if (it->second == resource)
		{
			--m_usage[it->first];

			if (deleteIfUnused && m_usage[it->first] == 0)
			{
				m_deleter(it->second);
				m_usage.erase(it->first);
				m_resources.erase(it);
			}
			return true;
		}
	}
	return false;
}


#endif // !H_RESOURCE_MANAGER
