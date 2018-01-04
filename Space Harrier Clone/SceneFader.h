#ifndef H_SCENE_FADER
#define H_SCENE_FADER

#include "Engine/Behaviour.h"
#include "Engine/Reference.h"
#include "Engine/SDL2/include/SDL_pixels.h"
#include "MessengerEventListener.h"
class RectangleRenderer;


class SceneFader :
	public Behaviour, public MessengerEventListener
{
public:
	virtual void onDestroy();

	void init(int targetSceneIndex, SDL_Color targetColor, int fadeTimeMS, int fadeInDelayMS, int fadeOutDelayMS, bool shouldFadeIn);
	virtual void awake() override;
	virtual void update() override;

	// Inherited via MessengerEventListener
	virtual void eventsCallback(MessengerEventType eventType) override;

private:
	void fadeOutToScene();

	Reference<RectangleRenderer> m_rectRenderer;
	int m_targetSceneIndex;
	Uint8 m_defaultAlpha;
	int m_fadeTimeMS;

	int m_fadeInDelayMS;
	int m_fadeOutDelayMS;

	bool m_isFadingIn;
	bool m_isFadingOut;
	int m_fadeElapsedTime;

	SDL_Color m_defaultColor;
};


#endif // !H_SCENE_FADER
