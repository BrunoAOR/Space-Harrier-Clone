#ifndef H_DARK_LINES_CONTROLLER
#define H_DARK_LINES_CONTROLLER

#include <vector>
#include "Engine/Reference.h"
#include "EngineExt/RectangleRenderer.h"
class FloorManager;
struct DarkLineInfo;

class DarkLinesController
{
public:
	DarkLinesController();
	~DarkLinesController();

	void start(FloorManager* floorManager, int darkLinesCount, float cycleDuration);

	void scrollDarkLinesVertical(int targetFloorHeight);
	float getNormalizedYPos(float normalizedMotionProgress) const;

private:
	int m_darkLinesCount = 0;
	float m_cycleDuration = 0;
	float m_currentCycleTime = 0;
	
	std::vector<DarkLineInfo> m_darkLineInfos;
	std::vector<Reference<RectangleRenderer>> m_rectangleRenderers;
	int m_darkLinesCurrentPixelOffset = 0;
	FloorManager* floorManager = nullptr;
};


#endif // !H_DARK_LINES_CONTROLLER
