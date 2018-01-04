#include "SceneFaderPrefab.h"

#include <assert.h>
#include "Engine/GameObject.h"
#include "EngineExt/RectangleRenderer.h"
#include "SceneFader.h"


void SceneFaderPrefab::configureGameObject(Reference<GameObject>& gameObject) const
{
	assert(gameObject->addComponent<SceneFader>());
	assert(gameObject->addComponent<RectangleRenderer>());
}
