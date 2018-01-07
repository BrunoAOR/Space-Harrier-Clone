#include "RenderersManager.h"

#include <algorithm>
#include "SDL2_image/include/SDL_image.h"
#include "gameConfig.h"
#include "globals.h"
#include "EngineUtils.h"
#include "ComponentType.h"
#include "Reference.h"
#include "Renderer.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "Component.h"
#include "ResourcesManager.h"


RenderersManager::RenderersManager()
{
}


RenderersManager::~RenderersManager()
{
}


bool RenderersManager::changeRendererLayer(const Renderer* renderer, const std::string & previousLayer, const std::string & newLayer)
{
	if (!validateLayerName(newLayer) || !validateLayerName(previousLayer))
	{
		return false;
	}

	Reference<Renderer> removedRenderer = removeRendererFromLayer(renderer, previousLayer);

	if (!removedRenderer)
	{
		return false;
	}

	m_dirtyFlags[previousLayer] = true;
	m_renderers[newLayer].push_back(removedRenderer);
	m_dirtyFlags[newLayer] = true;

	return true;
}


void RenderersManager::markLayerAsDirty(const std::string & layerName)
{
	if (validateLayerName(layerName))
	{
		m_dirtyFlags[layerName] = true;
	}
}


bool RenderersManager::subscribeComponent(Reference<Component>& component)
{
	if (managedComponentType() == getComponentType(component))
	{
		// If component is not already in the m_renderers map of lists, add it
		bool found = false;
		for (auto& mapEntry : m_renderers)
		{
			for (Reference<Renderer>& renderer : mapEntry.second)
			{
				if (component == renderer)
				{
					found = true;
					return false;
				}
			}
		}
		Reference<Renderer> renderer = component.static_reference_cast<Renderer>();
		std::string layerName = renderer->getRenderLayer();
		if (!validateLayerName(layerName))
		{
			layerName = m_renderLayers[m_renderLayers.size()-1];
		}
		m_renderers[layerName].push_back(renderer);
		m_dirtyFlags[layerName] = true;
		initializeComponent(component);
		return true;
	}
	return false;
}


bool RenderersManager::unsubscribeComponent(Reference<Component>& component)
{
	for (auto& mapEntry : m_renderers)
	{
		for (auto it = mapEntry.second.begin(); it != mapEntry.second.end(); ++it)
		{
			if (component == (*it))
			{
				mapEntry.second.erase(it);
				return true;
			}
		}
	}
	return false;
}


ComponentType RenderersManager::managedComponentType() const
{
	return ComponentType::RENDERER;
}


void RenderersManager::update()
{
	// Note: refreshRenderers ensures that all Reference in m_components are valid, so they can be safely used
	refreshRenderers();

	// Set Render Color to black transparent
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);

	// Clear screen
	SDL_RenderClear(m_renderer);

	for (const std::string& layerName : m_renderLayers)
	{
		for (Reference<Renderer>& rendererRef : m_renderers[layerName])
		{
			// Actual update
			if (rendererRef->isActive())
			{
				rendererRef->render();
			}
		}
	}

	// Update screen
	SDL_RenderPresent(m_renderer);
}


bool RenderersManager::init()
{
	// Success flag
	bool success = true;

	// Create window
	m_window = SDL_CreateWindow(GAME_NAME.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH * SCREEN_SIZE, SCREEN_HEIGHT * SCREEN_SIZE, SDL_WINDOW_SHOWN);
	if (m_window == nullptr)
	{
		OutputLog("Error: Window could not be created! SDL Error: %s", SDL_GetError());
		success = false;
	}
	else
	{
		// Create Renderer for window (used for texture rendering)
		Uint32 flags = SDL_RENDERER_ACCELERATED;
		if (USE_VSYNC)
		{
			flags |= SDL_RENDERER_PRESENTVSYNC;
		}
		m_renderer = SDL_CreateRenderer(m_window, -1, flags);
		if (m_renderer == nullptr)
		{
			OutputLog("Error: Renderer could not be created! SDL Error: %s", SDL_GetError());
			success = false;
		}
		// Create the drawLayers map nad the dirtyFlags map
		else
		{
			// Add the 'default' layer at the beggining of the list
			m_renderLayers = renderLayersConfig();
			m_renderLayers.push_back("default");
			for (const std::string& layer : m_renderLayers)
			{
				m_renderers[layer] = std::list<Reference<Renderer>>();
				m_dirtyFlags[layer] = false;
			}
		}
	}
	m_texturesManager = new ResourcesManager<SDL_Texture>(SDL_DestroyTexture);

	return success;
}


void RenderersManager::close()
{
	delete m_texturesManager;
	m_texturesManager = nullptr;
	SDL_DestroyRenderer(m_renderer);
	m_renderer = nullptr;
	SDL_DestroyWindow(m_window);
	m_window = nullptr;
}


bool RenderersManager::initializeComponent(Reference<Component>& component)
{
	// At this point, we know that component is a Renderer (or a sub-class there-of)
	if (component)
	{
		auto renderer = component.static_reference_cast<Renderer>();
		renderer->m_renderer = m_renderer;
		renderer->m_renderersManager = this;
		renderer->m_texturesManager = m_texturesManager;
		return true;
	}
	return false;
}



void RenderersManager::refreshRenderers()
{
	// First remove any empty References
	for (auto& mapEntry : m_renderers)
	{
		mapEntry.second.remove_if([](Reference<Renderer>& renderer) -> bool {return !renderer; });
	}

	// Next verify if any layerList needs sort and if so, sort
	for (const std::string& layerName : m_renderLayers)
	{
		if (m_dirtyFlags[layerName] == true)
		{
			m_renderers[layerName].sort([](Reference<Renderer>& renderer1, Reference<Renderer>& renderer2) -> bool { return renderer1->getZIndex() < renderer2->getZIndex(); });
			m_dirtyFlags[layerName] = false;
		}
	}
}


bool RenderersManager::validateLayerName(const std::string& layerName) const
{
	for (const std::string& name : m_renderLayers)
	{
		if (layerName == name)
		{
			return true;
		}
	}
	return false;
}


Reference<Renderer> RenderersManager::removeRendererFromLayer(const Renderer* renderer, const std::string & layerToRemoveFrom)
{
	std::list<Reference<Renderer>>& selectedList = m_renderers[layerToRemoveFrom];
	for (auto& it = selectedList.begin(); it != selectedList.end(); ++it)
	{
		if ((*it).get() == renderer)
		{
			Reference<Renderer> ref = (*it);
			selectedList.erase(it);
			return ref;
		}
	}
	return Reference<Renderer>();
}