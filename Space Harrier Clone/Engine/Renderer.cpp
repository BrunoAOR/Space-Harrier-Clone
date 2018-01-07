#include "Renderer.h"

#include "gameConfig.h"
#include "RenderersManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "ComponentType.h"
#include "ResourcesManager.h"


Renderer::Renderer()
	: m_positionPivot(Vector2(0.5f, 0.5f))
	, m_rotationPivot(Vector2(0.5f, 0.5f))
	, m_scalePivot(Vector2(0.5f, 0.5f))
	, m_renderLayer("default")
	, m_zIndex(0)
{
	m_type = ComponentType::RENDERER;
}


Renderer::~Renderer()
{
	// Deallocate texture
	free();
}


int Renderer::getWidth() const
{
	return m_width;
}


int Renderer::getHeight() const
{
	return m_height;
}


// PIVOTS


Vector2 Renderer::getPositionPivot() const
{
	return m_positionPivot;
}


void Renderer::setPositionPivot(const Vector2& positionPivot)
{
	m_positionPivot = positionPivot;
}


Vector2 Renderer::getRotationPivot() const
{
	return m_rotationPivot;
}


void Renderer::setRotationPivot(const Vector2& rotationPivot)
{
	m_rotationPivot = rotationPivot;
}


Vector2 Renderer::getScalePivot() const
{
	return m_scalePivot;
}


void Renderer::setScalePivot(const Vector2& scalePivot)
{
	m_scalePivot = scalePivot;
}


void Renderer::setAllPivots(const Vector2& pivot)
{
	setPositionPivot(pivot);
	setRotationPivot(pivot);
	setScalePivot(pivot);
}


const std::string& Renderer::getRenderLayer() const
{
	return m_renderLayer;
}


bool Renderer::setRenderLayer(const std::string & drawLayer)
{
	if (m_renderersManager->changeRendererLayer(this, m_renderLayer, drawLayer))
	{
		m_renderLayer = drawLayer;
		return true;
	}
	return false;
}


int Renderer::getZIndex() const
{
	return m_zIndex;
}


void Renderer::setZIndex(int zIndex)
{
	m_renderersManager->markLayerAsDirty(m_renderLayer);
	m_zIndex = zIndex;
}


void Renderer::renderMain(SDL_Rect* clip, SDL_RendererFlip flip) const
{
	if (m_renderer == nullptr || m_texture == nullptr)
	{
		return;
	}

	if (!gameObject()->transform)
	{
		return;
	}

	// Extract info from the transform
	Vector2 pos = gameObject()->transform->getWorldPosition();
	float rot = gameObject()->transform->getWorldRotation();
	Vector2 sca = gameObject()->transform->getWorldScale();

	// Correct the position and rotations to simulate a reference system with 0 in the bottom-left,
	// x increasing to the right (same as SDL) and Y increasing up (opposite of SDL)
	pos.y = SCREEN_HEIGHT - pos.y;
	rot *= -1;

	// Calculate the raw size, clipped if required
	Vector2 rawSize;
	if (clip)
	{
		rawSize = { (float)clip->w, (float)clip->h };
	}
	else
	{
		rawSize = { (float)m_width, (float)m_height };
	}

	// Set the rendering space based on the position and positionPivot
	float renderQuadX = pos.x - m_positionPivot.x * rawSize.x;
	float renderQuadY = pos.y - (1 - m_positionPivot.y) * rawSize.y;
	float renderQuadW = rawSize.x;
	float renderQuadH = rawSize.y;

	// Modify for the gameObject scale and scalePivot
	SDL_Rect renderQuad =
	{
		(int)round(SCREEN_SIZE * (renderQuadX - m_scalePivot.x * (sca.x - 1) * rawSize.x)),
		(int)round(SCREEN_SIZE * (renderQuadY - (1 - m_scalePivot.y) * (sca.y - 1) * rawSize.y)),
		(int)round(SCREEN_SIZE * (renderQuadW * sca.x)),
		(int)round(SCREEN_SIZE * (renderQuadH * sca.y))
	};
	// Calculate the center of rotation based on the rotationPivot
	Vector2 scaledSize = { rawSize.x * sca.x , rawSize.y * sca.y };
	SDL_Point center =
	{
		(int)round(SCREEN_SIZE * (m_rotationPivot.x * scaledSize.x)),
		(int)round(SCREEN_SIZE * ((1 - m_rotationPivot.y) * scaledSize.y))
	};

	// Correct issue with texture not being rendered if the renderQuad has negative width or height and there is no rotation
	// Solution: add a tiny rotation
	if (rot == 0 && (sca.x < 0 || sca.y<0))
	{
		rot = FLT_EPSILON;
	}

	SDL_RenderCopyEx(m_renderer, m_texture, clip, &renderQuad, rot, &center, flip);
}


void Renderer::free()
{
	// Free texture if it exists
	if (m_texture != nullptr)
	{
		if (m_isTextureUnique)
		{
			SDL_DestroyTexture(m_texture);
		}
		else
		{
			m_texturesManager->returnResource(m_texture);
		}
		m_texture = nullptr;
		m_width = 0;
		m_height = 0;
	}
}
