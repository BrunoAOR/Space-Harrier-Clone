#ifndef H_SCENE_MANAGER
#define H_SCENE_MANAGER

#include <typeinfo>
#include <vector>
#include "globals.h"
class Scene;


class SceneManager final
{
public:
	SceneManager();
	~SceneManager();

	void refreshScenes();
	void loadScene(unsigned int index);
	void close();

	template<typename T>
	bool addScene();
	bool hasActiveScene() const;

private:
	void doLoadScene();
	void unloadScene(Scene* sceneToUnload) const;

	std::vector<Scene*> m_scenes;
	Scene* m_activeScene = nullptr;
	Scene* m_sceneToLoad = nullptr;
};

template<typename T>
bool SceneManager::addScene()
{
	// Success flag
	bool success = true;

	if (std::is_base_of<Scene, T>::value && !std::is_same<Scene, T>::value)
	{
		m_scenes.push_back(new T());
	}
	else
	{
		success = false;
		OutputLog("ERROR: Can't add selected class of type %s as a scene!", typeid(T).name());
	}

	return success;
}


#endif // !H_SCENE_MANAGER
