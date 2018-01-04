#ifndef H_FLOOR_MANAGER
#define H_FLOOR_MANAGER

#include "Engine/Behaviour.h"
#include <vector>
#include <string>
#include "Engine/Reference.h"
#include "Engine/Sprite.h"
#include "FloorWarpController.h"
#include "DarkLinesController.h"


class FloorManager :
	public Behaviour
{
public:
	void init(const std::string& texturePath);
	virtual void awake() override;
	virtual void update() override;
	
	int getCurrentFloorHeight() const;
	float getCurrentHorizontalSpeed() const;
	int getFullMotionDuration() const;
	float getNormalizedYPos(float normalizedMotionProgress) const;
	float getXCoordinateForYPos(float startingXPos, float normalizedStartingYPos, float normalizedCurrentYPos) const;
	float getXSpeedForYPos(float interpolatedCurrentYPos) const;

	bool freezeAtBottom;
	bool stopHorizontal;

private:
	void updateCurrentFloorHeight(float normalizedSpeed);

	FloorWarpController floorWarpController;
	DarkLinesController darkLinesController;

	std::string m_texturePath;
	float m_currentPixelHeight = 0;
	float m_pixelScaleSpeed = 0;
	int m_darkLinesFullCycleDuration = 0;
	float m_horScrollSpeed = 0;
	int m_maxHeight = 0;
	int m_midHeight = 0;
	int m_minHeight = 0;

	// Interpolation related
	int m_horInterpolationDuration = 0;
	float m_horInterpolationElapsedTime = 0;
	float m_horSpeedStartingValue = 0;
	float m_horSpeedCurrentValue = 0;
	float m_horSpeedTargetValue = 0;

	int m_targetHeight = 0;
	int m_vertInterpolationDuration = 0;
	float m_vertInterpolationElapsedTime = 0;
	float m_vertSpeedStartingValue = 0;
	float m_vertSpeedCurrentValue = 0;
	float m_vertSpeedTargetValue = 0;
};


#endif // !H_FLOOR_MANAGER
