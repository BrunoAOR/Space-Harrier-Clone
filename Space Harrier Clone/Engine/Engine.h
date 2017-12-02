#ifndef H_ENGINE
#define H_ENGINE

class TimeController;
class InputController;
class AudioController;
class SceneManager;
class GameObjectsManager;
class ComponentsManager;


class Engine final
{
public:
	Engine();
	~Engine();

	bool init() const;
	void handleEvents(bool& shouldQuit) const;
	void loop() const;
	void close() const;

	TimeController* time = nullptr;
	InputController* input = nullptr;
	AudioController* audio = nullptr;
	SceneManager* sceneManager = nullptr;
	GameObjectsManager* gameObjectsManager = nullptr;
	ComponentsManager* componentsManager = nullptr;

private:
	bool initSDL() const;
	bool initEngine() const;
};

extern Engine* engine;


#endif // !H_ENGINE
