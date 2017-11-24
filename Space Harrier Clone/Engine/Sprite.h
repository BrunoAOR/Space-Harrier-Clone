#ifndef H_SPRITE
#define H_SPRITE

#include "SpriteRenderer.h"


class Sprite final:
	public SpriteRenderer
{
public:
	Sprite();
	~Sprite();

	// Inherited via Renderer
	virtual void render() override;

	SDL_Rect getClipRect() const;
	void setClipRect(const SDL_Rect& rect);
	void resetClipRect();

private:
	bool m_hasClipRect = false;
	SDL_Rect m_clipRect;
};


#endif // !H_SPRITE
