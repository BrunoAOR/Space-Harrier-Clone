#include "Sprite.h"


Sprite::Sprite()
{
}


Sprite::~Sprite()
{
}


void Sprite::render()
{
	if (m_hasClipRect)
	{
		renderMain(&m_clipRect);
	}
	else
	{
		renderMain();
	}
	
}


SDL_Rect Sprite::getClipRect() const
{
	return m_clipRect;
}


void Sprite::setClipRect(const SDL_Rect& rect)
{
	m_clipRect = rect;
	m_hasClipRect = true;
}


void Sprite::resetClipRect()
{
	m_hasClipRect = false;
}
