#include "TextRenderer.h"

#include "SDL2_image/include/SDL_image.h"
#include "globals.h"
#include "gameConfig.h"
#include "PixelPosition.h"


TextRenderer::TextRenderer()
	: m_text("")
	, m_shouldReloadTexture(true)
{
}


TextRenderer::~TextRenderer()
{
	freeFontTexture();
}


void TextRenderer::render()
{
	if (m_shouldReloadTexture)
	{
		rebuildTexture();
		m_shouldReloadTexture = false;
	}
	renderMain(&m_clipRect);
}


bool TextRenderer::loadFont(const Font& font)
{
	// Get rid of previous font texture
	if (m_texture == nullptr)
	{
		getBlankTexture();
	}
	freeFontTexture();

	// Load image at specified path as surface
	SDL_Surface* loadedSurface = IMG_Load(font.path.c_str());
	if (loadedSurface == nullptr)
	{
		OutputLog("ERROR: Unable to load font image at path %s! SDL_image Error: %s", font.path.c_str(), IMG_GetError());
	}
	else
	{
		if (!validateFont(font, loadedSurface->w, loadedSurface->h))
		{
			SDL_FreeSurface(loadedSurface);
			OutputLog("ERROR: The Font provided is not valid!");
			return false;
		}
		m_font = font;
		// Create texture from surface
		m_fontTexture = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);
		if (m_fontTexture == nullptr)
		{
			OutputLog("ERROR: Unable to create font texture for font image at path %s! SDL Error: %s", font.path.c_str(), SDL_GetError());
		}
		// Free the loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return m_fontTexture != nullptr;
}


int TextRenderer::getCharacterSpacing() const
{
	return m_characterSpacing;
}


void TextRenderer::setCharacterSpacing(int charSpacing)
{
	if (charSpacing < 0)
	{
		OutputLog("WARNING: The requested character spacing (%i) is a negative number. The character spacing will be set to zero.", charSpacing);
		m_characterSpacing = 0;
	}
	else
	{
		m_characterSpacing = charSpacing;
	}
}


int TextRenderer::getLineSpacing() const
{
	return m_lineSpacing;
}


void TextRenderer::setLineSpacing(int lineSpacing)
{
	if (lineSpacing < 0)
	{
		OutputLog("WARNING: The requested line spacing (%i) is a negative number. The line spacing will be set to zero.", lineSpacing);
		m_lineSpacing = 0;
	}
	else
	{
		m_lineSpacing = lineSpacing;
	}
}


std::string TextRenderer::getText() const
{
	return m_text;
}


void TextRenderer::setText(const std::string& text)
{
	if (m_text != text)
	{
		m_text = text;
		m_shouldReloadTexture = true;
	}
}


bool TextRenderer::rebuildTexture()
{
	if (m_fontTexture == nullptr)
	{
		OutputLog("ERROR: No font texture has been loaded for a TextRenderer with text '%s'!", m_text.c_str());
		return false;
	}

	if (m_texture == nullptr && !getBlankTexture())
	{
		return false;
	}

	// Change the renderer's render target to the text texture (keeping a reference to the original target)
	SDL_Texture* originalTarget = SDL_GetRenderTarget(m_renderer);
	SDL_SetRenderTarget(m_renderer, m_texture);

	// Set Render Color to black transparent and clear the texture
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
	SDL_RenderClear(m_renderer);

	// Reset the clip width and height to zero
	m_clipRect.w = 0;
	m_clipRect.h = 0;

	// For an empty text, nothing further needs to be done
	if (m_text.length() > 0)
	{
		// Current draw position
		int x = 0;
		int y = 0;

		int lineWidth = 0;

		// Account for the first line
		m_clipRect.h += m_font.characterHeight;

		// Now we loop through the whole string
		for (char c : m_text)
		{
			// New line case
			if (c == '\n')
			{
				m_clipRect.h += m_font.characterHeight;
				if (lineWidth > m_clipRect.w)
				{
					m_clipRect.w = lineWidth;
				}
				lineWidth = 0;
				x = 0;
				y += m_font.characterHeight;
			}
			// Space case
			else if (c == ' ')
			{
				lineWidth += m_font.characterWidth;
				x += m_font.characterWidth;
			}
			// Other characters
			else {
				// If a character is not found in the font info, we leave a space and log a message
				if (m_font.charsTopLeftCorners.count(c) == 0)
				{
					lineWidth += m_font.characterWidth;
					x += m_font.characterWidth;
					OutputLog("WARNING: Character %c could not be found in the font information!", c);
				}
				// But if the character is available, draw it to m_texture
				else
				{
					PixelPosition& tlCorner = m_font.charsTopLeftCorners[c];
					SDL_Rect sourceRect{
						tlCorner.x,
						tlCorner.y,
						m_font.characterWidth,
						m_font.characterHeight
					};
					SDL_Rect destinationRect{
						x,
						y,
						m_font.characterWidth,
						m_font.characterHeight
					};

					SDL_RenderCopy(m_renderer, m_fontTexture, &sourceRect, &destinationRect);
					
					// Account for the bigger image
					lineWidth += m_font.characterWidth;
					x += m_font.characterWidth;
				}
			}
		}
		
		if (lineWidth > m_clipRect.w)
		{
			m_clipRect.w = lineWidth;
		}
	}

	// Change the renderer's render target back to the original target
	SDL_SetRenderTarget(m_renderer, originalTarget);

	return m_texture != nullptr;
}


bool TextRenderer::getBlankTexture()
{
	// Just in case something goes wrong, we ensure there is no previous texture stored in m_texture
	free();

	//Create uninitialized texture
	m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (m_texture == nullptr)
	{
		OutputLog("ERROR: Unable to create blank texture! SDL Error: %s", SDL_GetError());
	}
	else
	{
		// Enable alpha blending
		SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_BLEND);
		// Reset internal dimensions
		m_width = SCREEN_WIDTH;
		m_height = SCREEN_HEIGHT;
	}

	return m_texture != nullptr;
}


void TextRenderer::freeFontTexture()
{
	if (m_fontTexture != nullptr)
	{
		SDL_DestroyTexture(m_fontTexture);
		m_fontTexture = nullptr;
	}
}

bool TextRenderer::validateFont(const Font& font, int width, int height) const
{
	if (font.path.length() == 0 || font.characterWidth <= 0 || font.characterHeight <= 0)
	{
		return false;
	}

	for (auto it : font.charsTopLeftCorners)
	{
		PixelPosition& tlCorner = it.second;
		if (tlCorner.x < 0 || tlCorner.y < 0 || tlCorner.x + font.characterWidth > width || tlCorner.y + font.characterHeight > height)
		{
			OutputLog("ERROR: Font information for character %c falls outside of the loaded texture (path: %s)", it.first, font.path.c_str());
			return false;
		}
	}
	return true;
}
