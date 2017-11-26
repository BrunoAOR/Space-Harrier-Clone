#include "RectangleRenderer.h"

#include "../Engine/gameConfig.h"


RectangleRenderer::RectangleRenderer()
{
}


RectangleRenderer::~RectangleRenderer()
{
}


void RectangleRenderer::render()
{
	SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
	SDL_Color oldColor;
	SDL_Rect drawRect;
	Vector2 posPivot = getPositionPivot();
	drawRect.x = (rect.x - posPivot.x * rect.w) * SCREEN_SIZE;
	drawRect.y = (SCREEN_HEIGHT - (rect.y - posPivot.y * rect.h) - rect.h) * SCREEN_SIZE;
	drawRect.w = rect.w * SCREEN_SIZE;
	drawRect.h = rect.h * SCREEN_SIZE;

	SDL_GetRenderDrawColor(m_renderer, &oldColor.r, &oldColor.g, &oldColor.b, &oldColor.a);
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(m_renderer, &drawRect);
	SDL_SetRenderDrawColor(m_renderer, oldColor.r, oldColor.g, oldColor.b, oldColor.a);
}
