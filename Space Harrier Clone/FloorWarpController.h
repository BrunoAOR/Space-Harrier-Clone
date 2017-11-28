#ifndef H_FLOOR_WARP_CONTROLLER
#define H_FLOOR_WARP_CONTROLLER

#include <string>
#include <vector>
#include "Engine/Reference.h"
#include "Engine/Sprite.h"
class FloorManager;


class FloorWarpController
{
public:
	FloorWarpController();
	~FloorWarpController();

	void init(FloorManager* floorManager, const std::string& texturePath, int floorLinesCount, float horScrollSpeed, int horScrollWrapLimit);
	void scrollFloorHorizontal(float normalizedSpeed);
	void scaleFloorVertical(int targetFloorHeight);

private:
	std::vector<Reference<Sprite>> m_spriteLines;
	FloorManager* m_floorManager = nullptr;

	// Start state
	int m_pixelWidth = 0;
	int m_floorLinesCount = 0;


	// Horizontal scrolling
	float m_horizontalScrollSpeed = 0;
	int m_scrollLimit = 0;
	float m_currentpixelOffset = 0;

	// Vertical scaling
	float m_currentPixelHeight = 0;
};


#endif // !H_FLOOR_WARP_CONTROLLER
