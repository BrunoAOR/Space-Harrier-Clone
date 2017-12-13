#include "SpriteSheet.h"

#include "globals.h"
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


bool SpriteSheet::selectAnimation(const std::string& animationName, int startingFrame)
{
	if (m_animations.count(animationName) == 1)
	{
		m_currentAnimation = &m_animations[animationName];
		if (startingFrame >= 0 && startingFrame < (int)m_currentAnimation->size())
		{
			m_currentClipRectIndex = startingFrame;
		}
		else
		{
			OutputLog("WARNING: Parameter startingFrame in the selectAnimation method has an invalid value of %i which falls outside of the range of the selected animation (%i frames)!", startingFrame, m_currentAnimation->size());
			m_currentClipRectIndex = 0;
		}
		m_currentClipRect = &(m_currentAnimation->at(m_currentClipRectIndex));
		m_isPlaying = false;
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


bool SpriteSheet::selectFrame(int frameIndex)
{
	if (m_currentAnimation != nullptr)
	{
		int size = m_currentAnimation->size();
		if (size == 0)
		{
			resetCachedFields();
			return false;
		}
		// Return false if frameIndex is out of bounds
		if (frameIndex >= 0 && frameIndex < size)
		{
			m_currentClipRectIndex = frameIndex;
			m_currentClipRect = &(m_currentAnimation->at(m_currentClipRectIndex));
			return true;
		}
		return false;
	}
	return false;
}


int SpriteSheet::getAnimationFrameCount(const std::string & animationName) const
{
	if (m_animations.count(animationName) == 1)
	{
		m_animations.at(animationName).size();
	}
	return -1;
}


int SpriteSheet::getCurrentAnimationFrameCount() const
{
	if (m_currentAnimation == nullptr)
	{
		return -1;
	}
	return m_currentAnimation->size();
}


int SpriteSheet::getCurrentAnimationFrameIndex() const
{
	return m_currentClipRectIndex;
}


bool SpriteSheet::playAnimation(const std::string& animationName, int startingFrame)
{
	stopAnimation();
	if (selectAnimation(animationName, startingFrame)) {
		m_elapsedTime = 0;
		m_isPlaying = true;
		return true;
	}

	return false;
}


bool SpriteSheet::playAnimation(const std::string& animationName, float fps, int startingFrame)
{
	stopAnimation();
	if (selectAnimation(animationName, startingFrame) && fps != 0) {
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
