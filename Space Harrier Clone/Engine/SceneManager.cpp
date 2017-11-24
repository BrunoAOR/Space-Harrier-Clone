#include "SceneManager.h"

#include "Engine.h"
#include "EngineUtils.h"
#include "Scene.h"
#include "GameObjectsManager.h"


SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}


bool SceneManager::hasActiveScene() const
{
	return m_activeScene != nullptr;
}


void SceneManager::refreshScenes()
{
	doLoadScene();
}


void SceneManager::loadScene(unsigned int index)
{
	if (index >= 0 && index < m_scenes.size())
	{
		m_sceneToLoad = m_scenes.at(index);
	}
}


void SceneManager::close()
{
	if (m_activeScene)
	{
		unloadScene(m_activeScene);
	}
	for (Scene* scene : m_scenes)
	{
		delete scene;
	}
	m_scenes.clear();
}


void SceneManager::doLoadScene()
{
	if (!m_sceneToLoad)
	{
		return;
	}

	if (m_activeScene)
	{
		unloadScene(m_activeScene);
		m_activeScene = nullptr;
	}
	// Set scene as active
	m_activeScene = m_sceneToLoad;
	// reset m_sceneToLoad
	m_sceneToLoad = nullptr;
	// Load scene
	m_activeScene->load();
}


void SceneManager::unloadScene(Scene* sceneToUnload) const
{
	if (sceneToUnload != nullptr)
	{
		sceneToUnload->unload();
		engine->gameObjectsManager->destroyAllGameObjects();
	}
}
