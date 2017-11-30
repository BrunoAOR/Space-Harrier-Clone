#include "DarkLinesController.h"

#include <assert.h>
#include "Engine/gameConfig.h"
#include "Engine/GameObject.h"
#include "Engine/API.h"
#include "FloorManager.h"
#include "DarkLineInfo.h"


DarkLinesController::DarkLinesController()
{
}


DarkLinesController::~DarkLinesController()
{
}


void DarkLinesController::init(FloorManager* floorManager, int darkLinesCount, float cycleDuration)
{
	floorManager = floorManager;
	m_darkLinesCount = darkLinesCount;
	m_cycleDuration = cycleDuration;
	assert(floorManager && m_darkLinesCount > 0 &&  m_cycleDuration > 0);

	m_rectangleRenderers.reserve(m_darkLinesCount);
	
	// A linear function will be used to calculate starting/endings positions and heights of each dark line initially assuming a height of 1 (100%)
	float slope = 3.0f / (darkLinesCount * darkLinesCount * darkLinesCount);
	//float slope = 2.0f / (linesCount * linesCount);
	float startY = 1;
	float usedSpace = 0;

	for (int i = 0; i < m_darkLinesCount; ++i)
	{
		auto rectangleRenderer = floorManager->gameObject()->addComponent<RectangleRenderer>();
		if (rectangleRenderer)
		{
			rectangleRenderer->setRenderLayer("Background");
			rectangleRenderer->setZIndex(2);
			rectangleRenderer->setAllPivots(Vector2{ 0, 1 });
			// Dark line color calculated assuming that SDL_BLENDMODE_BLEND will be used.
			rectangleRenderer->color = SDL_Color{ 140, 220, 140, 171 };
			rectangleRenderer->rect = SDL_Rect{ 0, 0, SCREEN_WIDTH, 0 };

			m_rectangleRenderers.push_back(rectangleRenderer);

			DarkLineInfo info;
			info.startHeight = slope * i * i / 2;
			info.endHeight = slope * (i + 1) * (i + 1) / 2;
			info.startY =  startY - usedSpace;
			usedSpace += slope * (i + 1) * (i + 1);
			info.endY = startY - usedSpace;
			m_darkLineInfos.push_back(info);
		}
	}
}


void DarkLinesController::scrollDarkLinesVertical(int targetFloorHeight)
{
	m_currentCycleTime += Time::deltaTime();
	if (m_currentCycleTime >= m_cycleDuration)
	{
		m_currentCycleTime -= m_cycleDuration;
	}

	for (int i = 0; i < m_darkLinesCount; ++i)
	{
		DarkLineInfo& info = m_darkLineInfos[i];
		Reference<RectangleRenderer>& rectRenderer = m_rectangleRenderers[i];
		// u is the proportional advance in the timeCycle
		float u = m_currentCycleTime / m_cycleDuration;
		// Interpolate within the DarkLine's limits to obtain its current position and height and round down to int
		float yPos = targetFloorHeight * ((1 - u) * info.startY + u * info.endY);
		float height = targetFloorHeight * ((1 - u) * info.startHeight + u * info.endHeight);
		// Modify the rect according to calculations
		rectRenderer->rect.y = (int)(yPos + 1 -FLT_EPSILON);
		rectRenderer->rect.h = (int)(height + 1 - FLT_EPSILON);
	}
}


float DarkLinesController::getNormalizedYPos(float normalizedMotionProgress) const
{
	float result = -1;
	int darkLineIndex = (int)(normalizedMotionProgress * m_darkLinesCount);
	if (darkLineIndex >= 0 && darkLineIndex < m_darkLinesCount)
	{
		const DarkLineInfo& info = m_darkLineInfos[darkLineIndex];
		// FLT_EPSILON is deducted from a normalized cycle duration (1/ m_darkLinesCount) to correct a precision error
		float cycleMotionProgress = fmodf(normalizedMotionProgress, (1.0f / m_darkLinesCount) - FLT_EPSILON) * m_darkLinesCount;
		result = ((1 - cycleMotionProgress) * info.startY + cycleMotionProgress * info.endY);
	}
	return result;
}