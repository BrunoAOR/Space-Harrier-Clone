#ifndef H_SPRITE_RENDERER
#define H_SPRITE_RENDERER

#include "Renderer.h"


class SpriteRenderer :
	public Renderer
{
	friend class RenderersManager;
public:
	SpriteRenderer();
	~SpriteRenderer();

	bool loadImage(const std::string& path, bool isUnique = false);
	bool loadImage(const std::string& path, Uint32 colorKey, bool isUnique = false);

	// Set color modulation
	void setColor(Uint8 r, Uint8 g, Uint8 b);

	// Set Blend Mode
	void setBlendMode(SDL_BlendMode blendMode);

	// Set alpha modulation
	void setAlpha(Uint8 a);

private:
	bool loadImage(const std::string& path, bool shouldColorKey, Uint32 colorKey, bool isUnique);
	void makeUnique();

	bool m_usesColorKey;
	Uint32 m_colorKey;
};


#endif // !H_SPRITE_RENDERER
