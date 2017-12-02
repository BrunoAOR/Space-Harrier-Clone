#include "SpriteRenderer.h"

#include "SDL2_image/include/SDL_image.h"
#include "globals.h"


SpriteRenderer::SpriteRenderer()
{
}


SpriteRenderer::~SpriteRenderer()
{
}


bool SpriteRenderer::loadImage(const std::string& path)
{
	return loadImage(path, false, 0);
}


bool SpriteRenderer::loadImage(const std::string& path, Uint32 colorKey)
{
	return loadImage(path, true, colorKey);
}



void SpriteRenderer::setColor(Uint8 r, Uint8 g, Uint8 b) const
{
	// Modulate texture color
	if (m_texture != nullptr) {
		SDL_SetTextureColorMod(m_texture, r, g, b);
	}
}


void SpriteRenderer::setBlendMode(SDL_BlendMode blendMode) const
{
	// Set blending function
	if (m_texture != nullptr) {
		SDL_SetTextureBlendMode(m_texture, blendMode);
	}
}


void SpriteRenderer::setAlpha(Uint8 alpha) const
{
	// Modulate texture alpha
	if (m_texture != nullptr) {
		SDL_SetTextureAlphaMod(m_texture, alpha);
	}
}


bool SpriteRenderer::loadImage(const std::string& path, bool shouldColorKey, Uint32 colorKey)
{
	// Get rid of previous texture
	free();

	// Load image at specified path as surface
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		OutputLog("Error: Unable to load image at path %s! SDL_image Error: %s", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image if required
		if (shouldColorKey)
		{
			if (SDL_SetColorKey(loadedSurface, SDL_TRUE, colorKey) != 0)
			{
				OutputLog("Warning: Unable to color key the loaded image at path %s! SDL Error: %s", path.c_str(), SDL_GetError());
			}
		}

		// Create texture from surface
		m_texture = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);
		if (m_texture == nullptr)
		{
			OutputLog("Error: Unable to create texture for image at path %s! SDL Error: %s", path.c_str(), SDL_GetError());
		}
		else
		{
			// Store image dimension
			m_width = loadedSurface->w;
			m_height = loadedSurface->h;
		}

		// Free the loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return m_texture != nullptr;
}
