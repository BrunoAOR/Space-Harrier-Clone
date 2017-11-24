#ifndef H_RENDERERS_MANAGER
#define H_RENDERERS_MANAGER

#include <unordered_map>
#include <string>
#include <list>
#include "SDL2/include/SDL.h"
#include "ComponentManager.h"
#include "Reference.h"
class Component;
class Renderer;


class RenderersManager final :
	public ComponentManager
{
	friend class ComponentsManager;
public:
	~RenderersManager();
	bool changeRendererLayer(const Renderer* renderer, const std::string& previousLayer, const std::string& newLayer);
	void markLayerAsDirty(const std::string& layerName);

private:
	RenderersManager();

	// Inherited via ComponentManager
	virtual bool subscribeComponent(Reference<Component>& component) override;
	virtual bool unsubscribeComponent(Reference<Component>& component) override;

	virtual ComponentType managedComponentType() const override;
	virtual void update() override;
	virtual bool init() override;
	virtual void close() override;
	virtual bool initializeComponent(Reference<Component>& component) override;
	
	void refreshRenderers();
	bool validateLayerName(const std::string& layerName) const;
	Reference<Renderer> removeRendererFromLayer(const Renderer* renderer, const std::string& layerToRemoveFrom);

	SDL_Window* m_window = nullptr;
	SDL_Renderer* m_renderer = nullptr;
	std::vector<std::string> m_renderLayers;

	std::unordered_map<std::string, std::list<Reference<Renderer>>> m_renderers;
	std::unordered_map<std::string, bool> m_dirtyFlags;
};


#endif // !H_RENDERERS_MANAGER
