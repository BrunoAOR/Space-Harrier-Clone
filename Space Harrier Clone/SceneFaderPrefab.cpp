#include "SceneFaderPrefab.h"

#include <assert.h>
#include "Engine/GameObject.h"
#include "EngineExt/RectangleRenderer.h"
#include "SceneFader.h"


void SceneFaderPrefab::configureGameObject(Reference<GameObject>& gameObject) const
{
	auto sceneFader = gameObject->addComponent<SceneFader>();
	auto rectangleRenderer = gameObject->addComponent<RectangleRenderer>();
	assert(sceneFader && rectangleRenderer);
}
