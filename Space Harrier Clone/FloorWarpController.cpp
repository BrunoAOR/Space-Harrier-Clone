#include "FloorWarpController.h"

#include <assert.h>
#include "Engine/API.h"
#include "Engine/GameObject.h"
#include "Engine/Sprite.h"
#include "FloorManager.h"


FloorWarpController::FloorWarpController()
{
}


FloorWarpController::~FloorWarpController()
{
}

#include "Engine/Transform.h"
void FloorWarpController::init(FloorManager* floorManager, const std::string& texturePath, int floorLinesCount, float horScrollSpeed, int horScrollWrapLimit)
{
	m_floorManager = floorManager;
	m_floorLinesCount = floorLinesCount;
	m_horizontalScrollSpeed = horScrollSpeed;
	m_scrollLimit = horScrollWrapLimit;
	assert(m_floorManager && !texturePath.empty() && m_floorLinesCount > 0 && m_scrollLimit > 0);

	m_spriteLines.reserve(floorLinesCount);
	OutputLog("floor position %f, %f", m_floorManager->gameObject()->transform->getWorldPosition().x, m_floorManager->gameObject()->transform->getWorldPosition().y);
	for (int i = 0; i < floorLinesCount; ++i)
	{
		auto sprite = m_floorManager->gameObject()->addComponent<Sprite>();

		if (sprite)
		{
			sprite->loadImage(texturePath);
			sprite->setRenderLayer("Background");
			sprite->setZIndex(2);
			float y = (float)(sprite->getHeight()) / floorLinesCount;
			sprite->setAllPivots(Vector2(0.5f, 0));
			sprite->setPositionPivot(Vector2(0.5f, -(float)(floorLinesCount - (i + 1))));
			sprite->setClipRect(SDL_Rect{ m_scrollLimit,(int)(y * i), sprite->getWidth() - 2 * m_scrollLimit, (int)y });
			m_spriteLines.push_back(sprite);
		}
	}

	if (m_spriteLines.size() > 0)
	{
		m_pixelWidth = m_spriteLines[0]->getWidth();
	}
}


void FloorWarpController::scrollFloorHorizontal(float normalizedSpeed)
{
	float distance = m_horizontalScrollSpeed * normalizedSpeed * Time::deltaTime() * 0.001f;

	m_currentpixelOffset += distance;
	if (m_currentpixelOffset >= m_scrollLimit)
	{
		m_currentpixelOffset -= m_scrollLimit;
	}
	else if (m_currentpixelOffset <= -m_scrollLimit)
	{
		m_currentpixelOffset += m_scrollLimit;
	}

	int floorLinesCount = m_spriteLines.size();
	int index = 0;
	for (auto& sprite : m_spriteLines)
	{
		if (sprite)
		{
			SDL_Rect currentClipRect = sprite->getClipRect();
			currentClipRect.x = m_scrollLimit - (int)(m_currentpixelOffset * index / floorLinesCount);
			sprite->setClipRect(currentClipRect);
		}
		++index;
	}
}


void FloorWarpController::scaleFloorVertical(int targetFloorHeight)
{
	float lineHeight = (float)targetFloorHeight / m_floorLinesCount;
	float currentPixelOver = 0;
	int currentLinesHeightSum = 0;

	for (int i = m_floorLinesCount - 1; i >= 0; --i)
	{
		if (auto& sprite = m_spriteLines[i])
		{
			int finalLineHeight = (int)ceilf(lineHeight + currentPixelOver);
			currentPixelOver += lineHeight - finalLineHeight;

			SDL_Rect currentClipRect = sprite->getClipRect();
			currentClipRect.h = finalLineHeight;
			sprite->setClipRect(currentClipRect);

			if (finalLineHeight > 0)
			{
				Vector2 currentPivotPos = sprite->getPositionPivot();
				currentPivotPos.y = -(float)currentLinesHeightSum / finalLineHeight;
				sprite->setPositionPivot(currentPivotPos);
				currentLinesHeightSum += finalLineHeight;
			}

		}
	}
}
