#include "FloorManager.h"

#include <math.h>
#include "Engine/gameConfig.h"
#include "Engine/API.h"
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Engine/Sprite.h"


void FloorManager::init(const std::string & texturePath)
{
	m_texturePath = texturePath;
}


void FloorManager::start()
{
	assert(!m_texturePath.empty());
	m_horInterpolationDuration = 500;
	m_vertInterpolationDuration = 500;
	m_pixelScaleSpeed = 64;
	m_darkLinesFullCycleDuration = 2000;	// Refers to the time required for a full cycle of dark lines scrolling
	// Following 3 values (in pixels) obtained by comparing with the Arcade (MAME) version of the origial game
	m_maxHeight = 159;	
	m_midHeight = 70;
	m_minHeight = 26;

	m_targetHeight = m_midHeight;

	m_horScrollSpeed = SCREEN_WIDTH / 0.6f; // Horizontal speed of the bottom-most line meassured in pixels per second
	int horScrollWrapLimit = 65;	// Pixels after which each rect returns to its original position
	int floorLinesCount = 128;		// The number of rects into which the floor is split for the warping effect
	
	floorWarpController.init(this, m_texturePath, floorLinesCount, m_horScrollSpeed, horScrollWrapLimit);

	int darkLinesCount = 10;	// Amount of dark lines on the screen
	float cycleDuration = m_darkLinesFullCycleDuration / 10.0f;	// Where a cycle is the time for one dark line to get to the size and position of the next one (in milliseconds)
	darkLinesController.init(this, darkLinesCount, cycleDuration);

	m_currentPixelHeight = (float)m_minHeight;
	floorWarpController.scaleFloorVertical((int)m_currentPixelHeight);
	darkLinesController.scrollDarkLinesVertical((int)m_currentPixelHeight);
}


void FloorManager::update()
{
	float horRequestedNormalizedSpeed = 0;
	m_targetHeight = m_midHeight;
	if (freezeAtBottom)
	{
		m_horSpeedCurrentValue = 0;
		m_horSpeedCurrentValue = 0;
		m_targetHeight = m_minHeight;
	}
	else
	{
		// Manage input
		if (Input::getKey(SDL_SCANCODE_LEFT))
		{
			// Rightwards
			horRequestedNormalizedSpeed = 1;
		}
		if (Input::getKey(SDL_SCANCODE_RIGHT))
		{
			// Leftwards
			horRequestedNormalizedSpeed = -1;
		}

		if (Input::getKey(SDL_SCANCODE_UP))
		{
			// Scale up
			m_targetHeight = m_maxHeight;
		}
		if (Input::getKey(SDL_SCANCODE_DOWN))
		{
			// Scale down
			m_targetHeight = m_minHeight;
		}
	}

	// Interpolate horizontal values if required
	if (horRequestedNormalizedSpeed != m_horSpeedTargetValue)
	{
		m_horSpeedStartingValue = m_horSpeedCurrentValue;
		m_horSpeedTargetValue = horRequestedNormalizedSpeed;
		m_horInterpolationElapsedTime = 0;
	}

	if (m_horSpeedCurrentValue != m_horSpeedTargetValue)
	{
		m_horInterpolationElapsedTime += Time::deltaTime();
		float horU = m_horInterpolationElapsedTime / (float)m_horInterpolationDuration;
		if (horU > 1) {
			horU = 1;
		}
		m_horSpeedCurrentValue = (1 - horU) * m_horSpeedStartingValue + horU * m_horSpeedTargetValue;
	}


	// Interpolate vertical values if required

	if (m_currentPixelHeight != (float)m_targetHeight)
	{
		float vertRequestedNormalizedSpeed = 0;
		if (m_currentPixelHeight > m_targetHeight)
		{
			vertRequestedNormalizedSpeed = -1;
		}
		else if (m_currentPixelHeight < m_targetHeight)
		{
			vertRequestedNormalizedSpeed = 1;
		}

		if (vertRequestedNormalizedSpeed != m_vertSpeedTargetValue)
		{
			m_vertSpeedStartingValue = m_vertSpeedCurrentValue;
			m_vertSpeedTargetValue = vertRequestedNormalizedSpeed;
			m_vertInterpolationElapsedTime = 0;
		}

		if (m_vertSpeedCurrentValue != m_vertSpeedTargetValue)
		{
			m_vertInterpolationElapsedTime += Time::deltaTime();
			float vertU = m_vertInterpolationElapsedTime / (float)m_vertInterpolationDuration;
			if (vertU > 1) {
				vertU = 1;
			}
			m_vertSpeedCurrentValue = (1 - vertU) * m_vertSpeedStartingValue + vertU * m_vertSpeedTargetValue;
		}
	}
	
	// Apply effects through the respective controllers
	int previousRoundedHeight = (int)m_currentPixelHeight;
	updateCurrentFloorHeight(m_vertSpeedCurrentValue);
	int roundedPixelHeigth = (int)m_currentPixelHeight;

	if (previousRoundedHeight != roundedPixelHeigth)
	{
		floorWarpController.scaleFloorVertical(roundedPixelHeigth);
	}

	floorWarpController.scrollFloorHorizontal(m_horSpeedCurrentValue);
	
	darkLinesController.scrollDarkLinesVertical(roundedPixelHeigth, freezeAtBottom);
}


int FloorManager::getCurrentFloorHeight() const
{
	return (int)m_currentPixelHeight;
}


float FloorManager::getCurrentHorizontalSpeed() const
{
	if (freezeAtBottom)
	{
		return 0;
	}
	return m_horSpeedCurrentValue * m_horScrollSpeed;

}


int FloorManager::getFullMotionDuration() const
{
	return m_darkLinesFullCycleDuration;
}


float FloorManager::getNormalizedYPos(float normalizedMotionProgress) const
{
	return darkLinesController.getNormalizedYPos(normalizedMotionProgress);
}


float FloorManager::getXCoordinateForYPos(float startingXPos, float normalizedStartingYPos, float normalizedCurrentYPos) const
{
	// Points have an absolute value for X but a normalized value for Y
	// vanishing point calculated through image inspection in image edition software
	Vector2 vanishingPoint(0, 1 + (float)8/256);
	Vector2 objectPoint(startingXPos, normalizedStartingYPos);

	// Calculate the line equation y = mx + b to later extract x through: x = (y - b)/m;
	float m = (vanishingPoint.y - objectPoint.y) / (vanishingPoint.x - objectPoint.x);
	float b = vanishingPoint.y - m * vanishingPoint.x;

	// Now calculate the required x for the input normalizedCurrentYPos;
	float x = (normalizedCurrentYPos - b) / m;

	return x;
}


float FloorManager::getXSpeedForYPos(float interpolatedCurrentYPos) const
{
	// The normalizedCurrentYPos goes from 1 to 0 (top to bottom), but for the speed calculations a value ranging from 0 to 1 is prefered
	float correctedYPos = 1 - interpolatedCurrentYPos;
	float xSpeed = correctedYPos * m_horSpeedCurrentValue * m_horScrollSpeed;
	return xSpeed;
}

void FloorManager::updateCurrentFloorHeight(float normalizedSpeed)
{
	float speed = m_pixelScaleSpeed * normalizedSpeed * Time::deltaTime() * 0.001f;

	m_currentPixelHeight += speed;

	if (m_vertSpeedTargetValue > 0 && m_currentPixelHeight > m_targetHeight || m_vertSpeedTargetValue < 0 && m_currentPixelHeight < m_targetHeight)
	{
		m_currentPixelHeight = (float)m_targetHeight;
		m_vertSpeedCurrentValue = 0;
	}
	return;
}
