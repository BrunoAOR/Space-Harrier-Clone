#ifndef H_RENDERER
#define H_RENDERER

#include "SDL2/include/SDL_render.h"
#include <string>
#include "Component.h"
#include "Vector2.h"


class Renderer :
	public Component
{
	friend class RenderersManager;
public:
	Renderer();
	virtual ~Renderer() = 0;

	virtual void render() = 0;

	// Get dimensions
	int getWidth() const;
	int getHeight() const;

	// Pivots
	Vector2 getPositionPivot() const;
	void setPositionPivot(const Vector2& positionPivot);

	Vector2 getRotationPivot() const;
	void setRotationPivot(const Vector2& rotationPivot);

	Vector2 getScalePivot() const;
	void setScalePivot(const Vector2& scalePivot);

	void setAllPivots(const Vector2& pivot);

	const std::string& getRenderLayer() const;
	bool setRenderLayer(const std::string& drawLayer);
	int getZIndex() const;
	void setZIndex(int zIndex);

protected:
	// Renders texture at given point
	void renderMain(SDL_Rect* clip = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE) const;

	void free();

	// The renderer associated with this texture
	SDL_Renderer* m_renderer = nullptr;
	RenderersManager* m_renderersManager = nullptr;

	// The actual hardware texture
	SDL_Texture* m_texture = nullptr;

	// Image dimensions
	int m_width = 0;
	int m_height = 0;

private:
	// Pivots
	Vector2 m_positionPivot;
	Vector2 m_rotationPivot;
	Vector2 m_scalePivot;

	// Draw-depth information
	std::string m_renderLayer;
	int m_zIndex;
};


#endif // !H_RENDERER
