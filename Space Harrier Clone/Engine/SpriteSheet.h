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
	bool selectAnimation(const std::string& animationName);
	bool previousAnimationFrame();
	bool nextAnimationFrame();

	// Play animations
	bool playAnimation(const std::string& animationName);
	bool playAnimation(const std::string& animationName, float fps);
	void setAnimationSpeed(float fps);
	bool stopAnimation();

private:
	void resetCachedFields();

	std::unordered_map<std::string, std::vector<SDL_Rect>> m_animations;
	std::vector<SDL_Rect>* m_currentAnimation = nullptr;
	SDL_Rect* m_currentClipRect = nullptr;
	int m_currentClipRectIndex;

	// automatic animation playback
	bool m_isPlaying;
	int m_elapsedTime;
	int m_timeLimit;
	int m_direction;
};


#endif // !H_SPRITE_SHEET
