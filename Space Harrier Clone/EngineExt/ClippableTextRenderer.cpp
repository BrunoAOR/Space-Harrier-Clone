#include "ClippableTextRenderer.h"

#include "../Engine/gameConfig.h"
#include "../Engine/GameObject.h"
#include "../Engine/Transform.h"
#include "../Engine/Vector2.h"


void ClippableTextRenderer::render()
{
	if (m_shouldReloadTexture)
	{
		rebuildTexture();
		m_shouldReloadTexture = false;
	}
	customRender();
}


void ClippableTextRenderer::setRenderRange(int xLeftWorld, int xRightWorld, int YBottomWorld, int yTopWorld)
{
	m_xLeft = xLeftWorld * SCREEN_SIZE;
	m_xRight = xRightWorld * SCREEN_SIZE;
	m_yBottom = YBottomWorld * SCREEN_SIZE;
	m_yTop = yTopWorld * SCREEN_SIZE;
	customRender();
}

void ClippableTextRenderer::customRender()
{
	if (m_renderer == nullptr || m_texture == nullptr)
	{
		return;
	}

	SDL_Rect currentClipRect = m_clipRect;

	// Extract info from the transform
	Vector2 pos = gameObject()->transform->getWorldPosition();
	float rot = gameObject()->transform->getWorldRotation();
	Vector2 sca = gameObject()->transform->getWorldScale();
	Vector2 positionPivot = getPositionPivot();
	Vector2 scalePivot = getScalePivot();

	// Correct the position and rotations to simulate a reference system with 0 in the bottom-left,
	// x increasing to the right (same as SDL) and Y increasing up (opposite of SDL)
	pos.y = SCREEN_HEIGHT - pos.y;
	rot *= -1;

	// Calculate the raw size, clipped if required
	Vector2 rawSize = { (float)currentClipRect.w, (float)currentClipRect.h };

	// Set the rendering space based on the position and positionPivot
	float renderQuadX = pos.x - positionPivot.x * rawSize.x;
	float renderQuadY = pos.y - (1 - positionPivot.y) * rawSize.y;
	float renderQuadW = rawSize.x;
	float renderQuadH = rawSize.y;

	// Modify for the gameObject scale and scalePivot
	SDL_Rect renderQuad =
	{
		(int)round(SCREEN_SIZE * (renderQuadX - scalePivot.x * (sca.x - 1) * rawSize.x)),
		(int)round(SCREEN_SIZE * (renderQuadY - (1 - scalePivot.y) * (sca.y - 1) * rawSize.y)),
		(int)round(SCREEN_SIZE * (renderQuadW * sca.x)),
		(int)round(SCREEN_SIZE * (renderQuadH * sca.y))
	};
	// Calculate the center of rotation based on the rotationPivot
	Vector2 scaledSize = { rawSize.x * sca.x , rawSize.y * sca.y };


	// Now comes the custom clipping

	// General check
	if (renderQuad.x + renderQuad.w <= m_xLeft || renderQuad.x >= m_xRight || renderQuad.y + renderQuad.h <= m_yTop || renderQuad.y > +m_yBottom)
	{
		// No rendering needed, because the renderQuad falls out of the render range
		return;
	}

	int diff = 0;

	// Check minX
	if (renderQuad.x < m_xLeft)
	{
		diff = m_xLeft - renderQuad.x;
		currentClipRect.x += diff;
		currentClipRect.w -= diff;
		renderQuad.x += diff;
		renderQuad.w -= diff;
	}
	// Check maxX
	if (renderQuad.x + renderQuad.w > m_xRight)
	{
		diff = (renderQuad.x + renderQuad.w) - m_xRight;
		currentClipRect.w -= diff;
		renderQuad.w -= diff;
	}
	// Check minY
	if (renderQuad.y < m_yTop)
	{
		diff = m_yTop - renderQuad.y;
		currentClipRect.y += diff;
		currentClipRect.h -= diff;
		renderQuad.y += diff;
		renderQuad.h -= diff;
	}
	// Check maxY
	if (renderQuad.y + renderQuad.h > m_yBottom)
	{
		diff = (renderQuad.y + renderQuad.h) - m_yBottom;
		currentClipRect.h -= diff;
		renderQuad.h -= diff;
	}

	SDL_RenderCopy(m_renderer, m_texture, &currentClipRect, &renderQuad);

}
