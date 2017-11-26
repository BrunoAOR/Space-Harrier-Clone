#include "FloorManager.h"

#include <math.h>
#include "Engine/gameConfig.h"
#include "Engine/API.h"
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Engine/Sprite.h"

void FloorManager::start()
{
	m_horInterpolationTime = 0.5f;
	m_vertInterpolationTime = 0.5f;
	m_pixelScaleSpeed = 64;
	// Following 3 values (in pixels) obtained by comparing with the Arcade (MAME) version of the origial game
	m_maxHeight = 159;	
	m_midHeight = 70;
	m_minHeight = 26;
	m_targetHeight = m_midHeight;

	
	float horScrollSpeed = SCREEN_WIDTH / 0.6f; // Horizontal speed of the bottom-most line meassured in pixels per second
	int horScrollWrapLimit = 65;	// Pixels after which each rect returns to its original position
	int floorLinesCount = 128;		// The number of rects into which the floor is split for the warping effect
	
	floorWarpController.start(this, texturePath, floorLinesCount, horScrollSpeed, horScrollWrapLimit);

	int darkLinesCount = 10;	// Amount of dark lines on the screen
	float cycleDuration = 175;	// Where a cycle is the time for one dark line to get to the size and position of the next one (in milliseconds)
	darkLinesController.start(this, darkLinesCount, cycleDuration);

	m_currentPixelHeight = (float)m_minHeight;
	floorWarpController.scaleFloorVertical((int)m_currentPixelHeight);
	darkLinesController.scrollDarkLinesVertical((int)m_currentPixelHeight);
}

void FloorManager::update()
{
	// Manage input
	float horRequestedNormalizedSpeed = 0;
	m_targetHeight = m_midHeight;
	if (Input::getKey(SDL_SCANCODE_A))
	{
		// Rightwards
		horRequestedNormalizedSpeed = 1;
	}
	if (Input::getKey(SDL_SCANCODE_D))
	{
		// Leftwards
		horRequestedNormalizedSpeed = -1;
	}

	if (Input::getKey(SDL_SCANCODE_W))
	{
		// Scale up
		m_targetHeight = m_maxHeight;
	}
	if (Input::getKey(SDL_SCANCODE_S))
	{
		// Scale down
		m_targetHeight = m_minHeight;
	}

	// Interpolate horizontal values if required
	if (horRequestedNormalizedSpeed != m_horSpeedTargetValue)
	{
		m_horSpeedStartingValue = m_horSpeedCurrentValue;
		m_horSpeedTargetValue = horRequestedNormalizedSpeed;
		m_horInterpolationStartTime = Time::time() * 0.001f;
	}

	if (m_horSpeedCurrentValue != m_horSpeedTargetValue)
	{
		float horU = (Time::time() * 0.001f - m_horInterpolationStartTime) / m_horInterpolationTime;
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
			m_vertInterpolationStartTime = Time::time() * 0.001f;
		}

		if (m_vertSpeedCurrentValue != m_vertSpeedTargetValue)
		{
			float vertU = (Time::time() * 0.001f - m_vertInterpolationStartTime) / m_vertInterpolationTime;
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
	darkLinesController.scrollDarkLinesVertical(roundedPixelHeigth);
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
