#ifndef H_SPRITE_SHEET
#define H_SPRITE_SHEET

#include <unordered_map>
#include <vector>
#include <string>
#include "SpriteRenderer.h"


class SpriteSheet final :
	public SpriteRenderer
{
public:
	SpriteSheet();
	~SpriteSheet();

	// Inherited via Renderer
	virtual void render() override;

	// Adding and removing Animations and sub-sprites
	bool addAnimation(const std::string& animationName);
	bool addRectForAnimation(const std::string& animationName, const Vector2& topLeftCorner, int width, int height);

	bool clearAllRectsInAnimation(const std::string& animationName);
	bool removeAnimation(const std::string& animationName);
	void clearAllAnimations();

	// Manually select animations and their frames
	bool selectAnimation(const std::string& animationName, int startingFrame);
	bool previousAnimationFrame();
	bool nextAnimationFrame();
	bool selectFrame(int frameIndex);

	// Get animation info
	int getAnimationFrameCount(const std::string& animationName) const;
	std::string getCurrentAnimationName() const;
	int getCurrentAnimationFrameCount() const;
	int getCurrentAnimationFrameIndex() const;
	int getCurrentAnimationFrameHeight() const;
	int getCurrentAnimationFrameWidth() const;
	bool isPlaying();
	bool isFinished();


	// Play animations
	bool playAnimation(const std::string& animationName, bool loop = true, int startingFrame = 0);
	bool playAnimation(const std::string& animationName, float fps, bool loop = true, int startingFrame = 0);
	void setAnimationSpeed(float fps);
	bool stopAnimation();

private:
	void resetCachedFields();

	std::unordered_map<std::string, std::vector<SDL_Rect>> m_animations;
	std::vector<SDL_Rect>* m_currentAnimation = nullptr;
	std::string m_currentAnimationName = "";
	SDL_Rect* m_currentClipRect = nullptr;
	int m_currentClipRectIndex;

	// automatic animation playback
	bool m_isPlaying;
	bool m_isLooping;
	bool m_isFinished;
	int m_elapsedTime;
	int m_timeLimit;
	int m_direction;
};


#endif // !H_SPRITE_SHEET
