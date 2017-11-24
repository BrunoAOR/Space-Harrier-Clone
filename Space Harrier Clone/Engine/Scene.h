#ifndef H_SCENE
#define H_SCENE


class Scene
{
	friend class SceneManager;
public:
	virtual ~Scene() {};
	virtual bool load() = 0;
	virtual void unload() = 0;
};


#endif // !H_SCENE
