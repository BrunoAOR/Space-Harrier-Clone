#ifndef H_RECTANGLE_RENDERER
#define H_RECTANGLE_RENDERER

#include "../Engine/Renderer.h"


class RectangleRenderer :
	public Renderer
{
public:
	RectangleRenderer();
	~RectangleRenderer();

	// Inherited via Renderer
	virtual void render() override;

	SDL_Rect rect;
	SDL_Color color;
};


#endif // !H_RECTANGLE_RENDERER
