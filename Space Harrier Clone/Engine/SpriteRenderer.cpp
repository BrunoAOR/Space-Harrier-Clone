#include "SpriteRenderer.h"

#include "SDL2_image/include/SDL_image.h"
#include "globals.h"
#include "ResourcesManager.h"


SpriteRenderer::SpriteRenderer()
{
}


SpriteRenderer::~SpriteRenderer()
{
}


bool SpriteRenderer::loadImage(const std::string& path, bool isUnique)
{
	return loadImage(path, false, 0, isUnique);
}


bool SpriteRenderer::loadImage(const std::string& path, Uint32 colorKey, bool isUnique)
{
	m_usesColorKey = true;
	m_colorKey = colorKey;
	return loadImage(path, true, colorKey, isUnique);
}



void SpriteRenderer::setColor(Uint8 r, Uint8 g, Uint8 b)
{
	// Modulate texture color
	if (m_texture != nullptr) {
		makeUnique();
		SDL_SetTextureColorMod(m_texture, r, g, b);
	}
}


void SpriteRenderer::setBlendMode(SDL_BlendMode blendMode)
{
	// Set blending function
	if (m_texture != nullptr) {
		makeUnique();
		SDL_SetTextureBlendMode(m_texture, blendMode);
	}
}


void SpriteRenderer::setAlpha(Uint8 alpha)
{
	// Modulate texture alpha
	if (m_texture != nullptr) {
		makeUnique();
		SDL_SetTextureAlphaMod(m_texture, alpha);
	}
}


bool SpriteRenderer::loadImage(const std::string& path, bool shouldColorKey, Uint32 colorKey, bool isUnique)
{
	// Get rid of previous texture
	free();

	m_isTextureUnique = isUnique;

	if (m_isTextureUnique || !m_texturesManager->hasResource(path))
	{
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
		if (!m_isTextureUnique && m_texture != nullptr)
		{
			m_texturesManager->saveResource(path, m_texture);
		}
	}
	else
	{
		m_texture = m_texturesManager->getResource(path);
		SDL_QueryTexture(m_texture, nullptr, nullptr, &m_width, &m_height);
	}

	return m_texture != nullptr;
}


void SpriteRenderer::makeUnique()
{
	if (m_texture && !m_isTextureUnique)
	{
		std::string path = m_texturesManager->getResourceName(m_texture);
		free();
		if (m_usesColorKey)
		{
			loadImage(path, m_colorKey, true);
		}
		else
		{
			loadImage(path, true);
		}
	}
}
