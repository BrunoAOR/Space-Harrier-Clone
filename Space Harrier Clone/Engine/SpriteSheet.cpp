#include "SpriteSheet.h"

#include "Engine.h"
#include "TimeController.h"


SpriteSheet::SpriteSheet()
	: m_currentClipRectIndex(-1)
	, m_isPlaying(false)
	, m_elapsedTime(0)
	, m_timeLimit(200)
	, m_direction(0)
{
}


SpriteSheet::~SpriteSheet()
{
}


void SpriteSheet::render()
{
	// Only render if an clipRect (and therefore an animation) is selected
	if (m_currentClipRect != nullptr)
	{
		// Check if automatic animation playback is active
		if (m_isPlaying && m_timeLimit != 0)
		{
			m_elapsedTime += engine->time->deltaTime();
			if (m_elapsedTime >= m_timeLimit)
			{
				m_elapsedTime -= m_timeLimit;
				if (m_direction > 0)
				{
					nextAnimationFrame();
				}
				else
				{
					previousAnimationFrame();
				}
			}
		}

		renderMain(m_currentClipRect);
	}
}


bool SpriteSheet::addAnimation(const std::string& animationName)
{
	if (m_animations.count(animationName) == 0)
	{
		// This will create a new entry for animationName and the value will be a default-constructed std::vector<SDL_Rect>
		m_animations[animationName];
		return true;
	}
	return false;
}


bool SpriteSheet::addRectForAnimation(const std::string& animationName, const Vector2& topLeftCorner, int width, int height)
{
	if (m_animations.count(animationName) == 1)
	{
		SDL_Rect rect{(int)topLeftCorner.x, (int)topLeftCorner.y, width, height};
		m_animations[animationName].push_back(rect);
		return true;
	}
	return false;
}


bool SpriteSheet::clearAllRectsInAnimation(const std::string& animationName)
{
	if (m_animations.count(animationName) == 1)
	{
		m_animations[animationName].clear();
		return true;
	}
	return false;
}


bool SpriteSheet::removeAnimation(const std::string& animationName)
{
	if (m_animations.count(animationName) == 1)
	{
		if (m_currentAnimation == &(m_animations[animationName]))
		{
			resetCachedFields();
		}
		m_animations.erase(animationName);
		return true;
	}
	return false;
}


void SpriteSheet::clearAllAnimations()
{
	m_animations.clear();
	resetCachedFields();
}


bool SpriteSheet::selectAnimation(const std::string& animationName)
{
	if (m_animations.count(animationName) == 1)
	{
		m_currentAnimation = &m_animations[animationName];
		m_currentClipRectIndex = 0;
		m_currentClipRect = &(m_currentAnimation->at(m_currentClipRectIndex));
		return true;
	}
	return false;
}


bool SpriteSheet::previousAnimationFrame()
{
	if (m_currentAnimation != nullptr)
	{
		int size = m_currentAnimation->size();
		if (size == 0)
		{
			resetCachedFields();
			return false;
		}
		// Loop around if the previous index is less than zero
		if (--m_currentClipRectIndex < 0)
		{
			m_currentClipRectIndex = size - 1;
		}
		m_currentClipRect = &(m_currentAnimation->at(m_currentClipRectIndex));
		return true;
	}
	return false;
}


bool SpriteSheet::nextAnimationFrame()
{
	if (m_currentAnimation != nullptr)
	{
		int size = m_currentAnimation->size();
		if (size == 0)
		{
			resetCachedFields();
			return false;
		}
		// Loop around if the next index exceeds the frame count
		if (++m_currentClipRectIndex >= size)
		{
			m_currentClipRectIndex = 0;
		}
		m_currentClipRect = &(m_currentAnimation->at(m_currentClipRectIndex));
		return true;
	}
	return false;
}


bool SpriteSheet::playAnimation(const std::string& animationName)
{
	stopAnimation();
	if (selectAnimation(animationName)) {
		m_elapsedTime = 0;
		m_isPlaying = true;
		return true;
	}

	return false;
}


bool SpriteSheet::playAnimation(const std::string& animationName, float fps)
{
	stopAnimation();
	if (selectAnimation(animationName) && fps != 0) {
		setAnimationSpeed(fps);
		m_elapsedTime = 0;
		m_isPlaying = true;
		return true;
	}
	
	return false;
}


void SpriteSheet::setAnimationSpeed(float fps)
{
	if (fps == 0)
	{
		m_timeLimit = 0;
		m_direction = 0;
	}
	else if (fps > 0)
	{
		m_timeLimit = (int)(1000 / fps);
		m_direction = 1;
	}
	else // if (fps < 0)
	{
		m_timeLimit = (int)(-1000 / fps);
		m_direction = -1;
	}
}


bool SpriteSheet::stopAnimation()
{
	if (m_isPlaying)
	{
		m_isPlaying = false;
		m_elapsedTime = 0;
		m_direction = 0;
		return true;
	}
	return false;
}


void SpriteSheet::resetCachedFields()
{
	m_currentAnimation = nullptr;
	m_currentClipRect = nullptr;
	m_currentClipRectIndex = -1;
}
